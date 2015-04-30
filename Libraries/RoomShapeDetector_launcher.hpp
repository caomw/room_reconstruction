#ifndef ROOMSHAPEDETECTOR_LAUNCHER_HPP
#define ROOMSHAPEDETECTOR_LAUNCHER_HPP

	RoomShapeDetector_launcher::RoomShapeDetector_launcher(ViewerRT *viewer_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected *cloudC_in){
		
		//-> Associate pointers
		viewer = viewer_in;
		cloud = cloud_in;
		cloudC = cloudC_in;
		
		RoomShapeDetector *Detector_declaration (new RoomShapeDetector);
		Detector = Detector_declaration;
		
		RoomShapeDetector::process_data *data_out_declaration (new RoomShapeDetector::process_data);
		data_out = data_out_declaration;
		
		RoomShapeDetector::config_parameters *config_declaration(new RoomShapeDetector::config_parameters);
		config = config_declaration;
		if (!Detector->get_default_configuration(config)){
			std::cout << "Can't get default configuration" << std::endl;}
		
		
		rotation_enable = true;
		
		return;}
		

	RoomShapeDetector_launcher::~RoomShapeDetector_launcher(){
		 return;}


	//**MAIN MENUS**//
	void RoomShapeDetector_launcher::launcher_1(){
	
		bool run(true);	
		while (run==true){			
			//**info showed**//
			system("clear");
			std::cout << "--------------Shape detector launcher-----------------\n"
					  << "Start viewer.......................................[1]\n"
					  << "Close viewer.......................................[2]\n"
					  << "Load cloud XYZ.....................................[3]\n"
					  << "Change configuration...............................[4]\n"
					  << "Execute room shape detector........................[5]\n"
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
				viewer->run_viewer();} 
			
			
			//-> Close viewer
			else if (!strcmp(input,"2")){	
				viewer->close_viewer_process(true);} 
			
				
			//-> Load cloud XYZ
			else if (!strcmp(input,"3")){
				
				//-> Get file name
				char name[20];
				std::cout << "Name of the file (.pcd): ";
				std::cin >> name;
				
				//-> Get window 
				int window(get_display_window());

				
				//->Read file
				std::cout << "Loading..." << std::endl;
				pcl::PCDReader reader;
				reader.read (name, *cloud);
				
				//-> Display
				if (window > 0){
					if (!viewer->load(cloud, window, false)){
							std::cout << "Error loading the edge point mesh";
							getchar();getchar();}}}


			//-> Change configuration
			else if (!strcmp(input,"4")){
				sub_launcher_2();}
			
			
			//->Execute room shape detector
			else if (!strcmp(input,"5")){
				system("clear");
				std::cout << "Processing..." << std::endl;
				if (!Detector->get_room_shape(cloud, config, cloudC, data_out)){
					std::cout << "Error in the shape detector process";
					getchar();getchar();}
				sub_launcher_results();
				sub_launcher_1();}
			
			
			//-> End menu
			else {
				std::cout << input << " is not an option";
				getchar();
				getchar();}}
				
		return;}
		
		
	//**PRIVATE FUNCTIONS**//
	//**GET DISPLAY WINDOW**//
	int RoomShapeDetector_launcher::get_display_window(){
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
	
	
	//**SUB LAUNCHERS**//
	void RoomShapeDetector_launcher::sub_launcher_2(){
		bool run(true);	
		while (run==true){			
			//**info showed**//
			system("clear");
			std::cout << "--------------Shape detector launcher-----------------\n"
					  << "Set default configuration..........................[1]\n"
					  << "Set percentile value...............................[2]\n"
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
				if (!Detector->get_default_configuration(config)){
					std::cout << "Can't get default configuration" << std::endl;}}
	
	
			else if (!strcmp(input,"2")){
				float value;
				std::cout << "Value (" << config->phase4.percentil << "): " ;
				std::cin >> value;
				config->phase4.percentil = value;}
				
			}
	}
	
	
	//**SUB2 LAUNCHERS**//

	void RoomShapeDetector_launcher::sub_launcher_1(){
	
		bool run(true);	
		while (run==true){
			//**Load launcher**//
			ViewerRT_launcher ViewerRTm(viewer);
			
			//**info showed**//
			system("clear");
			std::cout << "--------------Shape detector launcher-----------------\n"
					  << "Display phase 1 info...............................[1]\n"
					  << "Display phase 2 info...............................[2]\n"
					  << "Display phase 3 info...............................[3]\n"
					  << "Display phase 4 info...............................[4]\n"
					  << "Display phase 5 info...............................[5]\n"
					  << "Display phase 6 info...............................[6]\n"
					  << "Display phase 7 info...............................[7]\n"
					  << "Display the input data.............................[8]\n"
					  << "Display the output data............................[9]\n"
					  << "Enable/Disable all rotations.......................[10]\n"
					  << "Display viewer menu................................[11]\n"
					  << "Back...............................................[0]\n"
					  << "\nOption: ";
			
			
			
			//**get value**//
			char input [2];        
			std::cin >> input;        
		 


			//**manage value**//
			//->Exit launcher
			if (!strcmp(input,"0")){ 
				run = false;}
			
			
			//-> Display phase 1 info
			else if (!strcmp(input,"1")){
				sub_launcher_phase1();}
						
			
			//-> Display phase 2 info
			else if (!strcmp(input,"2")){
				sub_launcher_phase2();}
			
			
			//-> Display phase 3 info
			else if (!strcmp(input,"3")){
				sub_launcher_phase3();}
			
			
			//-> Display phase 4 info
			else if (!strcmp(input,"4")){
				sub_launcher_phase4();}
			
			
			//-> Display phase 5 info
			else if (!strcmp(input,"5")){
				sub_launcher_phase5();}
			
			
			//-> Display phase 6 info
			else if (!strcmp(input,"6")){
				sub_launcher_phase6();}

			
			//-> Display phase 7 info
			else if (!strcmp(input,"7")){
				sub_launcher_phase7();}				
			
	
			//-> Display the input data
			else if (!strcmp(input,"8")){
				
				//->Aux objects
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
				*cloud_aux = data_out->cloud;
				
				
				//-> Show info
				system("clear");
				std::cout << "Number of points of the input cloud: " << data_out->cloud.size() << std::endl;
				
				
				//-> Display cloud in viewer
				if (viewer->viewer_state()){
					//-> Configure viewer: Get current configuration
					ViewerRT::config_parameters config;
					viewer->get_parameters(&config);

					//-> Configure viewer: Set kind of rotation
					config.rotation_view_point.kind = 0;
					
					//-> Configure viewer: Configure the number of windows
					viewer->get_parameters(&config);
					config.n_windows = 1;
					
					//-> Configure viewer: Set parameters	
					viewer->set_parameters(config, true, false);
				int window(get_display_window());
				if (window > 0){
					if (!viewer->load(cloud_aux, window, false)){
					std::cout << "Cant display cloud";}}}
				
				getchar();
				getchar();}
			
			
			//-> Display the output data
			else if (!strcmp(input,"9")){
				sub_launcher_results();}
							
			
			//-> Enable / disable all rotations
			else if (!strcmp(input,"10")){
				if (rotation_enable){
					rotation_enable = false;
					std::cout << "Rotation disabled";
					getchar();				
					getchar();}				
				else{
					rotation_enable = true;
					std::cout << "Rotation enabled";
					getchar();
					getchar();}
				}
			
			
			//-> Load viewer menu
			else if (!strcmp(input,"11")){
				ViewerRTm.launcher_1();}
			
					
			//-> End menu
			else {
				std::cout << input << " is not an option";
				getchar();
				getchar();}}
				
		return;}
	
	
	//-> Phase 1 sub menu
	void RoomShapeDetector_launcher::sub_launcher_phase1(){
		//->Aux objects
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
		*cloud_aux = data_out->phase1.cloud_filtered;
		
		
		//-> Show info
		system("clear");
		std::cout << "Number of points of the filtered cloud: " << data_out->phase1.cloud_filtered.size() << std::endl;
		
		//-> Display cloud in viewer
		if (viewer->viewer_state()){
			//-> Configure viewer: Get current configuration
			ViewerRT::config_parameters config;
			viewer->get_parameters(&config);

			//-> Configure viewer: Set kind of rotation
			if (rotation_enable) config.rotation_view_point.kind = 7;
			if (!rotation_enable) config.rotation_view_point.kind = 0;
			
			//-> Configure viewer: Set rotation speed
			config.rotation_view_point.degree_inc = 1;
			
			//-> Configure viewer: Set module speed
			config.rotation_view_point.module_inc = 1;
			
			//-> Configure viewer: Configure the number of windows
			viewer->get_parameters(&config);
			config.n_windows = 1;
			
			//-> Configure viewer: Set parameters	
			viewer->set_parameters(config, true, false);
			
			
			int window(get_display_window());
			if (window > 0){
				if (!viewer->load(cloud_aux, window, 255, 0, 0, false)){
				std::cout << "Cant display cloud";}}}
				
				getchar();
				getchar();}
	
	
	//-> Phase 2 sub menu
	void RoomShapeDetector_launcher::sub_launcher_phase2(){
		
		//-> Common objects
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
		PointCloudXYZConectedTool PointCloudXYZConected_Tool;
		
			
		//-> Visualize the planes
		if (viewer->viewer_state()){
			
			//-> Configure viewer: Get current configuration
			ViewerRT::config_parameters config;
			viewer->get_parameters(&config);

			//-> Configure viewer: Set kind of rotation
			if (rotation_enable)config.rotation_view_point.kind = 7;
			if (!rotation_enable) config.rotation_view_point.kind = 0;
			
			
			//-> Configure viewer: Set rotation speed
			config.rotation_view_point.degree_inc = 1;
			
			//-> Configure viewer: Set module speed
			config.rotation_view_point.module_inc = 1;
			
			//-> Configure viewer: Configure the number of windows
			config.n_windows = 3;
			config.special_3_windows = true;
			
			//-> Configure viewer: Set parameters	
			viewer->set_parameters(config, true, false);
			
			
			//-> Display the filtered cloud in the windows 1
			*cloud_aux = data_out->phase1.cloud_filtered;
			if (!viewer->load(cloud_aux, 1, false)){
				std::cout << "Cant display cloud";}
			
			
			//-> Display all the planes
			for (int i=0; i < data_out->phase2.found_plane_points.size(); i++){
				*cloud_aux = data_out->phase2.found_plane_points[i];
					
				if (!viewer->load(cloud_aux, 3, i, data_out->phase2.found_plane_points.size(), false)){
				std::cout << "Cant display cloud";}}}
			
			
		//->Display a concrete plane and phase info
		bool stop (false);
		while (!stop){
			
			//-> Display text info
			system("clear");
			std::cout << "Process over cycles: " << data_out->phase2.process_over_cycles << std::endl;
			std::cout << "Cloud left under limit: " << data_out->phase2.cloud_left_under_limit << std::endl;
			std::cout << "Number of found planes: " << data_out->phase2.I_found_plane_points.size() << std::endl << std::endl;
			
			
			//-> Display number of point in each plane
			std::cout << "  - Planes info - " << std::endl;
			std::cout <<  std::endl;
			for (int i=0; i < data_out->phase2.I_found_plane_points.size(); i++)
				std::cout << " Plane " << i << ": " << data_out->phase2.found_plane_points[i].size() << " points" << std::endl;
			std::cout << std::endl;
			
			//-> Display planes info
			PointCloudXYZConected_Tool.display_plane_info(data_out->phase2.planes, true);
			
			
			//-> If the viewer is not running
			if (!viewer->viewer_state()){
				stop = true;
				getchar();
				getchar();}
			
			
			//-> If the viewer is running
			if (viewer->viewer_state()){
				int display_plane; 
				std::cout << "Plane to display (enter -1 to exit): ";
				std::cin >> display_plane;
				
				if (display_plane >= data_out->phase2.found_plane_points.size() || display_plane < 0)
					stop = true;
				
				if (!stop){
				viewer->delete_all_objets(2,false);
				sleep(1);
				*cloud_aux = data_out->phase2.found_plane_points[display_plane];
				if (!viewer->load(cloud_aux, 2, display_plane, data_out->phase2.found_plane_points.size(), false)){
				std::cout << "Cant display cloud";}}}}
		
		
		//-> Go back
		return;}
		
		
	//-> Phase 3 sub menu
	void RoomShapeDetector_launcher::sub_launcher_phase3(){
		//-> Display text info
		system("clear");
		std::cout << "Number of lines: " << data_out->phase3.lines.line.size() << std::endl;
		
		//-> Display lines info
		PointCloudXYZConectedTool PointCloudXYZConected_Tool;
		PointCloudXYZConected_Tool.display_line_info(data_out->phase3.lines, true);
		PointCloudXYZConected_Tool.display_plane_info(data_out->phase3.lines, true);

		getchar();
		getchar();}		

	
	//-> Phase 4 sub menu
	void RoomShapeDetector_launcher::sub_launcher_phase4(){
		
		//-> Clear screen
		system("clear");
		
		
		//-> Common objects
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
		PointCloudXYZConectedTool PointCloudXYZConected_Tool;
		
		//-> Configure viewer if is opened
		if (viewer->viewer_state()){
			
			//-> Configure viewer: Get current configuration
			ViewerRT::config_parameters config;
			viewer->get_parameters(&config);

			//-> Configure viewer: Set kind of rotation
			if (rotation_enable)config.rotation_view_point.kind = 1;
			if (!rotation_enable) config.rotation_view_point.kind = 0;
			
			//-> Configure viewer: Set rotation speed
			config.rotation_view_point.degree_inc = 1;
			
			//-> Configure viewer: Set module speed
			config.rotation_view_point.module_inc = 1;
			
			//-> Configure viewer: Configure the number of windows
			config.n_windows = 3;
			config.special_3_windows = true;
			
			//-> Configure viewer: Set parameters	
			viewer->set_parameters(config, true, false);}
		
		
		//-> Load All planes in if the viewer is opened 
		if (viewer->viewer_state()){
			//-> Display all the planes
			for (int i=0; i < data_out->phase2.found_plane_points.size(); i++){
				*cloud_aux = data_out->phase2.found_plane_points[i];
				if (!viewer->load(cloud_aux, 1, i, data_out->phase2.found_plane_points.size(), false)){
					std::cout << "Cant display cloud";}}}
			
		
		//-> Buckle menu
		bool stop(false);
		while (!stop){
		

		
			//-> Display general info on the shell
			std::cout << " - General information -" << std::endl;
			std::cout << " Number of projections: " << data_out->phase4.projections.size() << std::endl;
			std::cout << " Single filter values: "; 
			for (int i =0; i < data_out->phase4.filter_values.size(); i++)
					std::cout << data_out->phase4.filter_values[i] << "  ";
			std::cout << std::endl;
			std::cout << " Common filter value: " << data_out->phase4.commnon_filter_value << std::endl;
			std::cout << " Number of connexions points: " <<  data_out->phase4.segments.size() << std::endl;
			
			
			
			//-> Load option
			int input;
			std::cout << std::endl;
			std::cout << "-> Introduce projection ID value in order to see the projection segment" << std::endl;
			std::cout << "-> Introduce an out of range value to quit this menu " << std::endl;
			std::cout << "value: ";
			std::cin >> input;
			system("clear");
			

			//-> Display more info if the viewer is running
			if (!stop){
				
				//-> Exit sub menu out or range value is introducer
				if (input < 0 || input >= data_out->phase4.projections.size() +1){
					stop = true;}
				
					
				//-> Display all
				else if (input == data_out->phase4.projections.size()){
					//->Clear viewer
					if (viewer->viewer_state()){
						viewer->delete_all_objets(2,false);
						viewer->delete_all_objets(3,false);
						sleep(1);}
					
					
					//-> Display projections
					if (viewer->viewer_state())
					for (int i=0; i < data_out->phase4.projections.size(); i++) {
						*cloud_aux = data_out->phase4.projections[i].projection;
						if (!viewer->load(cloud_aux, 2, false)){
							std::cout << "Cant display cloud";}}
					
					
					//-> Display all the planes
					if (viewer->viewer_state())
					for (int i=0; i < data_out->phase2.found_plane_points.size(); i++){
						*cloud_aux = data_out->phase2.found_plane_points[i];
						if (!viewer->load(cloud_aux, 2, i, data_out->phase2.found_plane_points.size(), false)){
							std::cout << "Cant display cloud";}}
					

					//-> Display all segments on viewer
					if (viewer->viewer_state()){
						PointCloudXYZConectedTool PointCloud_XYZConected_Tool;
						viewer->delete_all_objets(1,false);
						viewer->delete_all_objets(2,false);
						viewer->delete_all_objets(3,false);
						if (!PointCloud_XYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(data_out->phase4.segments, cloud_aux, 0.01)){
							std::cout << "Can't make mesh line" << std::endl;}
						else {
							if (!viewer->load(cloud_aux, 2, false)){
								std::cout << "Cant display cloud" << std::endl;}
							if (!viewer->load(cloud_aux, 1, false)){
								std::cout << "Cant display cloud" << std::endl;}}						
						if (!PointCloud_XYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(data_out->phase4.no_filtered_segments, cloud_aux, 0.05)){
							std::cout << "Can't make mesh line" << std::endl;}
						else {
							if (!viewer->load(cloud_aux, 3, 100, 100, 100, false)){
								std::cout << "Cant display cloud" << std::endl;}							
							if (!viewer->load(cloud_aux, 1, 100, 100, 100, false)){
								std::cout << "Cant display cloud" << std::endl;}}}					
						
						
					//-> Display label
					std::cout << "\n\n - Filtered segments information -" << std::endl;
					PointCloudXYZConected_Tool.display_points_info(data_out->phase4.segments, true);
					PointCloudXYZConected_Tool.display_segment_info(data_out->phase4.segments, true);
					PointCloudXYZConected_Tool.display_plane_info(data_out->phase4.segments, true);					
					std::cout << std::endl;
					
					//-> Display label
					std::cout << "\n\n - Non Filtered segments information -" << std::endl;
					PointCloudXYZConected_Tool.display_points_info(data_out->phase4.no_filtered_segments, true);
					PointCloudXYZConected_Tool.display_segment_info(data_out->phase4.no_filtered_segments, true);
					PointCloudXYZConected_Tool.display_plane_info(data_out->phase4.no_filtered_segments, true);
					std::cout << std::endl;}	
						
				
				//-> Display an option
				else{
					//-> Display info
					std::cout << "\n\n - Projection " << input << " -" <<std::endl;
					std::cout << " Number of point of the projection: "<< data_out->phase4.projections[input].projection.size() << std::endl;
					
					
					//->Clear viewer
					if (viewer->viewer_state()){
						viewer->delete_all_objets(2,false);
						viewer->delete_all_objets(3,false);
						sleep(1);}				
					
					
					//-> Display non filtered projection in window 2
					*cloud_aux = data_out->phase4.projections[input].projection;
					if (viewer->viewer_state())
					if (!viewer->load(cloud_aux, 2, false)){
						std::cout << "Cant display cloud";}	
					
					
					//-> Display the belongs planes
					for (int i=0; i < data_out->phase4.projections[input].plane_index.size(); i++){
						//-> Display info
						std::cout << " Belongs to plane: " << data_out->phase4.projections[input].plane_index[i] << std::endl;
						
						//-> Display clouds
						if (viewer->viewer_state()){
							int plane_index(data_out->phase4.projections[input].plane_index[i]);
							*cloud_aux = data_out->phase2.found_plane_points[plane_index];
							if (!viewer->load(cloud_aux, 2, plane_index, data_out->phase2.found_plane_points.size(), false)){
								std::cout << "Cant display cloud";}
							if (!viewer->load(cloud_aux, 3, plane_index, data_out->phase2.found_plane_points.size(), false)){
							std::cout << "Cant display cloud";}}}
					
						
					//-> Display the segments information from line i 
					std::vector<int> index_segments_to_display;
					std::cout << " Connected points for the line: " << std::endl;
					for (int i=0; i<data_out->phase4.segments.size(); i++)
						for (int j=0; j< data_out->phase4.segments.Points[i].line_index.size(); j++)
							if (data_out->phase4.segments.Points[i].line_index[j] == input)
								index_segments_to_display.push_back(i);
					
					
					//-> Extract data
					PointCloudXYZConected display_cp;
					if (!PointCloudXYZConected_Tool.extract_index_from_pointcloudXYZC(data_out->phase4.segments, index_segments_to_display, &display_cp)){
						//-> Display label
						std::cout << "\n - Segment info -" << std::endl;
						PointCloudXYZConected_Tool.display_points_info(display_cp, true);
						PointCloudXYZConected_Tool.display_segment_info(display_cp, true);
						PointCloudXYZConected_Tool.display_plane_info(display_cp, true);					
						std::cout << std::endl;}
					

					//-> Display the segments from line i on viewer
					if (viewer->viewer_state()){
						if (PointCloudXYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(&display_cp, cloud_aux, 0.01)){
							if (!viewer->load(cloud_aux, 3, false)){
								std::cout << "Cant display cloud" << std::endl;}}}
					
					
					//-> Add gap
					std::cout << std::endl;}}}
					
					
		}//-> Exit menu
		
	
	//-> Phase 5 sub menu
	void RoomShapeDetector_launcher::sub_launcher_phase5(){
		
		//-> Display added segments
		std::cout << "The following segments have been added(" << data_out->phase5.added_segments.size() << "): " ;
		for (int i=0; i < data_out->phase5.added_segments.size(); i++){
			if (i != 0) std::cout << " ,";
			std::cout << data_out->phase5.added_segments[i]; }
		std::cout << std::endl;
		
		
		//-> Display added index
		std::cout << "The following index have been added(" << data_out->phase5.added_index.size() << "): " ;
		for (int i=0; i < data_out->phase5.added_index.size(); i++){
			if (i != 0) std::cout << " ,";
			std::cout << data_out->phase5.added_index[i]; }
		std::cout << std::endl;
		
		
		//-> Display eliminated segments
		std::cout << "The following segments have been deleted(" << data_out->phase5.deleted_segments.size() << "): " ;
		for (int i=0; i < data_out->phase5.deleted_segments.size(); i++){
			if (i != 0) std::cout << " ,";
			std::cout << data_out->phase5.deleted_segments[i]; }
		std::cout << std::endl;
		
		
		//-> Display eliminated index
		std::cout << "The following index have been deleted(" << data_out->phase5.deleted_index.size() << "): " ;
		for (int i=0; i < data_out->phase5.deleted_index.size(); i++){
			if (i != 0) std::cout << " ,";
			std::cout << data_out->phase5.deleted_index[i]; }
		
		
		
		//-> Display all segment info
		std::cout << "\n\n - Segments information -" << std::endl;
		PointCloudXYZConectedTool PointCloudXYZConected_Tool;
		PointCloudXYZConected_Tool.display_points_info(data_out->phase5.segments, true);
		PointCloudXYZConected_Tool.display_segment_info(data_out->phase5.segments, true);
		PointCloudXYZConected_Tool.display_plane_info(data_out->phase5.segments, true);

		
	
	
		//-> Configure viewer if is opened
		if (viewer->viewer_state()){
			
			//-> Configure viewer: Get current configuration
			ViewerRT::config_parameters config;
			viewer->get_parameters(&config);

			//-> Configure viewer: Set kind of rotation
			config.rotation_view_point.kind = 0;
			
			
			//-> Configure viewer: Configure the number of windows
			config.n_windows = 2;
			
			//-> Configure viewer: Set parameters	
			viewer->set_parameters(config, true, false);}
		
		
		//-> Display all segments on viewer before
		if (viewer->viewer_state()){
			PointCloudXYZConected segments_to_display(data_out->phase4.segments);
			PointCloudXYZConectedTool PointCloud_XYZConected_Tool;
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
			if (!PointCloud_XYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(&segments_to_display, cloud_aux, 0.01)){
				std::cout << "Can't make mesh line" << std::endl;}
			else {
				if (!viewer->load(cloud_aux, 1, false)){
					std::cout << "Cant display cloud" << std::endl;}}}
	
	
		//-> Display all segments on viewer after
		if (viewer->viewer_state()){
			PointCloudXYZConected segments_to_display(data_out->phase5.segments);
			PointCloudXYZConectedTool PointCloud_XYZConected_Tool;
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
			if (!PointCloud_XYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(&segments_to_display, cloud_aux, 0.01)){
				std::cout << "Can't make mesh line" << std::endl;}
			else {
				if (!viewer->load(cloud_aux, 2, false)){
					std::cout << "Cant display cloud" << std::endl;}}}
					
					
		//-> Wait			
		getchar();
		getchar();}
	
	
	//-> Phase 6 sub menu
	void RoomShapeDetector_launcher::sub_launcher_phase6(){
		system("clear");
		//-> Common objects
		PointCloudXYZConectedTool PointCloudXYZConected_Tool;
		
		
		//-> Display plane sequence
		std::cout << "Plane sequence: ";
		for (int i = 0; i < data_out->phase6.plane_sequence.size(); i++){
			if (i != 0) std::cout << " - ";
			std::cout << data_out->phase6.plane_sequence[i];}
		std::cout << std::endl;
		
		
		//-> Display Vertical lines info
		std::cout << std::endl;
		std::cout << " - Vertical lines -" << std::endl << std::endl; 
		PointCloudXYZConected_Tool.display_line_info(data_out->phase6.V_lines, true);				
		
		
		//-> Display connected point info
		std::cout << " - Reconstruction shape -" << std::endl << std::endl; 
		PointCloudXYZConected_Tool.display_points_info(data_out->phase6.reconstruction_points, true);
		PointCloudXYZConected_Tool.display_plane_info(data_out->phase6.reconstruction_points, true);
		
		
		//-> Configure viewer if is opened
		if (viewer->viewer_state()){
			
			//-> Configure viewer: Get current configuration
			ViewerRT::config_parameters config;
			viewer->get_parameters(&config);

			//-> Configure viewer: Set kind of rotation
			if (rotation_enable)config.rotation_view_point.kind = 1;
			if (!rotation_enable) config.rotation_view_point.kind = 0;
			
			//-> Configure viewer: Set rotation speed
			config.rotation_view_point.degree_inc = 1;
			
			//-> Configure viewer: Set module speed
			config.rotation_view_point.module_inc = 1;
			
			//-> Configure viewer: Configure the number of windows
			config.n_windows = 3;
			config.special_3_windows = true;
			
			//-> Configure viewer: Set parameters	
			viewer->set_parameters(config, true, false);}
		
		
		
		//-> Display the original cloud and the reconstruction shape
		if (viewer->viewer_state()){
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
			*cloud_aux = data_out->phase1.cloud_filtered;
			if (!viewer->load(cloud_aux, 1, false)){
				std::cout << "Cant display cloud";}}
		
		
		
		//-> Display reconstructed points
		if (viewer->viewer_state()){
			
			//-> Convert points
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
			PointCloudXYZConected conected_cloud_in(data_out->phase6.reconstruction_points);
			if (!PointCloudXYZConected_Tool.PointXYZC_2_PointCloudXYZ(&conected_cloud_in, cloud_aux)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(cloud_aux, 2, false)){
				std::cout << "Cant display cloud";}
				
			if (!PointCloudXYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(&conected_cloud_in, cloud_aux, 0.1)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(cloud_aux, 3, false)){
				std::cout << "Cant display cloud";}}
			

		getchar();
		getchar();}
		

	//-> Phase 7 sub menu
	void RoomShapeDetector_launcher::sub_launcher_phase7(){
		system("clear");
		//-> Common objects
		PointCloudXYZConectedTool PointCloudXYZConected_Tool;
		
		
		//-> Display horizontal lines info
		std::cout << " - Horizontal lines -" << std::endl << std::endl; 
		PointCloudXYZConected_Tool.display_line_info(data_out->phase7.H_lines, true);
		
		
		//-> Display connected point info
		std::cout << " - Reconstruction shape -" << std::endl << std::endl; 
		PointCloudXYZConected_Tool.display_points_info(data_out->phase7.reconstruction_points, true);
		PointCloudXYZConected_Tool.display_plane_info(data_out->phase7.reconstruction_points, true);
		
		
		//-> Configure viewer if is opened
		if (viewer->viewer_state()){
			
			//-> Configure viewer: Get current configuration
			ViewerRT::config_parameters config;
			viewer->get_parameters(&config);

			//-> Configure viewer: Set kind of rotation
			if (rotation_enable)config.rotation_view_point.kind = 1;
			if (!rotation_enable) config.rotation_view_point.kind = 0;
			
			//-> Configure viewer: Set rotation speed
			config.rotation_view_point.degree_inc = 1;
			
			//-> Configure viewer: Set module speed
			config.rotation_view_point.module_inc = 1;
			
			//-> Configure viewer: Configure the number of windows
			config.n_windows = 3;
			config.special_3_windows = true;
			
			//-> Configure viewer: Set parameters	
			viewer->set_parameters(config, true, false);}
		
		
		
		//-> Display the original cloud and the reconstruction shape
		if (viewer->viewer_state()){
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
			*cloud_aux = data_out->phase1.cloud_filtered;
			if (!viewer->load(cloud_aux, 1, false)){
				std::cout << "Cant display cloud";}}
		
		
		
		//-> Display reconstructed points
		if (viewer->viewer_state()){
			
			//-> Convert points
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
			PointCloudXYZConected conected_cloud_in(data_out->phase7.reconstruction_points);
			if (!PointCloudXYZConected_Tool.PointXYZC_2_PointCloudXYZ(&conected_cloud_in, cloud_aux)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(cloud_aux, 2, false)){
				std::cout << "Cant display cloud";}		
				
			if (!PointCloudXYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(&conected_cloud_in, cloud_aux, 0.1)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(cloud_aux, 3, false)){
				std::cout << "Cant display cloud";}}
			

		getchar();
		getchar();}
	
	
	//-> Results
	void RoomShapeDetector_launcher::sub_launcher_results(){
		//-> Common objects
		PointCloudXYZConectedTool PointCloudXYZConected_Tool;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
		PointCloudXYZConected conected_cloud_in(*cloudC);
		
		
		//-> Show info
		system("clear");
		
		std::cout << "Phase 0 (";
		if (data_out->GI_phase0.complete) std::cout  << "complete in  " << data_out->GI_phase0.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase0.complete) std::cout << "no successful) -> ";
		std::cout << "Check if the configuration values are ok. Set the default values for the wrong values." << std::endl;
		
		std::cout << "Phase 1 (";
		if (data_out->GI_phase1.complete) std::cout  << "complete in  " << data_out->GI_phase1.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase1.complete) std::cout << "no successful) -> ";
		std::cout << "Reduce the number of points in the cloud and set a lower bound of the distance between points for the next process." << std::endl;
		
		std::cout << "Phase 2 (";
		if (data_out->GI_phase2.complete) std::cout  << "complete in  " <<  data_out->GI_phase2.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase2.complete) std::cout << "no successful) -> ";
		std::cout << "Find the wall planes and classify them as lateral, upper or lower. Discard those that are no valid for the model." << std::endl;
		
		std::cout << "Phase 3 (";
		if (data_out->GI_phase3.complete) std::cout  << "complete in  " << data_out->GI_phase3.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase3.complete) std::cout << "no successful) -> ";
		std::cout << "Get the line coefficients for all the horizontal intersections of the model." << std::endl;
		
		std::cout << "Phase 4 (";
		if (data_out->GI_phase4.complete) std::cout  << "complete in  " << data_out->GI_phase4.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase4.complete) std::cout << "no successful) -> ";
		std::cout << "Get a first approximation for the lateral shape of the room." << std::endl;
		
		std::cout << "Phase 5 (";
		if (data_out->GI_phase5.complete) std::cout  << "complete in  " << data_out->GI_phase5.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase5.complete) std::cout << "no successful) -> ";
		std::cout << "Identify and erase incoherent segments for the calculated lateral shape." << std::endl;
		
		std::cout << "Phase 6 (";
		if (data_out->GI_phase6.complete) std::cout  << "complete in  " << data_out->GI_phase6.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase6.complete) std::cout << "no successful) -> ";
		std::cout << "Use the lateral shape to generate the connected points that will describe the room shape." << std::endl;
		
		std::cout << "Phase 7 (";
		if (data_out->GI_phase7.complete) std::cout  << "complete in  " << data_out->GI_phase7.time / 1000 << " seconds) \t-> ";
		if (!data_out->GI_phase7.complete) std::cout << "no successful) -> ";
		std::cout << "Complete the missing connections of the connected points and create new connected points using the horizontal planes." << std::endl;
		
		
		
		//-> Connected point info
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << " - Connected points out - " << std::endl;
		PointCloudXYZConected_Tool.display_points_info(*cloudC, true);
		
		
		
		//-> Configure viewer
		if (viewer->viewer_state()){
			
			//-> Configure viewer: Get current configuration
			ViewerRT::config_parameters config;
			viewer->get_parameters(&config);

			//-> Configure viewer: Set kind of rotation
			if (rotation_enable)config.rotation_view_point.kind = 7;
			if (!rotation_enable) config.rotation_view_point.kind = 0;
			
			//-> Configure viewer: Set rotation speed
			config.rotation_view_point.degree_inc = 1;
			
			//-> Configure viewer: Set module speed
			config.rotation_view_point.module_inc = 1;
			
			//-> Configure viewer: Configure the number of windows
			config.n_windows = 1;
			config.special_3_windows = true;
			
			//-> Configure viewer: Set parameters	
			viewer->set_parameters(config, true, false);}
		
		
		//-> Load Original cloud and mesh point edge in viewer 1
		if (viewer->viewer_state()){
			//*cloud_aux =  data_out->phase1.cloud_filtered;
			*cloud_aux = data_out->cloud;
			if (!viewer->load(cloud_aux, 1, false)){
				std::cout << "Cant display cloud";}
			sleep(1);	
				
			if (!PointCloudXYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(&conected_cloud_in, cloud_aux, 0.05)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(cloud_aux, 1, 255, 0, 0, false)){
				std::cout << "Cant display cloud";}}
		

		//-> Load  point edge mesh in viewer 2	
		if (false)if (viewer->viewer_state()){
			if (!PointCloudXYZConected_Tool.PointXYZC_2_Edge_Point_Mesh(&conected_cloud_in, cloud_aux, 0.05)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(cloud_aux, 2, false)){
				std::cout << "Cant display cloud";}}		
		
		
		//-> Load polygon mesh in viewer 3	
		if (false)if (viewer->viewer_state()){
			pcl::PolygonMesh polymesh;
			if (!PointCloudXYZConected_Tool.PointXYZC_2_PolygonMesh(&conected_cloud_in, &polymesh)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(polymesh, 3, false)){
				std::cout << "Cant display cloud";}}		
				
		
		//-> Load point mesh in viewer 4	
		if (false)if (viewer->viewer_state()){
			pcl::PolygonMesh polymesh;
			if (!PointCloudXYZConected_Tool. PointXYZC_2_Point_Mesh(&conected_cloud_in, cloud_aux, 0.05, 2)){
				std::cout << "Cant convert cloud";}
			if (!viewer->load(cloud_aux, 4, false)){
				std::cout << "Cant display cloud";}}			
				
				
				
				
				
				
			
		
		
		

		getchar();
		getchar();}
	
	
#endif