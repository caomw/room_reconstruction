#ifndef ROOMSHAPEDETECTOR_HHP
#define ROOMSHAPEDETECTOR_HHP
	
	
	//**PUBLIC FUNCTIONS**//
		
		RoomShapeDetector::RoomShapeDetector (){
			//-> Initialize shell log
			sh_log = true;
			developer = false;
			
			
			//-> Declare memory space for the dynamic structure data
			process_data *data_declared (new process_data);
			data = data_declared;
		
			config_parameters *config_declared (new config_parameters);
			config = config_declared;
			
			//-> Set default configuration 
			set_default_configuration();
			
			//-> Initialize data
			initialize_stored_data();
			
			return;}
		
		
		RoomShapeDetector::~RoomShapeDetector (){
			return;}
		
		
		bool RoomShapeDetector::set_default_configuration(){
			
			if (!get_default_configuration(config)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::set_default_configuration] Failed when setting default configuration\033[0m" << std::endl;
				return(false);}	
			
			
			return(true);}	
		
		
		bool RoomShapeDetector::get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, struct config_parameters* config_in, PointCloudXYZConected* conected_cloud_out){
			*config = *config_in;
			bool process_status (manage_process(cloud_in, conected_cloud_out));
			if (!release_memory()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::get_room_shape] Failed, can't release memory\033[0m" << std::endl;}
			return(process_status);}		
		bool RoomShapeDetector::get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected* conected_cloud_out, struct process_data* data_out){
			
			developer = true;
	
			bool process_status (manage_process(cloud_in, conected_cloud_out));
			*data_out = *data;
			if (!release_memory()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::get_room_shape] Failed, can't release memory\033[0m" << std::endl;}
			return(process_status);}		
		bool RoomShapeDetector::get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, struct config_parameters* config_in,  PointCloudXYZConected* conected_cloud_out, struct process_data* data_out){
			developer = true;
			*config = *config_in;
			bool process_status (manage_process(cloud_in, conected_cloud_out));
			*data_out = *data;
			if (!release_memory()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::get_room_shape] Failed, can't release memory\033[0m" << std::endl;}
			return(process_status);}
		bool RoomShapeDetector::get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected* conected_cloud_out){
			bool process_status(manage_process(cloud_in, conected_cloud_out));
			if (!release_memory()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::get_room_shape] Failed, can't release memory\033[0m" << std::endl;}
			return(process_status);}
			
		
	
	//**PRIVATE FUCNTIONS**//
		//-> Manage process phases
		bool RoomShapeDetector::manage_process(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected* conected_cloud_out){
		
			//-> Declare objects
			pcl::console::TicToc console_time;
			
			//-> Initialize data
			initialize_stored_data();
			
			//->Set in cloud
			data->cloud = *cloud_in;
			
			
			//-> Start the process
			console_time.tic();
			if (!phase0()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 0\033[0m" << std::endl;
				return(false);}				
			data->GI_phase0.time = console_time.toc();
			
			console_time.tic();
			if (!phase1()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 1\033[0m" << std::endl;
				return(false);}				
			data->GI_phase1.time = console_time.toc();
			
			console_time.tic();
			if (!phase2()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 2\033[0m" << std::endl;
				return(false);}				
			data->GI_phase2.time = console_time.toc();
			
			console_time.tic();
			if (!phase3()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 3\033[0m" << std::endl;
				return(false);}				
			data->GI_phase3.time = console_time.toc();
			
			console_time.tic();
			if (!phase4()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 4\033[0m" << std::endl;
				return(false);}				
			data->GI_phase4.time = console_time.toc();
			
			console_time.tic();
			if (!phase5()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 5\033[0m" << std::endl;
				return(false);}	
			data->GI_phase5.time = console_time.toc();
			
			console_time.tic();
			if (!phase6()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 6\033[0m" << std::endl;
				return(false);}
			data->GI_phase6.time = console_time.toc();
			
			console_time.tic();
			if (!phase7()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::manage_process] Failed in phase 7\033[0m" << std::endl;
				return(false);}
			data->GI_phase7.time = console_time.toc();
			
			
			//-> Return data
			PointCloudXYZConected result;
			result.Points = data->phase7.reconstruction_points.Points;
			for (int i=0; i < result.size(); i++)
				result.Points[i].plane_index.clear();
				
			
			*conected_cloud_out = result;
			
			return(true);}
		
	
		//-> Initialize store data for the processes
		bool RoomShapeDetector::initialize_stored_data(){
			process_data data_declared;
			*data = data_declared;
			
			//-> initialize phase info
			phase_general_info start_data;
			start_data.complete = false;
			start_data.time = -1;
			
			data->GI_phase0 = start_data;
			data->GI_phase1 = start_data;
			data->GI_phase2 = start_data;
			data->GI_phase3 = start_data;
			data->GI_phase4 = start_data;
			data->GI_phase5 = start_data;
			data->GI_phase6 = start_data;
			data->GI_phase7 = start_data;
			
			
			//-> Initialize phase 2 info
			data->phase2.process_over_cycles = false;
			data->phase2.cloud_left_under_limit = false;
			
			return(true);}
		
		
		//-> Get default configuration
		bool RoomShapeDetector::get_default_configuration(struct config_parameters* config_out){
			
			struct config_parameters config_aux;
			
			//-> General configuration
			config_aux.general.laser_z_axis.x = 0;
			config_aux.general.laser_z_axis.y = 0;
			config_aux.general.laser_z_axis.z = 1;
			config_aux.general.laser_ref_axis.x = 1;
			config_aux.general.laser_ref_axis.y = 0;
			config_aux.general.laser_ref_axis.z = 0;
			config_aux.general.laser_origen.x = 0;
			config_aux.general.laser_origen.y = 0;
			config_aux.general.laser_origen.z = 0;
			config_aux.general.laser_xy_plane.push_back(0);
			config_aux.general.laser_xy_plane.push_back(0);
			config_aux.general.laser_xy_plane.push_back(1);
			config_aux.general.laser_xy_plane.push_back(0);
			
			
			//-> Phase 1 configuration
			config_aux.phase1.grid = 0.1;
			config_aux.phase1.min_filter_cloud = 500;
			
			
			//-> Phase 2 configuration
			config_aux.phase2.max_cycles = 800;
			config_aux.phase2.min_point_left = 30;
			config_aux.phase2.min_extracted_points = 150;
			config_aux.phase2.min_relation_SE = 4;
			
			config_aux.phase2.SACSegmentation_OptimizeCoefficients = true;
			config_aux.phase2.SACSegmentation_MaxIterations = 10000;
			config_aux.phase2.SACSegmentation_DistanceThreshold = 0.05;
			
			config_aux.phase2.Concave_Hull_Alpha = 0.5;
			
			config_aux.phase2.U_plane_angle_allowed = 0.785;
			config_aux.phase2.L_plane_angle_allowed = 2.355;
			
			
			//-> Phase 3 configuration
			config_aux.phase3.min_allowed_planes = 2;
			
			
			//-> Phase 4 configuration
			config_aux.phase4.common_filter_activate = true;
			config_aux.phase4.grid_error = 1e-8;
			config_aux.phase4.percentil = 0.25;
			config_aux.phase4.min_percentil_val = 5;
			
			
			//-> Phase 6 configuration
			config_aux.phase6.case_1_angle = 0.75 * float_PI;
			
			
			//-> Return configuration
			*config_out = config_aux;
			
			return(true);}	
		
	
		//-> Phase 0: Check if the configuration values are ok. Set the default values for the wrong values
		bool  RoomShapeDetector::phase0(){
			
			//-> Declare auxiliary object
			struct config_parameters default_config;
			get_default_configuration(&default_config);
			
			//-> General configuration
			if (config->general.laser_xy_plane.size() != 4) config->general = default_config.general;
			if (config->general.laser_z_axis.x == 0 && config->general.laser_z_axis.y == 0 && config->general.laser_z_axis.z == 0) config->general = default_config.general;
			if (config->general.laser_ref_axis.x == 0 && config->general.laser_ref_axis.y == 0 && config->general.laser_ref_axis.z == 0) config->general = default_config.general;
	
			
			//-> Phase 1
			if (config->phase1.grid < 0) config->phase1 = default_config.phase1;
			if (config->phase1.min_filter_cloud < 8) config->phase1 = default_config.phase1;
			
			
			//-> Phase 2
			if (config->phase2.max_cycles < 10) config->phase2 = default_config.phase2;
			if (config->phase2.min_point_left < 0) config->phase2 = default_config.phase2;
			if (config->phase2.min_extracted_points < 1) config->phase2 = default_config.phase2;
			if (config->phase2.min_relation_SE < 1) config->phase2 = default_config.phase2;
			if (config->phase2.SACSegmentation_MaxIterations < 1) config->phase2 = default_config.phase2;
			if (config->phase2.SACSegmentation_DistanceThreshold < 1) config->phase2 = default_config.phase2;
			if (config->phase2.Concave_Hull_Alpha < 1) config->phase2 = default_config.phase2;
			if (config->phase2.U_plane_angle_allowed  < 0 || config->phase2.U_plane_angle_allowed  > 1.1775) config->phase2 = default_config.phase2;
			if (config->phase2.L_plane_angle_allowed  > 3.14 || config->phase2.L_plane_angle_allowed  < 1.9625) config->phase2 = default_config.phase2;
	

			
			//-> Phase 3
			if (config->phase3.min_allowed_planes < 2) config->phase3 = default_config.phase3;

			
			//-> Phase 4
			if (config->phase4.grid_error < 0 || config->phase4.grid_error > 0.1) config->phase4 = default_config.phase4;
			if (config->phase4.percentil <= 0 || config->phase4.percentil > 1) config->phase4 = default_config.phase4;
			if (config->phase4.min_percentil_val < 0) config->phase4 = default_config.phase4;

			
			//-> Phase 6
			if (config->phase6.case_1_angle < (0.5)*float_PI || config->phase6.case_1_angle > (1.5)*float_PI) config->phase6 = default_config.phase6;


			
			//-> Phase 7
			
			
			data->GI_phase0.complete = true;
			return(true);}
		
		
		//-> Phase 1: Reduce the number of points in the cloud and set a lower bound of the distance between points for the next process
		bool  RoomShapeDetector::phase1(){
			//-> Get required information from other phases
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aux (new pcl::PointCloud<pcl::PointXYZ>);
			*cloud_aux = data->cloud;
			
			
			//->Declare objects
			pcl::VoxelGrid<pcl::PointXYZ> voxelgrid_filter;
			

			//->Configure filter
			voxelgrid_filter.setInputCloud (cloud_aux);
			float grid(config->phase1.grid);
			voxelgrid_filter.setLeafSize (grid, grid, grid);

			
			//-> Get filtered cloud
			voxelgrid_filter.filter (data->phase1.cloud_filtered);
			
			
			if (data->phase1.cloud_filtered.size() < config->phase1.min_filter_cloud) {
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase1] Failed, the number of points in the filter cloud is too low\033[0m" << std::endl;
				return(false);}	
			
			data->GI_phase1.complete = true;
			return(true);}
		
		
		//-> Phase 2: Find the wall planes and classify them as lateral, upper or lower. Discard those that are no valid for the model
		bool  RoomShapeDetector::phase2(){
		
			//-> Get required information from other phases
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
			*cloud_filtered = data->phase1.cloud_filtered;
			
			
			//-> Declare general objects for the phase
			bool keep_finding(true);
			int cycles(0);
			
			
			//-> check if the filtered cloud is enough
			if (cloud_filtered->size() < 8){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase2] Failed, The number of the in cloud is too low\033[0m" << std::endl;
				return(false);}	
			
			
			//-> Start man buckle
			while (keep_finding){
				
				//-> Check cycle break condition
				if (cycles++ > config->phase2.max_cycles){
					data->phase2.process_over_cycles = true;
					keep_finding = false;}
				
				//-> Check the rest of the points
				if (cloud_filtered->size() < config->phase2.min_point_left){
					data->phase2.cloud_left_under_limit = false;
					keep_finding = false;}
			
				
				//-> keep finding
				if (keep_finding){
					
					//-> Declare common objects used un the while
					pcl::PointCloud<pcl::PointXYZ>::Ptr extracted_points (new pcl::PointCloud<pcl::PointXYZ>);
					pcl::PointCloud<pcl::PointXYZ>::Ptr extracted_edge (new pcl::PointCloud<pcl::PointXYZ>);
					pcl::ExtractIndices<pcl::PointXYZ> Extract_Index;
					pcl::SACSegmentation<pcl::PointXYZ> SAC_Segmentation;
					pcl::ConcaveHull <pcl::PointXYZ> Concave_Hull;
					pcl::PointIndices::Ptr index (new  pcl::PointIndices() );
					pcl::ModelCoefficients::Ptr plane_coefficients (new pcl::ModelCoefficients() );
					PCLtools PCL_tools;
					
					
					//-> Use RANSAC object in order to find the most common plane
					SAC_Segmentation.setOptimizeCoefficients(config->phase2.SACSegmentation_OptimizeCoefficients);
					SAC_Segmentation.setModelType (pcl::SACMODEL_PLANE);
					SAC_Segmentation.setMethodType (pcl::SAC_RANSAC);
					SAC_Segmentation.setMaxIterations (config->phase2.SACSegmentation_MaxIterations); 
					SAC_Segmentation.setDistanceThreshold (config->phase2.SACSegmentation_DistanceThreshold);      
					SAC_Segmentation.setInputCloud (cloud_filtered);
					SAC_Segmentation.segment (*index, *plane_coefficients);
					
					
					//-> Check the number of the points
					if (index->indices.size() < config->phase2.min_extracted_points)
						keep_finding = false;
						
					
					if (keep_finding){	
						//Extract the points that belong to the plane (positive and negative)
						Extract_Index.setInputCloud (cloud_filtered);
						Extract_Index.setIndices (index);
						Extract_Index.setNegative (false);
						Extract_Index.filter (*extracted_points);
						
						
						//Extract the points that belong to the plane (negative)
						Extract_Index.setInputCloud (cloud_filtered);
						Extract_Index.setIndices (index);
						Extract_Index.setNegative (true);
						Extract_Index.filter (*cloud_filtered);
						
						
						//Get the Ns and Ne for the method
						Concave_Hull.setInputCloud (extracted_points);
						Concave_Hull.setDimension(2);
						Concave_Hull.setAlpha (config->phase2.Concave_Hull_Alpha);
						Concave_Hull.reconstruct(*extracted_edge);
						
						
						//Check the SE method and storing whether the relationship meets the condition
 						float NsNb ((float) extracted_points->size() / (float) extracted_edge->size());
						if (NsNb > config->phase2.min_relation_SE){
							//-> Convert coefficients
							std::vector <float> aux;
							
							if (plane_coefficients->values[3] >= 0){
								aux.push_back(plane_coefficients->values[0]);
								aux.push_back(plane_coefficients->values[1]);
								aux.push_back(plane_coefficients->values[2]);
								aux.push_back(plane_coefficients->values[3]);}
							else{
								aux.push_back( -1 * plane_coefficients->values[0]);
								aux.push_back( -1 * plane_coefficients->values[1]);
								aux.push_back( -1 * plane_coefficients->values[2]);
								aux.push_back( -1 * plane_coefficients->values[3]);}
							
							
							//-> Identify type of plane
							Plane_coef Plane_coef_aux;
							pcl::PointXYZ v2(aux[0],aux[1],aux[2]);
							float Zangle;
							if (!PCL_tools.angle_between_two_vetors(config->general.laser_z_axis, v2, &Zangle)){
								if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase2] Failed, can't calculate the Z angle\033[0m" << std::endl;
								return(false);}	
							
							if (Zangle < config->phase2.U_plane_angle_allowed){ 
								Plane_coef_aux.type = -1;}
							else if (Zangle > config->phase2.L_plane_angle_allowed){ 
								Plane_coef_aux.type = 1;}
							else{
								Plane_coef_aux.type = 0;}
							
							
							//-> Set the structure values
							Plane_coef_aux.Zangle = Zangle;
							Plane_coef_aux.valid = true;
							Plane_coef_aux.SE_relation = NsNb;
							Plane_coef_aux.a = aux[0];
							Plane_coef_aux.b = aux[1];
							Plane_coef_aux.c = aux[2];
							Plane_coef_aux.d = aux[3];
							
							
							//-> Store the all data
							data->phase2.planes.plane.push_back(Plane_coef_aux);
							data->phase2.found_plane_points.push_back(*extracted_points);	
							data->phase2.I_found_plane_points.push_back(*index);}}}}	
			
			
			//-> Discard wrong L and U planes
			float SE_relation_U(-1), SE_relation_L(-1);
			for (int i=0; i < data->phase2.planes.plane.size(); i++){
				if (data->phase2.planes.plane[i].type == 1){
					if (data->phase2.planes.plane[i].SE_relation > SE_relation_U)
						SE_relation_U = data->phase2.planes.plane[i].SE_relation;
					else{ 
						data->phase2.planes.plane[i].valid = false;}}
				
				else if (data->phase2.planes.plane[i].type == -1){
					if (data->phase2.planes.plane[i].SE_relation > SE_relation_L)
						SE_relation_L = data->phase2.planes.plane[i].SE_relation;
					else {
						data->phase2.planes.plane[i].valid = false;}}}
				
			
			//-> Check if there are one upper plane
			if (SE_relation_U < 0){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase2] Failed, no upper plane were calculated\033[0m" << std::endl;
				return(false);}				
			if (SE_relation_L < 0){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase2] Failed, no lower plane were calculated\033[0m" << std::endl;
				return(false);}	
			
			
			data->GI_phase2.complete = true;
			return(true);}
		
		
		//-> Phase 3: Get the line coefficients for all the horizontal intersections of the model
		bool  RoomShapeDetector::phase3(){
			//-> Get required information from other phases
			PointCloudXYZConected planes (data->phase2.planes);
			
			
			//-> Identify the lateral planes index
			std::vector<int> lateral_planes;
			for (int i=0; i < planes.plane.size(); i++){
				if (planes.plane[i].type == 0 && planes.plane[i].valid)
					lateral_planes.push_back(i);}
			
			
			//-> Store info
			data->phase3.lateral_planes = lateral_planes;
			
			
			//-> Check for errors
			if (lateral_planes.size() < 2){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase3] Failed, not enough planes to make the reconstruction\033[0m" << std::endl;
				return(false);}	
			
			
			//-> Get intersections
			PCLtools PCL_tools;
			std::vector <float> reference_plane;
			reference_plane = config->general.laser_xy_plane;
			
			for (int i=0; i < lateral_planes.size(); i++){
				std::vector <float> line_out;
				std::vector <float> lateral_plane;
				lateral_plane.push_back(planes.plane[lateral_planes[i]].a);
				lateral_plane.push_back(planes.plane[lateral_planes[i]].b);
				lateral_plane.push_back(planes.plane[lateral_planes[i]].c);
				lateral_plane.push_back(planes.plane[lateral_planes[i]].d);
				
				
				//-> Call PLC_Tool function
				if (!PCL_tools.inter_with_two_planes(&reference_plane, &lateral_plane, &line_out)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase3] Failed, can't get intersection coefficients for upper plane\033[0m" << std::endl;
					return(false);}	

				
				
				//->Set line structures
				line_coef line_coef_aux;
				line_coef_aux.x  = line_out[0];
				line_coef_aux.y  = line_out[1];
				line_coef_aux.z  = line_out[2];
				line_coef_aux.vx = line_out[3];
				line_coef_aux.vy = line_out[4];
				line_coef_aux.vz = line_out[5];
				line_coef_aux.plane_index.push_back(lateral_planes[i]); 
				
				
				
				//-> Store lines
				data->phase3.lines.line.push_back(line_coef_aux);}
			



			
			//-> Set complete
			data->GI_phase3.complete = true;
			return(true);}
		
		
		//-> Phase 4: Get a first approximation for the lateral shape of the room
		bool  RoomShapeDetector::phase4(){
			//-> Get required information from other phases
			PointCloudXYZConected lines (data->phase3.lines);
			PointCloudXYZConected planes (data->phase2.planes);
			std::vector<int> lateral_planes(data->phase3.lateral_planes);
			std::vector <pcl::PointCloud<pcl::PointXYZ> > found_plane_points (data->phase2.found_plane_points);
			
			
			//-> Check if the number of lateral planes is the same than the lines equations
			if (lateral_planes.size() != lines.line.size()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, the number of lateral planes is not the same that the line equations\033[0m" << std::endl;
				return(false);}		
			
			
			//-> Declare common objects
			PCLtools PCL_tools;

			
			//-> Get all projections (without filter them) and store them in "data->phase4.projections"
			for (int i=0; i < lateral_planes.size(); i++){
				
				//->Common objects 
				pcl::PointCloud<pcl::PointXYZ>::Ptr  plane_points (new pcl::PointCloud<pcl::PointXYZ>);
				pcl::ProjectInliers<pcl::PointXYZ> Project_Inliers;
				
				
				//->Common configuration
				*plane_points = found_plane_points[lateral_planes[i]];
				Project_Inliers.setInputCloud (plane_points);				
				Project_Inliers.setModelType (pcl::SACMODEL_LINE);
				
				
				//-> Load line upper model
				pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients ());
				coefficients->values.resize (6);
				coefficients->values[0] = lines.line[i].x;
				coefficients->values[1] = lines.line[i].y;
				coefficients->values[2] = lines.line[i].z;
				coefficients->values[3] = lines.line[i].vx;
				coefficients->values[4] = lines.line[i].vy;
				coefficients->values[5] = lines.line[i].vz;				
								
				
				// Project all points of the lateral "plane lateral_planes[i]"
				pcl::PointCloud<pcl::PointXYZ>::Ptr  projected_points (new pcl::PointCloud<pcl::PointXYZ>);
				Project_Inliers.setModelCoefficients (coefficients);
				Project_Inliers.filter (*projected_points);
				
				
				//-> Store the projected points
				projection st_projection;
				st_projection.projection = *projected_points;
				st_projection.plane_index.push_back(lateral_planes[i]);
				data->phase4.projections.push_back(st_projection);}
					
			
			//-> Get the percentile value for single filter value and store then in "data->phase4.filter_values"
			std::vector<int> percentile_All;
			for (int i=0; i < data->phase4.projections.size(); i++){
				
				//-> Get farthest points in the projection in order to make the sampling
				pcl::PointXYZ P1;
				pcl::PointXYZ P2;
				pcl::PointCloud<pcl::PointXYZ>::Ptr  projections (new pcl::PointCloud<pcl::PointXYZ>);
				*projections = data->phase4.projections[i].projection;
				if (!PCL_tools.Get_the_two_farthest_points(projections, &P1,&P2)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed when getting the external points of the sampling\033[0m" << std::endl;
					return(false);}		
				
				
				//-> Make the sampling. This process may be avoid, so turn off the shell alerts
				bool sampling_ok;
				bool sh_log_value = PCL_tools.sh_log;
				pcl::PointCloud<pcl::PointXYZ>::Ptr  sampling_cloud (new pcl::PointCloud<pcl::PointXYZ>);
				PCL_tools.sh_log = false;
				sampling_ok = PCL_tools.mesh_line_with_gap(P1,P2,config->phase1.grid, sampling_cloud);
				PCL_tools.sh_log = sh_log_value;
			
				
				//-> Get the number of points in each cell
				projection_density projection_denity_aux;
				pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
				kdtree.setInputCloud (projections);
				
				
				//-> Store the plane that the projection belongs
				for (int j=0; j < data->phase4.projections[i].plane_index.size(); j++)
					projection_denity_aux.plane_index.push_back(data->phase4.projections[i].plane_index[j]);
				
				
				//-> Calculate for each point the density and store it
				for (size_t j=0; j< sampling_cloud->size(); j++){
					std::vector< int > k_indices;
					std::vector< float > k_sqr_distances;
					
			
					//-> Get the density of the point
					kdtree.radiusSearch(sampling_cloud->points[j],config->phase1.grid - config->phase4.grid_error,k_indices,k_sqr_distances);
					
					
					//-> If there are points for the centre of gravity
					//if (k_indices.size() > 0 ) {
					if (true) {
						
						//-> Store the density
						projection_denity_aux.density.push_back(k_indices.size());
					
					
						//->Store the found points in a new cloud in order to get de centre of gravity point
						pcl::PointCloud<pcl::PointXYZ>::Ptr points_for_cog (new pcl::PointCloud<pcl::PointXYZ>);
						if (!PCL_tools.extract_index_from_cloud(projections, &k_indices, points_for_cog)){
							if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, can't extract the points from cloud\033[0m" << std::endl;
							return(false);}	
						
						
						//-> Get de point
						pcl::PointXYZ point_aux;
						if (points_for_cog->size() < 1){
							point_aux = sampling_cloud->points[j];}
						else{
							if (!PCL_tools.get_CDM(points_for_cog, &point_aux)){
								if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, can't get de the centre point of the sample\033[0m" << std::endl;
								return(false);}	}
						
						
						//-> Store the centre of gravity
						projection_denity_aux.projection.push_back(point_aux);}}
					
					
				//-> Store the sampling line
				data->phase4.filter_projections.push_back(projection_denity_aux);
			
				
				//-> Organize the density values in order to get the percentile. percentile_All declared in common declarations
				std::vector<int> percentile;
				if (!PCL_tools.organize_vector_descending(projection_denity_aux.density, &percentile)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, can't organize the array in order to get the percentile\033[0m" << std::endl;
					return(false);}	
				for (int j=0; j < percentile.size(); j++)
					percentile_All.push_back(percentile[j]);

				
				//-> Get percentile for single filter_value
				float percentile_position (config->phase4.percentil * percentile.size());
				if (percentile[(int)percentile_position] > config->phase4.min_percentil_val){
					data->phase4.filter_values.push_back(percentile[(int)percentile_position]);}
				else{
					data->phase4.filter_values.push_back(config->phase4.min_percentil_val);}}
				
			
			//-> Get the percentile value for common filter value and store it in "data->phase4.commnon_filter_value"
			////-> Organize the density values in order to get the percentile. percentile_All declared in common declarations
			if (!PCL_tools.organize_vector_descending(percentile_All, &percentile_All)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, can't organize the array in order to get the common percentile\033[0m" << std::endl;
				return(false);}	


			////-> Get percentile for common filter_value
			float percentile_common_position (config->phase4.percentil * percentile_All.size());
			if (percentile_All[(int)percentile_common_position] > config->phase4.min_percentil_val){
				data->phase4.commnon_filter_value = percentile_All[(int)percentile_common_position] ;}
			else{
				data->phase4.commnon_filter_value = config->phase4.min_percentil_val;}
			
			
			//-> Initialize planes of the (PointCloudXYZConected)data->phase4.segments configuration
			for (int i=0; i < planes.plane.size(); i++){
				data->phase4.segments.plane.push_back(planes.plane[i]);
				data->phase4.no_filtered_segments.plane.push_back(planes.plane[i]);}
			
			
			//-> Initialize lines of the (PointCloudXYZConected)data->phase4.segments configuration
			for (int i=0; i < lines.line.size(); i++){
				data->phase4.segments.line.push_back(lines.line[i]);
				data->phase4.no_filtered_segments.line.push_back(data->phase3.lines.line[i]);}			
			
			
			//-> filter the projections and store them in "data->phase4.segments"
			int segment_index(0);
			int nf_segment_index(0);
			for (int i=0; i < data->phase4.filter_projections.size(); i++){
				
				//-> Check errors
				if (data->phase4.filter_projections[i].density.size() != data->phase4.filter_projections[i].projection.size()){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, the density array is no equal to the point array\033[0m" << std::endl;
					return(false);}	
				
				
				//-> Initialize common PointXYZC structure
				PointXYZC conected_point_aux;
				PointXYZC conected_nf_point_aux;
				conected_point_aux.segment_index.push_back(segment_index);
				conected_nf_point_aux.segment_index.push_back(segment_index);
				
				//-> initialize the values for the index planes index and check if the plane exists
				for (int j=0; j < data->phase4.filter_projections[i].plane_index.size(); j++){
					if (data->phase4.filter_projections[i].plane_index[j] > data->phase4.segments.plane.size()){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, the related index for plane do not exists\033[0m" << std::endl;
						return(false);}	
					conected_point_aux.plane_index.push_back(data->phase4.filter_projections[i].plane_index[j]);
					conected_nf_point_aux.plane_index.push_back(data->phase4.filter_projections[i].plane_index[j]);}
				
				
				//-> Initialize the common value for the index line and check if the line index exists
				conected_point_aux.line_index.push_back(i); 
				conected_nf_point_aux.line_index.push_back(i); 
				if (i > data->phase4.segments.line.size()){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, the related index for line do not exists\033[0m" << std::endl;
					return(false);}	
				
				
				//-> Get filter value (threshold)
				int filter_value;
				if (config->phase4.common_filter_activate){
					filter_value = data->phase4.commnon_filter_value;}
				else{
					filter_value = data->phase4.filter_values[i];}
				
				
				//-> Check. The line structure should have just one plane associated
				if (data->phase4.segments.line[i].plane_index.size() != 1){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase4] Failed, the line structure should belong to one plane\033[0m" << std::endl;
					return(false);}	
				
				
				//-> Go through the projection density Create segment with those where the density is over de density threshold
				bool new_segment(true);
				bool new_nf_segment(true);
				segment_description segment_desc;
				segment_desc.plane_index.push_back(data->phase4.segments.line[i].plane_index[0]);
				segment_description segment_nf_desc;
				segment_nf_desc.plane_index.push_back(data->phase4.segments.line[i].plane_index[0]);
				int temp_density_val;
				int start_point_index;
				int end_point_index;				
				int start_nf_point_index;
				int end_nf_point_index;
				int segment_denity(0);
				int segment_denity_counter(0);
				int nf_segment_denity(0);
				int nf_segment_denity_counter(0);
				
				
				for (int j=0; j< data->phase4.filter_projections[i].density.size(); j++){
				
					//-> For the start of the segment
					if (new_segment && data->phase4.filter_projections[i].density[j] > filter_value){
						
						//-> Store density
						segment_denity = segment_denity + data->phase4.filter_projections[i].density[j];
						segment_denity_counter++;
						
						//-> Store the point in the structure
						conected_point_aux.p = data->phase4.filter_projections[i].projection.points[j];
						conected_point_aux.segment_index[0] = segment_index;
						start_point_index = data->phase4.segments.size();
						
						
						//-> Set start segment info
						segment_desc.start_point = data->phase4.filter_projections[i].projection.points[j];

						
						
						//-> Turn off look for the start of the segment 
						new_segment = false;
						
						
						//-> Store 
						data->phase4.segments.Points.push_back(conected_point_aux);
						
						
						//-> Clear index connexions
						conected_point_aux.linear_conexion_index.clear();}
					
					
					//-> For the end of the segment, store the segment
					if (!new_segment && (data->phase4.filter_projections[i].density[j] <= filter_value || j == data->phase4.filter_projections[i].density.size()-1)){
						//-> Generate density
						float float_density;
						float_density = segment_denity / segment_denity_counter;
						segment_denity = (int) float_density;
						segment_denity_counter = 0;
						segment_desc.density = segment_denity;
						segment_denity = 0;
						
						//-> Store the point in the structure
						conected_point_aux.p = data->phase4.filter_projections[i].projection.points[j-1];
						conected_point_aux.segment_index[0] = segment_index;
						conected_point_aux.linear_conexion_index.push_back(start_point_index);
						end_point_index = data->phase4.segments.size();
						
						
						//-> Set start segment info
						segment_desc.end_point = data->phase4.filter_projections[i].projection.points[j-1];
						
						
						//-> Turn off look for the start of the segment 
						new_segment = true;
						segment_index++;
						
						
						//-> Store 
						data->phase4.segments.segment.push_back(segment_desc);
						data->phase4.segments.Points.push_back(conected_point_aux);
						
						
						//-> Set the connexion for the start point
						data->phase4.segments.Points[start_point_index].linear_conexion_index.push_back(end_point_index);
						
						
						//-> Clear index connexions
						conected_point_aux.linear_conexion_index.clear();}
						
						
					//-> For the start of the non filtered segment
					if (new_nf_segment && data->phase4.filter_projections[i].density[j] > 2 && data->phase4.filter_projections[i].density[j] <= filter_value){
						
						//-> Store density
						nf_segment_denity = nf_segment_denity + data->phase4.filter_projections[i].density[j];
						nf_segment_denity_counter++;
						
						//-> Store the point in the structure
						conected_nf_point_aux.p = data->phase4.filter_projections[i].projection.points[j];
						conected_nf_point_aux.segment_index[0] = nf_segment_index;
						start_nf_point_index = data->phase4.no_filtered_segments.size();
						
						
						//-> Set start segment info
						segment_nf_desc.start_point = data->phase4.filter_projections[i].projection.points[j];

						
						
						//-> Turn off look for the start of the segment 
						new_nf_segment = false;
						
						
						//-> Store 
						data->phase4.no_filtered_segments.Points.push_back(conected_nf_point_aux);
						
						
						//-> Clear index connexions
						conected_nf_point_aux.linear_conexion_index.clear();}
					
					
					//-> For the end of the non filtered segment, store the segment
					if (!new_nf_segment && (data->phase4.filter_projections[i].density[j] <= 2  || j == data->phase4.filter_projections[i].density.size()-1 || data->phase4.filter_projections[i].density[j] > filter_value )){
						//-> Generate density
						float float_density;
						float_density = nf_segment_denity / nf_segment_denity_counter;
						nf_segment_denity = (int) float_density;
						nf_segment_denity_counter = 0;
						segment_nf_desc.density = nf_segment_denity;
						nf_segment_denity = 0;
						
						
						
						//-> Store the point in the structure
						conected_nf_point_aux.p = data->phase4.filter_projections[i].projection.points[j-1];
						conected_nf_point_aux.segment_index[0] = nf_segment_index;
						conected_nf_point_aux.linear_conexion_index.push_back(start_nf_point_index);
						end_nf_point_index = data->phase4.no_filtered_segments.size();
						
						
						//-> Set start segment info
						segment_nf_desc.end_point = data->phase4.filter_projections[i].projection.points[j-1];
						
						
						//-> Turn off look for the start of the segment 
						new_nf_segment = true;
						nf_segment_index++;
						
						
						//-> Store 
						data->phase4.no_filtered_segments.segment.push_back(segment_nf_desc);
						data->phase4.no_filtered_segments.Points.push_back(conected_nf_point_aux);
						
						
						//-> Set the connexion for the start point
						data->phase4.no_filtered_segments.Points[start_nf_point_index].linear_conexion_index.push_back(end_nf_point_index);
						
						
						//-> Clear index connexions
						conected_nf_point_aux.linear_conexion_index.clear();}}}	
															
						
									
	
			//-> Set phase as complete
			data->GI_phase4.complete = true;
			return(true);}
		
		
		//-> Phase 5: Identify and erase incoherent segments for the calculated lateral shape
		bool  RoomShapeDetector::phase5(){
			
			//-> Get required information from other phases
			data->phase5.initial_segments = data->phase4.segments;
			
			
			//->Declare common objects
			PCLtools PCL_tools;
			PointCloudXYZConectedTool PointCloudXYZConected_Tool;
			
			
			//-> Index to delete
			std::vector <int> index_to_delete;
			std::vector <int> segments_to_delete;
			
			//-> Check data
			if (data->phase5.initial_segments.size() < 4){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, the given number of connected points is too low\033[0m" << std::endl;
				return(false);}			
			
			
			//-> Check data
			if (data->phase5.initial_segments.segment.size() != data->phase5.initial_segments.size() / 2){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, the number of segments is not correct\033[0m" << std::endl;
				return(false);}		
						

			//-> Get the angles and references
			std::vector <pcl::PointXYZ> references;
			std::vector <double> end_angles;
			for (int i=0; i < data->phase5.initial_segments.segment.size(); i++){
				
				//-> Check if the segment belongs to one plane
				if (data->phase5.initial_segments.segment[i].plane_index.size() != 1){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, the segment should belong to one plane\033[0m" << std::endl;
					return(false);}		

				
				pcl::PointXYZ end1 (data->phase5.initial_segments.segment[i].start_point);
				pcl::PointXYZ end2 (data->phase5.initial_segments.segment[i].end_point);
				
				double angle;
				pcl::PointXYZ reference (end1);
				pcl::PointXYZ end (end2);
				if (!PCL_tools.full_angle_between_two_vetors(reference, end, config->general.laser_origen, &angle)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't the the angle\033[0m" << std::endl;
					return(false);}						
				
				
				if (angle >= double_PI){
					reference = end2;
					end = end1;
					if (!PCL_tools.full_angle_between_two_vetors(reference, end, config->general.laser_origen, &angle)){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't the the angle\033[0m" << std::endl;
						return(false);}}
				
				references.push_back(reference);
				end_angles.push_back(angle);}
			
			
			//Check errors
			if (references.size() != end_angles.size()){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, the size of the array references and angles are not equal\033[0m" << std::endl;
					return(false);}		

			
			//-> look for incoherent segments
			for (int i=0; i < data->phase5.initial_segments.size(); i++){
				
				//-> Check, the connected points should belong just to one segment
				if (data->phase5.initial_segments.Points[i].segment_index.size() != 1){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, the connected index should belong just to one segment\033[0m" << std::endl;
					return(false);}	
				
				
				//-> Check, the connected points should belong just to one plane
				if (data->phase5.initial_segments.Points[i].plane_index.size() != 1){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, the connected index should belong just to one plane\033[0m" << std::endl;
					return(false);}	
				
				
				//-> Check if the segment of the point has been eliminated
				bool keep_searching;
				keep_searching = true;
				for (int j=0; j < segments_to_delete.size(); j++){
					if (segments_to_delete[j] ==  data->phase5.initial_segments.Points[i].segment_index[0])
						keep_searching = false;}
					
				
				
				//-> Check the connected point with all the segments, avoid id the point belong to a point that has been eliminated
				if (keep_searching) for (int j=0; j < references.size(); j++){
					
					
					//-> Check if the segment has been removed
					keep_searching = true;
					for (int k=0; k < segments_to_delete.size()	; k++){
						if (segments_to_delete[k] == j)
							keep_searching = false;}
						
					
					//-> Avoid if the connected point belongs to segment or if the segment has been eliminated
					if (keep_searching) if (data->phase5.initial_segments.Points[i].segment_index[0] != j){
					
						//-> Get angle
						double angle;
						if (!PCL_tools.full_angle_between_two_vetors(references[j], data->phase5.initial_segments.Points[i].p, config->general.laser_origen, &angle)){
							if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't the the angle\033[0m" << std::endl;
							return(false);}	
						
						

						
						//-> Check if the connected point is incoherent
						if (angle < end_angles[j]){
							
							//-> Get the distance between the connection point and the laser
							double connection_point_distance;
							pcl::PointXYZ connection_point_vector(data->phase5.initial_segments.Points[i].p);
							if (!PCL_tools.vector_module(connection_point_vector, config->general.laser_origen, &connection_point_distance)){
								if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't get distance to the connected point\033[0m" << std::endl;
								return(false);}	
							
							
							//-> Get the intersection line
							std::vector<float> int_line;
							int_line.push_back(config->general.laser_origen.x);
							int_line.push_back(config->general.laser_origen.y);
							int_line.push_back(config->general.laser_origen.z);
							int_line.push_back(connection_point_vector.x);
							int_line.push_back(connection_point_vector.y);
							int_line.push_back(connection_point_vector.z);
							
							
							//-> Identify the plane of the segment and extract its coefficients
							int segment_plane_index(data->phase5.initial_segments.segment[j].plane_index[0]);
							std::vector<float> segment_plane_coeff;
							segment_plane_coeff.push_back(data->phase5.initial_segments.plane[segment_plane_index].a);
							segment_plane_coeff.push_back(data->phase5.initial_segments.plane[segment_plane_index].b);
							segment_plane_coeff.push_back(data->phase5.initial_segments.plane[segment_plane_index].c);
							segment_plane_coeff.push_back(data->phase5.initial_segments.plane[segment_plane_index].d);
							
							
							//-> Get the intersection between the line an the segment plane
							pcl::PointXYZ segment_point;
							if (!PCL_tools.inter_with_line_and_plane(segment_plane_coeff, int_line, &segment_point)){
								if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't get intersection point with the segment\033[0m" << std::endl;
								return(false);}	
							
							
							//-> Get the distance between the intersection and the laser
							double segment_point_distance;
							pcl::PointXYZ segment_point_vector(segment_point);
							if (!PCL_tools.vector_module(segment_point_vector, config->general.laser_origen, &segment_point_distance)){
								if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't get distance to the segment point\033[0m" << std::endl;
								return(false);}	
							
							
							//-> Identify the segment to delete
							int segment_to_delete_index;
							if (connection_point_distance < segment_point_distance){
								segment_to_delete_index = data->phase5.initial_segments.Points[i].segment_index[0];
								segments_to_delete.push_back(segment_to_delete_index);}	
							else {
								segment_to_delete_index = j;
								segments_to_delete.push_back(segment_to_delete_index);}							
							
							
							//-> Identify the index of the point that must be deleted_index
							for (int k=0; k < data->phase5.initial_segments.size(); k++){
								if (data->phase5.initial_segments.Points[k].segment_index[0] == segment_to_delete_index)
									index_to_delete.push_back(k);}}}}}
			
			
			//-> Delete duplicated for index
			if (!PCL_tools.delete_duplicated_values(index_to_delete, &index_to_delete)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't delete duplicated values\033[0m" << std::endl;
				return(false);}	
			data->phase5.deleted_index = index_to_delete;
			
			
			//-> Delete duplicated for index
			if (!PCL_tools.delete_duplicated_values(segments_to_delete, &segments_to_delete)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't delete duplicated values\033[0m" << std::endl;
				return(false);}	
			data->phase5.deleted_segments = segments_to_delete;
			
			
			//-> Delete incoherences
			PointCloudXYZConected aux_conected_cloud_in (data->phase5.initial_segments);
			PointCloudXYZConected aux_conected_cloud_out;
			if (!PointCloudXYZConected_Tool.extract_index_from_pointcloudXYZC(&aux_conected_cloud_in, &index_to_delete, &aux_conected_cloud_out, true)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase5] Failed, can't eliminate the incoherent index\033[0m" << std::endl;
				return(false);}		
			
			
			//-> Store the new segments
			data->phase5.segments = aux_conected_cloud_out;
			
			
			data->GI_phase5.complete = true;
			return(true);}
		
		
		//-> Phase 6: Use the lateral shape to generate the connected points that will describe the room shape
		bool  RoomShapeDetector::phase6(){
			
			//-> Get required information from other phases
			PointCloudXYZConected segments (data->phase5.segments);
			
			
			//-> Declare general objects
			PCLtools PCL_tools;
			PointCloudXYZConectedTool PointCloudXYZConected_Tool;
	
			
			//-> Generate the lateral plane combinations
			std::vector<int> point_index;
			std::vector<int> plane_index;
			std::vector<double> segment_angle;	
			if (segments.size() < 1){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, there is not connected points\033[0m" << std::endl;
				return(false);}			
			pcl::PointXYZ reference (segments.Points[0].p);
			for (int i=0; i < segments.size(); i++){
				double angle;
				if (!PCL_tools.full_angle_between_two_vetors(reference, segments.Points[i].p, config->general.laser_origen, &angle)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't the the angle\033[0m" << std::endl;
					return(false);}		
				segment_angle.push_back(angle);
				point_index.push_back(i);
				if (segments.Points[i].plane_index.size() != 1){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, the plane index size is not correct\033[0m" << std::endl;
					return(false);}		
				plane_index.push_back(segments.Points[i].plane_index[0]);}
				
			
			//-> Organize arrays by the angle
			if (!PCL_tools.organize_vector_ascending(point_index, segment_angle, &point_index)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't organize array\033[0m" << std::endl;
				return(false);}	
			if (!PCL_tools.organize_vector_ascending(plane_index, segment_angle, &plane_index)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't organize array\033[0m" << std::endl;
				return(false);}	
			if (!PCL_tools.organize_vector_ascending(segment_angle, &segment_angle)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't organize array\033[0m" << std::endl;
				return(false);}	
			

			//-> Get the plane sequence
			std::vector <int> plane_sequence;
			std::vector <int> A_point_index;
			std::vector <int> B_point_index;
			if (plane_index.size() < 1){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, the size of the array is not OK\033[0m" << std::endl;
				return(false);}
			int last_secuence(plane_index[0]);
			for (int i=0; i < plane_index.size(); i++){
				if (plane_index[i] != last_secuence){
					A_point_index.push_back(point_index[i]);
					B_point_index.push_back(point_index[i-1]);
					plane_sequence.push_back(plane_index[i]);
					last_secuence = plane_index[i];}}
			if (plane_index.front() != plane_index.back()){
				plane_sequence.push_back(plane_index.front());
				A_point_index.push_back(point_index.back());
				B_point_index.push_back(point_index.front());}
				

			//-> Check
			if (plane_sequence.size() < 3){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, there is not enough planes to continue the reconstruction\033[0m" << std::endl;
				return(false);}	
					
			
			//-> Store data
			data->phase6.plane_sequence = plane_sequence;
			
		
			//-> Initialize connection point data
			data->phase6.reconstruction_points.plane = segments.plane;
			
			
			//-> Identify the line direction
			int num_lower_planes(0);
			int lower_plane_index;
			pcl::PointXYZ line_direction;
			for (int i=0; i < data->phase6.reconstruction_points.plane.size(); i++){
				if (data->phase6.reconstruction_points.plane[i].type == -1){
					num_lower_planes++;
					lower_plane_index = i;}}
			if (num_lower_planes == 1){
				line_direction.x = data->phase6.reconstruction_points.plane[lower_plane_index].a;
				line_direction.y = data->phase6.reconstruction_points.plane[lower_plane_index].b;
				line_direction.z = data->phase6.reconstruction_points.plane[lower_plane_index].c;}
			else{
				line_direction.x = config->general.laser_xy_plane[0];
				line_direction.y = config->general.laser_xy_plane[1];
				line_direction.z = config->general.laser_xy_plane[2];}
						

			//-> Generate lines coefficients
			for (int i=0; i < plane_sequence.size(); i++){
				//-> Set plane index
				int plane_index_A;
				if (i == 0) plane_index_A = plane_sequence[plane_sequence.size()-1];
				else plane_index_A = plane_sequence [i-1];
				int plane_index_B(plane_sequence[i]);
				
				
				//-> Get point sequence
				int plane_index_A_point_index(A_point_index[i]);
				int plane_index_B_point_index(B_point_index[i]);
		
		
				//Get coefficient
				std::vector<float> plane_A;
				plane_A.push_back(segments.plane[plane_index_A].a);
				plane_A.push_back(segments.plane[plane_index_A].b);
				plane_A.push_back(segments.plane[plane_index_A].c);
				plane_A.push_back(segments.plane[plane_index_A].d);				
				std::vector<float> plane_B;
				plane_B.push_back(segments.plane[plane_index_B].a);
				plane_B.push_back(segments.plane[plane_index_B].b);
				plane_B.push_back(segments.plane[plane_index_B].c);
				plane_B.push_back(segments.plane[plane_index_B].d);				

				
				//-> Compare the normal angle of the planes
				float angle;
				pcl::PointXYZ n1(plane_A[0], plane_A[1], plane_A[2]);
				pcl::PointXYZ n2(plane_B[0], plane_B[1], plane_B[2]);
				if (!PCL_tools.angle_between_two_vetors(n1, n2, &angle)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't get the angle between the normals of the planes\033[0m" << std::endl;
					return(false);}	
				

				//-> Set the case of the segments
				int case_solution(-1);
				
				
				//-> CASE 1. The angle is hight than the case_1_angle, the laser is between the planes.
				if (angle >= config->phase6.case_1_angle){
					
					//-> Get lines with the segments ends
					case_solution = 1;}
				
				
				//-> The angle is lower than the case_1_angle, The planes are in the same size of the laser.
				else {
					
					//-> Get the intersection between the three planes (two consecutive laterals planes and reference XY plane)
					pcl::PointXYZ intersection;
					
					//-> CASE 1. The intersection can't be calculated
					bool sh_log (PCL_tools.sh_log);
					PCL_tools.sh_log = false;
					if (!PCL_tools.inter_with_three_planes (plane_A, plane_B, config->general.laser_xy_plane, &intersection)){
						//-> Restore the log status
						PCL_tools.sh_log = sh_log;
						
							
						//-> Set the solution case
						case_solution = 1;}
					
					
					//-> The intersection can be calculated.
					else{
						//-> Restore the log status
						PCL_tools.sh_log = sh_log;
						
						
						//-> Get laser angles and intersection angles, use as reference laser1
						double gap_angle;
						pcl::PointXYZ reference(segments.Points[plane_index_A_point_index].p);
						if (!PCL_tools.full_angle_between_two_vetors(reference, segments.Points[plane_index_B_point_index].p, config->general.laser_origen, &gap_angle)){
							if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't the the angle\033[0m" << std::endl;
							return(false);}	
						if (gap_angle > double_PI){
							reference = segments.Points[plane_index_B_point_index].p;
							if (!PCL_tools.full_angle_between_two_vetors(reference, segments.Points[plane_index_A_point_index].p, config->general.laser_origen, &gap_angle)){
								if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't the the angle\033[0m" << std::endl;
								return(false);}	}
							
						//-> Get the angle for the intersection
						double inter_angle;
						if (!PCL_tools.full_angle_between_two_vetors(reference,intersection, config->general.laser_origen, &inter_angle)){
							if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't the the angle\033[0m" << std::endl;
							return(false);}	
						
						//-> CASE 2. The inter5secion is coherent
						if (gap_angle >= inter_angle) case_solution = 2;
						
						//-> CASE 1. The intersection is not coherent
						else case_solution = 1;}}
					
				
				//-> Get the solution for the select case 1
				if (case_solution == 1){
					
				
					
					//-> Generate the lines
					line_coef line_coef_solution1;
					line_coef_solution1.plane_index.push_back(plane_index_A);
					line_coef_solution1.x = segments.Points[plane_index_A_point_index].p.x;
					line_coef_solution1.y = segments.Points[plane_index_A_point_index].p.y;
					line_coef_solution1.z = segments.Points[plane_index_A_point_index].p.z;
					line_coef_solution1.vx = line_direction.x;
					line_coef_solution1.vy = line_direction.y;
					line_coef_solution1.vz = line_direction.z;					
					
					line_coef line_coef_solution2;
					line_coef_solution2.plane_index.push_back(plane_index_B);
					line_coef_solution2.x = segments.Points[plane_index_B_point_index].p.x;
					line_coef_solution2.y = segments.Points[plane_index_B_point_index].p.y;
					line_coef_solution2.z = segments.Points[plane_index_B_point_index].p.z;
					line_coef_solution2.vx = line_direction.x;
					line_coef_solution2.vy = line_direction.y;
					line_coef_solution2.vz = line_direction.z;
					
					
					//-> Store the solution 1
					data->phase6.V_lines.line.push_back(line_coef_solution1);
					data->phase6.V_lines.line.push_back(line_coef_solution2);}
								
				
				//-> Get the solution for the select case 2. The solution will be calculated with the intersection of the two planes
				else if (case_solution == 2){
					//-> Get the solution
					std::vector<float> solution;
					if (!PCL_tools.inter_with_two_planes (plane_A, plane_B, &solution)){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't get the intersection with the two planes\033[0m" << std::endl;
						return(false);}	
					
					
					//-> Convert the solution 
					line_coef line_coef_solution;
					if (!PointCloudXYZConected_Tool.vector_coefficients_2_line_coef(solution, &line_coef_solution)){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't convert the solution\033[0m" << std::endl;
						return(false);}	
					line_coef_solution.plane_index.push_back(plane_index_A);
					line_coef_solution.plane_index.push_back(plane_index_B);
					
					
					//-> Store the solution
					data->phase6.V_lines.line.push_back(line_coef_solution);}
					
									
					
				//-> Get the solution for the select case 1
				else {
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, there is not selected case for the solution\033[0m" << std::endl;
					return(false);}	}
					

			//-> Identify the no lateral planes	
			std::vector <int> non_lateral_planes;
			for (int i=0; i < segments.plane.size(); i++){
				if (segments.plane[i].type != 0 && segments.plane[i].valid)
					non_lateral_planes.push_back(i);}	
			
			
			//-> Generate the connected reconstruction points with the line-plane intersection 
			for (int i=0; i < data->phase6.V_lines.line.size(); i++){
			
				//-> Generate the connected points
				PointCloudXYZConected Temp_PointConected;
				Temp_PointConected.plane = segments.plane;
				for (int j=0; j < non_lateral_planes.size(); j++){
					//-> Get line coefficients
					std::vector<float> line_coeff;
					if (!PointCloudXYZConected_Tool.line_coef_2_vector_coefficients(data->phase6.V_lines.line[i], &line_coeff)){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't convert line structure\033[0m" << std::endl;
						return(false);}	
					
					
					//-> Get plane coefficients
					std::vector<float> plane_coeff;
					if (!PointCloudXYZConected_Tool.PlaneCoef_2_vector_coefficients(segments.plane[non_lateral_planes[j]], &plane_coeff)){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't convert plane structure\033[0m" << std::endl;
						return(false);}	
					
					
					//-> Get intersection
					pcl::PointXYZ reconstruction_point;
					if (!PCL_tools.inter_with_line_and_plane(plane_coeff, line_coeff, &reconstruction_point)){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't get the reconstruction point\033[0m" << std::endl;
						return(false);}		
				
					
					//->Generate the connected point
					PointXYZC New_PointXYZC;
					New_PointXYZC.p = reconstruction_point;
					New_PointXYZC.plane_index.push_back(non_lateral_planes[j]);
					for (int k=0; k < data->phase6.V_lines.line[i].plane_index.size(); k++)
						New_PointXYZC.plane_index.push_back(data->phase6.V_lines.line[i].plane_index[k]);
					
					
					//-> Store in a temporal point cloud
					Temp_PointConected.Points.push_back(New_PointXYZC);}
					
				
				//-> Check
				if (Temp_PointConected.size() < 2){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, the number of connected points is not correct\033[0m" << std::endl;
					return(false);}	
			
				
				//-> Case of only two points
				else if (Temp_PointConected.size() == 2){
					//-> Store the selected points
					Temp_PointConected.Points[0].linear_conexion_index.push_back(data->phase6.reconstruction_points.size()+1);
					Temp_PointConected.Points[1].linear_conexion_index.push_back(data->phase6.reconstruction_points.size());
					data->phase6.reconstruction_points.Points.push_back(Temp_PointConected.Points[0]);
					data->phase6.reconstruction_points.Points.push_back(Temp_PointConected.Points[1]);}
				
				
				//-> Case of only one point
				else if (Temp_PointConected.size() == 1){
					data->phase6.reconstruction_points.Points.push_back(Temp_PointConected.Points[0]);}
				
				
				//-> Case of more than two points
				else if (Temp_PointConected.size() > 2){
					int index1;
					int index2;
					std::vector< std::vector <int> > match_exceptions;
					std::vector <int> upper_points;
					std::vector <int> lower_points;
					pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud (new pcl::PointCloud<pcl::PointXYZ>);
					for (int j=0; j < Temp_PointConected.size(); j++){
						temp_cloud->push_back(Temp_PointConected.Points[j].p);
										
						//-> Check the plane status
						if (!Temp_PointConected.CheckPointPlaneIndexStatus()){
							if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, the plane status is not ok\033[0m" << std::endl;
							return(false);}	
						
						
						//-> Classify the plane
						for (int k=0; k < Temp_PointConected.Points[j].plane_index.size(); k++){
							int plane_index(Temp_PointConected.Points[j].plane_index[k]);
							if (Temp_PointConected.plane[plane_index].type == 1 && Temp_PointConected.plane[plane_index].valid) upper_points.push_back(j);
							else if (Temp_PointConected.plane[plane_index].type == -1 && Temp_PointConected.plane[plane_index].valid) lower_points.push_back(j);
							}}		
					match_exceptions.push_back(upper_points);
					match_exceptions.push_back(lower_points);	
					if (!PCL_tools.Get_the_two_closest_points(temp_cloud, match_exceptions, &index1, &index2)){
						if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase6] Failed, can't identify the closest points\033[0m" << std::endl;
						return(false);}	
					
				
					//-> Store the selected points
					Temp_PointConected.Points[index1].linear_conexion_index.push_back(data->phase6.reconstruction_points.size()+1);
					Temp_PointConected.Points[index2].linear_conexion_index.push_back(data->phase6.reconstruction_points.size());
					data->phase6.reconstruction_points.Points.push_back(Temp_PointConected.Points[index1]);
					data->phase6.reconstruction_points.Points.push_back(Temp_PointConected.Points[index2]);}}
		
			
			data->GI_phase6.complete = true;
			return(true);}
		
		
		//-> Phase 7: Complete the missing connections of the connected points and create new connected points using the horizontal planes
		bool  RoomShapeDetector::phase7(){

			//-> Get required information
			data->phase7.reconstruction_points = data->phase6.reconstruction_points;
			
			
			//-> Declare common objects
			PCLtools PCL_tools;
			PointCloudXYZConectedTool PointCloudXYZConected_Tool;
			
			
			//-> Get upper and lower planes index
			for (int i=0; i < data->phase7.reconstruction_points.size(); i++){
				
				bool upper_plane(false);
				bool lower_plane(false);
				for (int j=0; j < data->phase7.reconstruction_points.Points[i].plane_index.size(); j++){
					int plane_index(data->phase7.reconstruction_points.Points[i].plane_index[j]);
					
					if (data->phase7.reconstruction_points.plane[plane_index].type == 1 && data->phase7.reconstruction_points.plane[plane_index].valid)
						upper_plane = true;
					if (data->phase7.reconstruction_points.plane[plane_index].type == -1 && data->phase7.reconstruction_points.plane[plane_index].valid)
						lower_plane = true;
						
					}
				
				
				//-> Check
				if (upper_plane && lower_plane){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, the same plane can't belong to an upper and a lower plane at the same time\033[0m" << std::endl;
					return(false);}					
				if (!upper_plane && !lower_plane){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, the plane must belong to one upper or lower plane\033[0m" << std::endl;
					return(false);}	
				
				
				//->Save index
				if (upper_plane){
					data->phase7.upper_points_index.push_back(i);}
					
					
				if (lower_plane){
					data->phase7.lower_points_index.push_back(i);}}
			
			
			//-> Check the number of points
			if (data->phase7.upper_points_index.size() < 3){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, there is not enough upper points to continue\033[0m" << std::endl;
				return(false);}				
			if (data->phase7.lower_points_index.size() < 3){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, there is not enough lower points to continue\033[0m" << std::endl;
				return(false);}	

			
			//-> Create the project object
			pcl::ProjectInliers<pcl::PointXYZ> Project_Inliers;				
			Project_Inliers.setModelType (pcl::SACMODEL_PLANE);
				
			
			//-> Load plane model
			pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients ());
			coefficients->values.resize (4);
			coefficients->values[0] = config->general.laser_xy_plane[0];
			coefficients->values[1] = config->general.laser_xy_plane[1];
			coefficients->values[2] = config->general.laser_xy_plane[2];
			coefficients->values[3] = config->general.laser_xy_plane[3];
			Project_Inliers.setModelCoefficients (coefficients);			
			

			//-> Get the points in order to project
			pcl::PointCloud<pcl::PointXYZ>::Ptr Projected_upper_points (new pcl::PointCloud<pcl::PointXYZ>);
			for (int i=0; i < data->phase7.upper_points_index.size(); i++){
				Projected_upper_points->push_back(data->phase7.reconstruction_points.Points[data->phase7.upper_points_index[i]].p);}			
			
			pcl::PointCloud<pcl::PointXYZ>::Ptr Projected_lower_points (new pcl::PointCloud<pcl::PointXYZ>);
			for (int i=0; i < data->phase7.lower_points_index.size(); i++){
				Projected_lower_points->push_back(data->phase7.reconstruction_points.Points[data->phase7.lower_points_index[i]].p);}
			
			
			//-> Project points upper and lower points
			Project_Inliers.setInputCloud (Projected_upper_points);
			Project_Inliers.filter (*Projected_upper_points);			
			Project_Inliers.setInputCloud (Projected_lower_points);
			Project_Inliers.filter (*Projected_lower_points);
			
			
			
			//-> Check
			if (Projected_upper_points->size() < 3){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, there is not enough upper points to continue\033[0m" << std::endl;
				return(false);}			
			if (Projected_lower_points->size() < 3){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, there is not enough upper points to continue\033[0m" << std::endl;
				return(false);}
			
			
			//-> Get the upper angles of the points
			std::vector<double> upper_angles;
			pcl::PointXYZ upper_reference (Projected_upper_points->points[0]);
			for (int i=0; i < Projected_upper_points->size(); i++){
				double angle;
				pcl::PointXYZ point(Projected_upper_points->points[i]);
				if (!PCL_tools.full_angle_between_two_vetors(upper_reference, point, config->general.laser_origen, &angle)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, can't the the angle\033[0m" << std::endl;
					return(false);}
				upper_angles.push_back(angle);}
				

			//-> Get the lower angles of the points
			std::vector<double> lower_angles;
			pcl::PointXYZ lower_reference (Projected_lower_points->points[0]);
			for (int i=0; i < Projected_lower_points->size(); i++){
				double angle;
				pcl::PointXYZ point(Projected_lower_points->points[i]);
				if (!PCL_tools.full_angle_between_two_vetors(lower_reference, point, config->general.laser_origen, &angle)){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, can't the the angle\033[0m" << std::endl;
					return(false);}					
				lower_angles.push_back(angle);}
			
			
			//->Order the points by angles
			std::vector<int> organized_upper_points_index;
			if (!PCL_tools.organize_vector_ascending(data->phase7.upper_points_index, upper_angles, &organized_upper_points_index)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, can't organize the array\033[0m" << std::endl;
				return(false);}				
			data->phase7.upper_points_index = organized_upper_points_index;
			
				
			std::vector<int> organized_lower_points_index;
			if (!PCL_tools.organize_vector_ascending(data->phase7.lower_points_index, lower_angles, &organized_lower_points_index)){
				if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, can't organize the array\033[0m" << std::endl;
				return(false);}	
			data->phase7.lower_points_index = organized_lower_points_index;	
			
			
			//-> Generate the upper connexions
			for (int j, i(0); i < data->phase7.upper_points_index.size(); i++){
				if (i==0) j = data->phase7.upper_points_index.size()-1;
				else j = i-1;
				
				//-> Point index
				int index_A(data->phase7.upper_points_index[i]);
				int index_B(data->phase7.upper_points_index[j]);
	
				
				//-> Get the upper index plane
				int upper_planeA(-1);
				for (int k=0; k < data->phase7.reconstruction_points.Points[index_A].plane_index.size(); k++){
					int plane_index(data->phase7.reconstruction_points.Points[index_A].plane_index[k]);
					if (data->phase7.reconstruction_points.plane[plane_index].type == 1 && data->phase7.reconstruction_points.plane[plane_index].valid)
						upper_planeA = plane_index;}
					
				int upper_planeB(-1);
				for (int k=0; k < data->phase7.reconstruction_points.Points[index_B].plane_index.size(); k++){
					int plane_index(data->phase7.reconstruction_points.Points[index_B].plane_index[k]);
					if (data->phase7.reconstruction_points.plane[plane_index].type == 1 && data->phase7.reconstruction_points.plane[plane_index].valid)
						upper_planeB = plane_index;}
				
				
				//-> Check
				if (upper_planeA == -1 && upper_planeB == -1){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, the plane index is not ok\033[0m" << std::endl;
					return(false);}
					
				
				//-> Case of same index: Generate connexion between points
				if (upper_planeA == upper_planeB){
					data->phase7.reconstruction_points.Points[index_A].linear_conexion_index.push_back(index_B);
					data->phase7.reconstruction_points.Points[index_B].linear_conexion_index.push_back(index_A);}
				
				
				//-> Case of different index, generate new point (case not implemented, can't tested with an example
				if (upper_planeA != upper_planeB){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, this case is not implemented\033[0m" << std::endl;
					return(false);}}


			//-> Generate the lower connexions
			for (int j, i(0); i < data->phase7.lower_points_index.size(); i++){
				if (i==0) j = data->phase7.lower_points_index.size()-1;
				else j = i-1;
				
				//-> Point index
				int index_A(data->phase7.lower_points_index[i]);
				int index_B(data->phase7.lower_points_index[j]);
				
				
				//-> Get the lower index plane
				int lower_planeA(-1);
				for (int k=0; k < data->phase7.reconstruction_points.Points[index_A].plane_index.size(); k++){
					int plane_index(data->phase7.reconstruction_points.Points[index_A].plane_index[k]);
					if (data->phase7.reconstruction_points.plane[plane_index].type == -1 && data->phase7.reconstruction_points.plane[plane_index].valid)
						lower_planeA = plane_index;}
					
				int lower_planeB(-1);
				for (int k=0; k < data->phase7.reconstruction_points.Points[index_B].plane_index.size(); k++){
					int plane_index(data->phase7.reconstruction_points.Points[index_B].plane_index[k]);
					if (data->phase7.reconstruction_points.plane[plane_index].type == -1 && data->phase7.reconstruction_points.plane[plane_index].valid)
						lower_planeB = plane_index;}
				
				
				//-> Check
				if (lower_planeA == -1 && lower_planeB == -1){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, the plane index is not ok\033[0m" << std::endl;
					return(false);}
				
				
				//-> Case of same index: Generate connexion between points
				if (lower_planeA == lower_planeB){
					data->phase7.reconstruction_points.Points[index_A].linear_conexion_index.push_back(index_B);
					data->phase7.reconstruction_points.Points[index_B].linear_conexion_index.push_back(index_A);}
				
				
				//-> Case of different index, generate new point (case not implemented, can't tested with an example
				if (lower_planeA != lower_planeB){
					if (sh_log) std::cout << "\033[1;31m[RoomShapeDetector::phase7] Failed, this case is not implemented\033[0m" << std::endl;
					return(false);}}
			
			
			data->GI_phase7.complete = true;
			return(true);}

			
		//-> END PROCESS
		bool RoomShapeDetector::release_memory(){
			
			process_data *data_declared (new process_data);
			data = data_declared;
			
			return (true);}
	
#endif
