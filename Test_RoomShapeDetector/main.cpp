#include "../Libraries/RoomShapeDetector_launcher.h" 


int main (int argc, char** argv){
		
	ViewerRT viewer;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>); 
	PointCloudXYZConected cloudC;
	system("clear");
	
	//-> Check if there is any cloud to load
	if (argc>1){
		//->Read file
		std::cout << "Loading..." << std::endl;
		pcl::PCDReader reader;
		reader.read (argv[1], *cloud);}
		
	
	//-> Room shape detector handler
	RoomShapeDetector_launcher Detector_launcher(&viewer, cloud, &cloudC);
	
	Detector_launcher.launcher_1();
	
	system("clear");
	
	return (0);
}
