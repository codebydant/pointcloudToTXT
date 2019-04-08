# pointcloudToTXT
convert a pcl point cloud into txt format

----------------------
This program convert a point cloud into .txt file  <br />

## Input file structure 

* .pcd
* .ply 

## Output file structure 
* point_cloud.txt: 

        x y z r g b

## Compilation
* Set "YOUR OWN" PCL Build DIR in CMakeList.txt e.g: **/opt/pcl-1.8.1/build** and save it.
* Create a "build" folder

in the main folder:

	- cd /build  
	- cmake ../src/
    - make
       
        	 
### Test

	cd /build
	./pointcloudToTXT <pcd file> -o <output dir>
  	./pointcloudToTXT <ply file> -o <output dir>

  



