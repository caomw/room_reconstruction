#ifndef ViewerRT_LAUNCHER_HPP
#define ViewerRT_LAUNCHER_HPP

	//**CONSTRUCTOR (PRINCIPAL MENU)**//
	 ViewerRT_launcher::ViewerRT_launcher (ViewerRT *viewer_real_time){
		viewer = viewer_real_time;}



	//**DESTRUCTOR**//
	 ViewerRT_launcher::~ViewerRT_launcher (){}



	//**MAIN MENUS**//
	void ViewerRT_launcher::launcher_1(){
	
		bool run(true);	
		int i(0);
		while (run==true){			
			//**info showed**//
			system("clear");
			std::cout << "-------------------Viewer launcher--------------------\n"
					  << "Start viewer.......................................[1]\n"
					  << "Stop viewer........................................[2]\n"
					  << "Show PID vector....................................[3]\n"
					  << "Change the number of windows ......................[4]\n"
					  << "Turn on/off rotation ..............................[5]\n"
					  << "Turn on/off fullscreen ............................[6]\n"
					  << "Load XYZ cloud.....................................[7]\n"
					  << "Load XYZ colour cloud..............................[8]\n"
					  << "Load XYX RGB cloud.................................[9]\n"
					  << "Load STL mesh......................................[10]\n"
					  << "Delete all clouds..................................[11]\n"
					  << "Delete last clouds.................................[12]\n"
					  << "Back...............................................[0]\n"
					  << "\nOption: ";
			
			
			
			//**get value**//
			char input [2];        
			std::cin >> input;        
		 


			//**manage value**//
			//->Exit launcher
			if (!strcmp(input,"0")){ 
				run = false;}
			
			//->Start viewer
			else if (!strcmp(input,"1")){
				viewer->run_viewer();}
			
			
			//->Close viewer
			else if (!strcmp(input,"2")){
				viewer->close_viewer_process(true);}
			
			
			//-> Get pid vector
			else if (!strcmp(input,"3")){
				system("clear");
				std::cout << "Proccess / pid\n" << std::endl;
				getchar();
				for (i = 0; i < viewer->proccess_vector.size(); i++) {
					std::cout << viewer->proccess_vector[i].process_name << " / " << viewer->proccess_vector[i].pid << std::endl;}
				getchar();}
			
			
			//->Change the number of windows
			else if (!strcmp(input,"4")){
				ViewerRT::config_parameters config;
				viewer->get_parameters(&config);
				std::cout << "Number of windows: ";
				std::cin >> config.n_windows;
				if (config.n_windows == 3){
					std::cout << "Special type: ";
					char a[3];
					std::cin >> a;
					if (!strcmp(a,"yes")) config.special_3_windows = true;
					else config.special_3_windows = false;}
					
				viewer->set_parameters(config, true, false);}
			
			
			//-> Turn on / off rotation
			else if (!strcmp(input,"5")){
				ViewerRT::config_parameters config;
				viewer->get_parameters(&config);
				std::cout << "Kind of rotation: ";
				std::cin >> config.rotation_view_point.kind;
				if (config.rotation_view_point.kind == 1){
					std::cout << "Speed: ";
					std::cin >> config.rotation_view_point.degree_inc;}
				else if (config.rotation_view_point.kind == 2 
				||       config.rotation_view_point.kind == 3
				||       config.rotation_view_point.kind == 4
				||       config.rotation_view_point.kind == 5
				||       config.rotation_view_point.kind == 6
				||       config.rotation_view_point.kind == 7
				||       config.rotation_view_point.kind == 8){
					std::cout << "Speed: ";
					std::cin >> config.rotation_view_point.degree_inc;
					std::cout << "Module: ";
					std::cin >> config.rotation_view_point.module_inc;}
				
					
				viewer->set_parameters(config, false, false);}
			
			
			//-> Turn on / off fullscreen
			else if (!strcmp(input,"6")){
				ViewerRT::config_parameters config;
				viewer->get_parameters(&config);
				config.fullscreen = !config.fullscreen;			
				viewer->set_parameters(config, true, false);}
			
			
			//-> Load XYZ cloud
			else if (!strcmp(input,"7")){
				pcl::PCDReader reader;
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ> ); 
				char name[20];
				unsigned int window;
				
				std::cout << "Name of the file (.pcd): ";
				std::cin >> name;
				std::cout << "Window: ";
				std::cin >> window;
				
				//->Read file
				std::cout << "Loading..." << std::endl;
				reader.read (name, *cloud);
				viewer->load(cloud, window, false);}
			

			//-> Load XYZ colour cloud
			else if (!strcmp(input,"8")){
				pcl::PCDReader reader;
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ> ); 
				char name[20];
				unsigned int window;
				float R,G,B;
				
				std::cout << "Name of the file (.pcd): ";
				std::cin >> name;
				std::cout << "Window: ";
				std::cin >> window;
				std::cout << "R: ";
				std::cin >> R;
				std::cout << "G: ";
				std::cin >> G;
				std::cout << "B: ";
				std::cin >> B;
				
				//->Read file
				std::cout << "Loading..." << std::endl;
				reader.read (name, *cloud);
				viewer->load(cloud, window, R, G, B, false);}			
			
			
			//-> Load RGB XYZ cloud
			else if (!strcmp(input,"9")){
			pcl::PCDReader reader;
				pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB> ); 
				char name[20];
				unsigned int window;
				
				std::cout << "Name of the file (.pcd): ";
				std::cin >> name;
				std::cout << "Window: ";
				std::cin >> window;
				
				//->Read file
				std::cout << "Loading..." << std::endl;
				reader.read (name, *cloud);
				viewer->load(cloud, window, false);}
			
			
			//-> Load mesh
			else if (!strcmp(input,"10")){
				pcl::PolygonMesh polymesh;
				char name[20];
				unsigned int window;
				
				
				std::cout << "Name of the file (.slt): ";
				std::cin >> name;
				std::cout << "Window: ";
				std::cin >> window;
				pcl::io::loadPolygonFile (name, polymesh);
				//->Read file
				std::cout << "Loading..." << std::endl;
				//reader.read (name, *cloud);
				viewer->load(polymesh, window, false);}
			
			
			//-> Delete all clouds
			else if (!strcmp(input,"11")){
				signed int window;
				std::cout << "Number of the windows (0 for delete all): " << std::endl;
				std::cin >> window;
				if (window == 0) viewer->delete_all_objets(false);
				else             viewer->delete_all_objets(window,false);}
			
			
			//-> Delete last clouds
			else if (!strcmp(input,"12")){
				signed int window;
				std::cout << "Number of the windows: " << std::endl;
				std::cin >> window;
				viewer->delete_last_objets(window,false);}
			

			//**Examples**//
			else if (!strcmp(input,"example1")){
				//-> start viewer
				viewer->run_viewer();
				
				//->read example file
				pcl::PCDReader reader;
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ> ); 

				//->load example file (red)
				std::cout << "Loading..." << std::endl;
				reader.read ("Example.pcd", *cloud);
				viewer->load(cloud, 1, 255,0,0, false);
				
				//->Start rotation
				ViewerRT::config_parameters config;
				viewer->get_parameters(&config);
				config.rotation_view_point.kind = 2;
				config.rotation_view_point.degree_inc = 1;
				config.rotation_view_point.module_inc = 1;
				viewer->set_parameters(config, false, false);}	
			
			
			//-> End menu
			else {
				std::cout << input << " is not an option";
				getchar();
				getchar();}}
				
				
		//sleep(4);
		return;}
#endif
	
			
			
			
			
			
			
			
