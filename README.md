# pointcloudToTXT
convert a pcl point cloud to txt format

----------------------
This program convert a point cloud to .txt file.
Support the next extension:

* PCD 
* PLY 

## Compilation
* Set "YOUR OWN" PCL Build DIR in CMakeList.txt e.g: **/opt/pcl-1.8.1/build** and save it.
* Create a "build" folder

in the main folder:

	- cd /build  
	- cmake ../src/
    - make
       
        	 
### Test

	cd /build
	./pcl-visualizer <pcd file> 
  	./pcl-visualizer <ply file> 

  



