/*********************************
           HEADERS
**********************************/
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>

#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

#include <iostream>
#include <fstream>
#include <string>

void printUsage (const char* progName){
  std::cout << "\nUse: " << progName << " <file> -o <output dir>"  << std::endl <<
               "support: .pcd .ply" << std::endl <<
               "[q] to exit" << std::endl;
}


int main(int argc, char **argv){

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
  pcl::PolygonMesh cl;
  std::vector<int> filenames;
  bool file_is_pcd = false;
  bool file_is_ply = false;
  bool file_is_txt = false;
  bool file_is_xyz = false;


  if(argc < 4 or argc > 4){
      printUsage (argv[0]);
      return -1;
  }

  pcl::console::TicToc tt;
  pcl::console::print_highlight ("Loading ");

  filenames = pcl::console::parse_file_extension_argument(argc, argv, ".ply");
  if(filenames.size()<=0){
      filenames = pcl::console::parse_file_extension_argument(argc, argv, ".pcd");
      if(filenames.size()<=0){
        printUsage (argv[0]);
        return -1;
         
      }else if(filenames.size() == 1){
          file_is_pcd = true;
      }
  }else if(filenames.size() == 1){
      file_is_ply = true;
  }else{
      printUsage (argv[0]);
      return -1;
  }
  
  std::string output_dir;
  if(pcl::console::parse_argument(argc, argv, "-o", output_dir) == -1){
      PCL_ERROR ("Need an output directory! Please use <input cloud> -o <output dir>\n");
      return(-1);
  }
    
  if(file_is_pcd){
      if(pcl::io::loadPCDFile(argv[filenames[0]], *cloud) < 0){
          std::cout << "Error loading point cloud " << argv[filenames[0]]  << "\n";
          printUsage (argv[0]);
          return -1;
      }
      pcl::console::print_info("\nFound pcd file.\n");
      pcl::console::print_info ("[done, ");
      pcl::console::print_value ("%g", tt.toc ());
      pcl::console::print_info (" ms : ");
      pcl::console::print_value ("%d", cloud->size ());
      pcl::console::print_info (" points]\n");
      
    }else if(file_is_ply){
      pcl::io::loadPLYFile(argv[filenames[0]],*cloud);
      if(cloud->points.size()<=0 or cloud->points.at(0).x <=0 and cloud->points.at(0).y <=0 and cloud->points.at(0).z <=0){
          pcl::console::print_warn("\nloadPLYFile could not read the cloud, attempting to loadPolygonFile...\n");
          pcl::io::loadPolygonFile(argv[filenames[0]], cl);
          pcl::fromPCLPointCloud2(cl.cloud, *cloud);
          if(cloud->points.size()<=0 or cloud->points.at(0).x <=0 and cloud->points.at(0).y <=0 and cloud->points.at(0).z <=0){
              pcl::console::print_warn("\nloadPolygonFile could not read the cloud, attempting to PLYReader...\n");
              pcl::PLYReader plyRead;
              plyRead.read(argv[filenames[0]],*cloud);
              if(cloud->points.size()<=0 or cloud->points.at(0).x <=0 and cloud->points.at(0).y <=0 and cloud->points.at(0).z <=0){
                  pcl::console::print_error("\nError. ply file is not compatible.\n");
                  return -1;
              }
          }
       }

      pcl::console::print_info("\nFound ply file.\n");
      pcl::console::print_info ("[done, ");
      pcl::console::print_value ("%g", tt.toc ());
      pcl::console::print_info (" ms : ");
      pcl::console::print_value ("%d", cloud->points.size ());
      pcl::console::print_info (" points]\n");
      
  }else{
      
      printUsage (argv[0]);
      return -1;
  }

  cloud->width = (int) cloud->points.size ();
  cloud->height = 1;
  cloud->is_dense = true;

  std::ofstream fout; 
  
  std::string str1 = output_dir; 
  str1 += "/TXT_cloud.txt";
  fout.open(str1.c_str());

  for(int i = 0; i < cloud->points.size (); ++i){
  
      //fout << cloud->points[i] << std::endl;
     
      uint32_t rgb_ = *reinterpret_cast<int*>(&cloud->points[i].rgb); 
      uint8_t r_, g_, b_; 

      r_ = (rgb_ >> 16) & 0x0000ff; 
      g_ = (rgb_ >> 8)  & 0x0000ff; 
      b_ = (rgb_)       & 0x0000ff; 

      unsigned int r, g, b; 
      r = *((uint8_t *) &r_); 
      g = *((uint8_t *) &g_); 
      b = *((uint8_t *) &b_);      

      fout << cloud->points[i].x << " " << cloud->points[i].y << " " << cloud->points[i].z << " " << 
              r << " " << g << " " << b << std::endl;             
  }
    
  fout.close();
  
  output_dir += "/TXT_cloud.txt";
  
  std::string sav = "saved point cloud in:";
  sav += output_dir;

  pcl::console::print_info(sav.c_str());
  std::cout << std::endl;


  return 0;
}



