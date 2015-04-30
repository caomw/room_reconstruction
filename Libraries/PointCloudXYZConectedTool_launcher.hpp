#ifndef PointCloudXYZConectedTool_LAUNCHER_HPP
#define PointCloudXYZConectedTool_LAUNCHER_HPP
	
	//**CONSTRUCTOR**//
	PointCloudXYZConectedTool_launcher::PointCloudXYZConectedTool_launcher (PointCloudXYZConected *cloud_in, ViewerRT *viewer_in){
		
		PointCloudXYZConectedTool PointCloudXYZConectedTool_in;
		
		PointCloudXYZConectedTool_ob = &PointCloudXYZConectedTool_in;
		cloud = cloud_in;
		viewer = viewer_in;
		
		viewer_shared = true;
		
		
		return;}



	//**DESTRUCTOR**//
	 PointCloudXYZConectedTool_launcher::~PointCloudXYZConectedTool_launcher (){
		return;}


	//**MAIN MENUS**//
	void PointCloudXYZConectedTool_launcher::launcher_1(){
	
		bool run(true);	
		int i(0);
		pcl::PolygonMesh polymesh_aux;
		polymesh = &polymesh_aux;
		
		while (run==true){			
			//**info showed**//
			system("clear");
			std::cout << "-------------------Handler launcher-------------------\n"
					  << "Start viewer.......................................[1]\n"
					  << "Close viewer.......................................[2]\n"
					  << "Display cloud info.................................[3]\n"
					  << "Display stl info...................................[4]\n"
					  << "Save Point_XYZC....................................[5]\n"
					  << "Save Point_XYZC (as STL file)......................[6]\n"
					  << "load Point_XYZC....................................[7]\n"
					  << "Convert and display PointXYZC To PolygonMesh.......[8]\n"
					  << "Convert and display PointXYZC To PolygonMesh_STL...[9]\n"
					  << "Convert and display PointXYZC To PointCloudXYZ.....[10]\n"
					  << "Convert and display PointXYZC To Edge_Point_Mesh...[11]\n"
					  << "Convert and display PointXYZC To Point_Mesh........[12]\n"
					  << "Back...............................................[0]\n"
					  << "\nOption: ";
			
			
			
			//**get value**//
			char input [2];        
			std::cin >> input;        
		 


			//**manage value**//
			//->Exit launcher
			if (!strcmp(input,"0")){ 
				run = false;}			
			
			
			//-> Start viewer
			else if (!strcmp(input,"1")){
				if (viewer_shared) viewer->run_viewer();} 
			
			
			//-> Close viewer
			else if (!strcmp(input,"2")){	
				if (viewer_shared) viewer->close_viewer_process(true);} 
			
			
			//->Display cloud info
			else if (!strcmp(input,"3")){
				std::cout << "\nPoints (" << cloud->size() << ")" << std::endl;			
				for (int i=0; i<cloud->size(); i++){
					std::cout << "\n" << i << ".- (X,Y,Z) -> " << cloud->Points[i].p << std::endl;
					std::cout << "\n\tConexions index (" << cloud->Points[i].linear_conexion_index.size() << ")" << std::endl;
					for (int j=0; j < cloud->Points[i].linear_conexion_index.size(); j++)
						std::cout << "\t " << cloud->Points[i].linear_conexion_index[j] << std::endl;
					
					std::cout << "\n\tPlane index (" << cloud->Points[i].plane_index.size() << ")" << std::endl;
					for (int j=0; j < cloud->Points[i].plane_index.size(); j++)
						std::cout << "\t " << cloud->Points[i].plane_index[j] << std::endl;
						
					std::cout << "\n\tLine index (" << cloud->Points[i].line_index.size() << ")" << std::endl;
					for (int j=0; j < cloud->Points[i].line_index.size(); j++)
						std::cout << "\t " << cloud->Points[i].line_index[j] << std::endl;}
				
				std::cout << "\n[Press intro to continue]";
				getchar();
				getchar();
				std::cout <<std::endl;
				
				std::cout << "\nPlane (" << cloud->plane.size() << ")" << std::endl;
				for (int i=0; i < cloud->plane.size(); i++)
					std::cout << "\tPlane " << i << " -> a: " << cloud->plane[i].a << ", b: " << cloud->plane[i].b << ", c: " << cloud->plane[i].c << ", d: " << cloud->plane[i].d << std::endl;
					
				std::cout << "\n[Press intro to continue]";
				getchar();
				std::cout <<std::endl;
				
				std::cout << "\nLine (" << cloud->line.size() << ")" << std::endl;
				for (int i=0; i < cloud->line.size(); i++)
					std::cout << "\tLine " << i << " -> x: " << cloud->line[i].x << ", y:  " << cloud->line[i].y << ", z: " << cloud->line[i].z << " - vx: " << cloud->line[i].vx <<  ", vy: "<< cloud->line[i].vy << ", vz: " << cloud->line[i].vz << std::endl;
				

				getchar();}
			
			
			//->Display STL info
			else if (!strcmp(input,"4")){
				
				if (polymesh->polygons.size() < 1){
					std::cout << "There is no mesh data" << std::endl;
					getchar();
					getchar();}
					
				else{
					std::cout << "\nNumber of polygons: " << polymesh->polygons.size() << std::endl;
					
					for (int i=0; i < polymesh->polygons.size(); i++){
						std::cout << "Polygon " << i << "(" << polymesh->polygons[i].vertices.size() << " vertices)\t->  ";
						for (int j=0; j < polymesh->polygons[i].vertices.size() - 1; j++)
							std::cout << polymesh->polygons[i].vertices[j] << " - ";
						std::cout << polymesh->polygons[i].vertices[polymesh->polygons[i].vertices.size() - 1] << std::endl;}
					
					std::cout << "\n[Press intro to continue]";
					getchar();
					getchar();
					std::cout <<std::endl;
					
					
					//->Convert Pointcloud2 to Pointcloud and display points
					pcl::PointCloud<pcl::PointXYZ> cloud_xyz;
					pcl::fromPCLPointCloud2(polymesh->cloud,cloud_xyz);
					std::cout << "\nNumber of points: " << cloud_xyz.size() << std::endl;
					for (int i=0; i < cloud_xyz.size(); i++)
						std::cout << i << " -> " << cloud_xyz.points[i] << std::endl;
									
					getchar();}}
			
			
			//->Save Point_XYZC
			else if (!strcmp(input,"5")){
				//-> Save
				char name[20];
				std::cout << "File name: ";
				std::cin >> name;
				const char* file_name(name);
				if (!PointCloudXYZConectedTool_ob->save_shape_as_vtk_file(*cloud,file_name)){
					std::cout << "Error when saving the file";
					getchar();getchar();}

					
			}
			
			
			//->Save Point_XYZC (As a STL file)
			else if (!strcmp(input,"6")){
				//-> Save
				char name[20];
				std::cout << "File name: ";
				std::cin >> name;
				const char* file_name(name);
				if (!PointCloudXYZConectedTool_ob->save_shape_as_STL_file(*cloud,file_name)){
					std::cout << "Error when saving the file";
					getchar();getchar();}}
			
			
			//->load Point_XYZC
			else if (!strcmp(input,"7")){
				//-> Load
				char name[20];
				std::cout << "File name: ";
				std::cin >> name;
				const char* file_name(name);
				if (!PointCloudXYZConectedTool_ob->load_shape_from_vtk_fie(cloud,file_name)){
					std::cout << "Error when saving the file";
					getchar();getchar();}}
			
			
			//->Convert and display PointXYZC To PolygonMesh
			else if (!strcmp(input,"8")){
				
				if (!PointCloudXYZConectedTool_ob->PointXYZC_2_PolygonMesh(cloud,&polymesh_aux)){
					std::cout << "Error when converting to polymesh";
					getchar();getchar();}
				
				else {
					int window;
					window = get_display_window();
					if (window > 0){
						if (!viewer->load(*polymesh, window, false)){
							std::cout << "Error loading the polymesh";
							getchar();getchar();}}
							
							
					else {
						std::cout << "Can't display";
						getchar();getchar();}}}
								
			
			//->Convert and display PointXYZC To PolygonMesh_STL
			else if (!strcmp(input,"9")){
				if (!PointCloudXYZConectedTool_ob->PointXYZC_2_PolygonMesh_STL(cloud,&polymesh_aux)){
					std::cout << "Error when converting to polymesh_STL";
					getchar();getchar();}
				
				else {
					int window;
					window = get_display_window();
					if (window > 0){
						if (!viewer->load(*polymesh, window, false)){
							std::cout << "Error loading the polymesh_STL";
							getchar();getchar();}}
							
							
					else {
						std::cout << "Can't display";
						getchar();getchar();}}}
			
			
			//->Convert and display PointXYZC To PointCloudXYZ
			else if (!strcmp(input,"10")){
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
				if (!PointCloudXYZConectedTool_ob->PointXYZC_2_PointCloudXYZ(cloud,cloud_aux)){
					std::cout << "Error when converting to cloud XYZ";
					getchar();getchar();}
				
				else {
					cloud_XYZ = cloud_aux;
					int window;
					window = get_display_window();
					if (window > 0){
						if (!viewer->load(cloud_XYZ, window, 255,0,0, false)){
							std::cout << "Error loading the cloud XYZ";
							getchar();getchar();}}
							
							
					else {
						std::cout << "Can't display";
						getchar();getchar();}}}
			
			
			//->Convert and display PointXYZC To Edge_Point_Mesh
			else if (!strcmp(input,"11")){
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
				float gap;
				std::cout << "Gap: ";
				std::cin >> gap;
				if (!PointCloudXYZConectedTool_ob->PointXYZC_2_Edge_Point_Mesh(cloud,cloud_aux,gap)){
					std::cout << "Error when converting to edge point mesh";
					getchar();getchar();}
				
				else {
					cloud_XYZ = cloud_aux;
					int window;
					window = get_display_window();
					if (window > 0){
						if (!viewer->load(cloud_XYZ, window, false)){
							std::cout << "Error loading the edge point mesh";
							getchar();getchar();}}
							
							
					else {
						std::cout << "Can't display";
						getchar();getchar();}}}
			
			
			//->Convert and display PointXYZC To Point_Mesh
			else if (!strcmp(input,"12")){
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
				float density;
				std::cout << "Density: ";
				std::cin >> density;
				if (!PointCloudXYZConectedTool_ob->PointXYZC_2_Point_Mesh(cloud,cloud_aux,density)){
					std::cout << "Error when converting to point mesh";
					getchar();getchar();}
				
				else {
					cloud_XYZ = cloud_aux;
					int window;
					window = get_display_window();
					if (window > 0){
						if (!viewer->load(cloud_XYZ, window, false)){
							std::cout << "Error loading the point mesh";
							getchar();getchar();}}
							
							
					else {
						std::cout << "Can't display";
						getchar();getchar();}}}
			
			
			//**Examples**//
			//**Make an example (cube)
			else if (!strcmp(input,"example1")){
				
				//-> Clear cloud
				cloud->clear();
				
				
				PointXYZC point;
				
				//->Point 0
				point.p.x = 0; 
				point.p.y = 0;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(7);
				cloud->Points.push_back(point);
				
				//->Point 1
				point.p.x = 1; 
				point.p.y = 0;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(4);
				cloud->Points.push_back(point);
				
				//->Point 2
				point.p.x = 0; 
				point.p.y = 1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);
				
				//->Point 3
				point.p.x = 1; 
				point.p.y = 1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(5);
				cloud->Points.push_back(point);
				
				//->Point 4
				point.p.x = 1; 
				point.p.y = 0;
				point.p.z = 1;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(5);
				point.linear_conexion_index.push_back(7);
				cloud->Points.push_back(point);
				
				//->Point 5
				point.p.x = 1; 
				point.p.y = 1;
				point.p.z = 1;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(6);
				point.linear_conexion_index.push_back(4);
				cloud->Points.push_back(point);
				
				//->Point 6
				point.p.x = 0; 
				point.p.y = 1;
				point.p.z = 1;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(5);
				point.linear_conexion_index.push_back(7);
				cloud->Points.push_back(point);
				
				//->Point 7
				point.p.x = 0; 
				point.p.y = 0;
				point.p.z = 1;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);}			
			
			//**Make an example2 (piramid)
			else if (!strcmp(input,"example2")){
				
				//-> Clear cloud
				cloud->clear();
				
				
				PointXYZC point;
				
				//->Point 0
				point.p.x = 1; 
				point.p.y = 0;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(2);
				cloud->Points.push_back(point);
				
				//->Point 1
				point.p.x = 0; 
				point.p.y = 1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(3);
				cloud->Points.push_back(point);
				
				//->Point 2
				point.p.x = 0; 
				point.p.y = -1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(3);
				cloud->Points.push_back(point);
				
				//->Point 3
				point.p.x = -1; 
				point.p.y = 0;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(1);
				cloud->Points.push_back(point);
				
				//->Point 4
				point.p.x = 0; 
				point.p.y = 0;
				point.p.z = 1;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(3);
				cloud->Points.push_back(point);}
					
			//**Make an example3 ()
			else if (!strcmp(input,"example3")){
				
				//-> Clear cloud
				cloud->clear();
				
				
				PointXYZC point;
				
				//->Point 0
				point.p.x = 1; 
				point.p.y = 0;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(5);
				cloud->Points.push_back(point);
				
				//->Point 1
				point.p.x = 0; 
				point.p.y = 1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(5);
				cloud->Points.push_back(point);
				
				//->Point 2
				point.p.x = 0; 
				point.p.y = -1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(5);
				cloud->Points.push_back(point);
				
				//->Point 3
				point.p.x = -1; 
				point.p.y = 0;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(5);
				cloud->Points.push_back(point);
				
				//->Point 4
				point.p.x = 0; 
				point.p.y = 0;
				point.p.z = 1;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(3);
				cloud->Points.push_back(point);				
				
				//->Point 5
				point.p.x = 0; 
				point.p.y = 0;
				point.p.z = -1;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(3);
				cloud->Points.push_back(point);
				
				
				}
					
					
			//**Make an example4 ()
			else if (!strcmp(input,"example4")){
				
				//-> Clear cloud
				cloud->clear();
				
				
				PointXYZC point;
				
				//->Point 0
				point.p.x = -1; 
				point.p.y = 2;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(5);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);
				
				//->Point 1
				point.p.x = 1; 
				point.p.y = 2;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);
				
				//->Point 2
				point.p.x = 2; 
				point.p.y = 1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);
				
				//->Point 3
				point.p.x = 2; 
				point.p.y = -1;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);
				
				//->Point 4
				point.p.x = 1; 
				point.p.y = -2;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(5);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);				
				
				//->Point 5
				point.p.x = -1; 
				point.p.y = -2;
				point.p.z = 0;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(6);
				cloud->Points.push_back(point);
				
				
				//->Point 6
				point.p.x = 0; 
				point.p.y = 0;
				point.p.z = 2;
				point.linear_conexion_index.clear();
				point.linear_conexion_index.push_back(0);
				point.linear_conexion_index.push_back(1);
				point.linear_conexion_index.push_back(2);
				point.linear_conexion_index.push_back(3);
				point.linear_conexion_index.push_back(4);
				point.linear_conexion_index.push_back(5);
				cloud->Points.push_back(point);
				}
					
			
			//** Develop int
			else if (!strcmp(input,"develop_int") || !strcmp(input,"i")){
				
				system("clear");
				std::cout << "Int vector info \t size: " << PointCloudXYZConectedTool_ob->develop_int->size() <<  std::endl << std::endl;
				std::vector <int> develop_vector;
				develop_vector = *PointCloudXYZConectedTool_ob->develop_int;
				for (int w=0; w < develop_vector.size(); w++){
					//-> simple space
					if (develop_vector[w] == 1*1e5+1) std::cout << std::endl;
					
					//-> Triple space
					else if (develop_vector[w] == 2*1e5+1) std::cout << std::endl << std::endl << std::endl;
					
					
					//-> Label
					else if (develop_vector[w] == 3*1e5+1) std::cout << "Set of data number " << w << std::endl;
					
					//-> Print info
					else std::cout <<  develop_vector[w] << "\t";}
				getchar();
				getchar();}
			
			
			//** Develop float
			else if (!strcmp(input,"develop_float") || !strcmp(input,"f")){
				
				system("clear");
				std::cout << "Float vector info \t size: " << PointCloudXYZConectedTool_ob->develop_float->size() <<  std::endl << std::endl;
				std::vector <float> develop_vector;
				develop_vector = *PointCloudXYZConectedTool_ob->develop_float;
				for (int w=0; w < develop_vector.size(); w++){
					//-> simple space
					if (develop_vector[w] == 1*1e5+1) std::cout << std::endl;
					
					//-> Triple space
					else if (develop_vector[w] == 2*1e5+1) std::cout << std::endl << std::endl << std::endl;
					
					
					//-> Label
					else if (develop_vector[w] == 3*1e5+1) std::cout << "Set of data number " << w << std::endl;
					
					//-> Print info
					else std::cout <<  develop_vector[w] << "\t";}
				getchar();
				getchar();}
			
			
			//-> End menu
			else {
				std::cout << input << " is not an option" ;
				getchar();
				getchar();}}
		
		
		return;}

	
	
	
	//**PRIVATE FUNCTIONS**//
	//**GET DISPLAY WINDOW**//
	int PointCloudXYZConectedTool_launcher::get_display_window(){
		//-> See if the viewer is running
		if (!viewer->viewer_state()) return (-1);
		
		//-> If the viewer is running, see how many windows are available
		ViewerRT::config_parameters config;
		viewer->get_parameters(&config);
		if (config.n_windows == 1) return (1);
		else if (config.n_windows < 1) return (-1);
		else if (config.n_windows > 1){
			unsigned int window; 
			std::cout << "Display window: ";
			std::cin >> window;
			return (window);}
		return (-1);}
	
#endif