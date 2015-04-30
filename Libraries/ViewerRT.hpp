#ifndef ViewerRT_HPP
#define ViewerRT_HPP
	
	//**STATIC VARIABLES DECLARATIONS**//
	static int semid;
	static std::vector<int> static_pid_vector;
	
	
	//**CONSTRUCTOR**//
	ViewerRT::ViewerRT (){
		running = false;
		sh_log = true;
		sh_exit = true;
		
		
		//**INIZIALIZE VIEWER CONFIGURATION**//
		//->viewer_config declared in private variables
		viewer_config = inicialize_data ();
		
		
		return;}


	//**DESTRUCTOR**//
	ViewerRT::~ViewerRT (){
		
		//**CLOSE VIEWER**//
		if (running) close_viewer_process(true);
		
		
		//**CLOSE PIPES**//
		close(instructions_pipe[1]);
		close(instructions_pipe[0]);
		close(info_pipe[1]);
		close(info_pipe[0]);
		
		//**WAIT TO THE VIEWER PROCESS TO END**//
		if (pid != 0){
			int status;
			waitpid(pid, &status, WUNTRACED);}
		return;}
	

	//**INTERRUPTION HANDLER**//
	void ViewerRT::signalHandler(int signum){
		//**CLOSE SEMPAPHORES**//
		semctl(semid,0,IPC_RMID,0);
		std::cout << "\033[1;31m[ViewerRT::signalHandler] Fatal Error. Interrupt signal (" << signum << ") for viewer procces received\033[0m" << std::endl;
		
		exit(1);}
	
		
	//**MAIN INTERRUPTION HANDLER**//
	void ViewerRT::main_signalHandler(int signum){
		//**KILL ALL EXECUTED PROCCESS**//
		for (int i = 0; i < static_pid_vector.size(); i++){ 
			kill(static_pid_vector[i], SIGKILL); 
		}	
		std::cout << "\033[1;31m[ViewerRT::main_signalHandler] Fatal Error. Interrupt signal (" << signum << ") for main proccess received\033[0m" << std::endl;
		
		exit(1);}
	
		
	//**INICIALIZE DATA**//
	ViewerRT::config_parameters ViewerRT::inicialize_data (){
		//**MAKE THE DEFAULT STRUCTURE**//
		config_parameters viewer_config;
		
		
		//**CONFIGURE PARAMETERS**//
		//->windows size, number and viewer point
			//temp// viewer_config.win_size.x = 1360;
			//temp// viewer_config.win_size.y = 768;		
		

		//viewer_config.win_size.x = 340;
		//viewer_config.win_size.y = 192;
		viewer_config.win_size.x = 816;
		viewer_config.win_size.y = 460;		
		//viewer_config.win_size.x = 1360;
		//viewer_config.win_size.y = 768;
		viewer_config.fullscreen = false;
		
		viewer_config.n_windows = 1;
		viewer_config.special_3_windows = true;
		
		viewer_config.view_point.x0 = 17;
		viewer_config.view_point.y0 = 17;
		viewer_config.view_point.z0 = 14.5;
		viewer_config.view_point.x1 = 20;
		viewer_config.view_point.y1 = 20;
		viewer_config.view_point.z1 = 20;
		
		
		//->Cordenate system
		viewer_config.dim_cord_syst = 1;
		viewer_config.show_cord_syst = true;
		
		
		//->Back ground color
		viewer_config.back_ground_color.R = 0;
		viewer_config.back_ground_color.G = 0;
		viewer_config.back_ground_color.B = 0;
		
		
		//->Set trurn configuration
		viewer_config.rotation_view_point.degree_inc = 1;
		viewer_config.rotation_view_point.module_inc = 1;
		viewer_config.rotation_view_point.min_module = 0.15;
		viewer_config.rotation_view_point.range_module = 0.45;
		viewer_config.rotation_view_point.kind = 0;
		
		
		
		//**RETURN THE DEFAULT STRUCT**//
		return(viewer_config);
	}
	

	//**RUN INTRUCTION**//
	bool ViewerRT::run_viewer(){
		//**check if the viewer is running**//
		if (running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is running\033[0m" << std::endl;
			return(false);}
		running = true;
	
	
		//**MAKE AND CONFIGURE SEMAPHORE**//
		//-> "semid" in static declaration
		int key(10);
		int num_semaphore(2);
		if((semid = semget(key,num_semaphore,IPC_CREAT|0600)) == -1){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] Failure to create the semaphore\033[0m" << std::endl;
			return(false);}

		
		//**SET INITIAL VALUES TO THE USED SEMAPHORE**//
		semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,0);
		semctl(semid,SEM_TURN_TO_SEND_THE_INSTRUCTION,SETVAL,1);
	
		
	
		//**MAKE AND CONFIGURE PIPES**//
		// "instructions_pipe[2]" in general declaration (-> Pipes)
		// "info_pipe[2]" in general declaration (-> Pipes)
		if (pipe(instructions_pipe) == -1){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] Failure to create the pipe\033[0m" << std::endl;
			return(false);}
		if (pipe(info_pipe) == -1){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] Failure to create the pipe\033[0m" << std::endl;
			return(false);}
	
	
	
		//**FORK THE EXECUTION**//
		//-> "pid" in private declarations
		pid = fork();

		
		//**CHECK ERROR IN FORK**//
		if (pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] Can't fork program to make viewer window\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; CONFIGURE THE INTERTUPTIONS**//
		else if (pid > 0){
			//**ACTIVE SIGNAL INTERRUPTIONs**//
			//-> Termination signal
			signal (SIGTERM,ViewerRT::main_signalHandler);
			//-> Process abort signal
			signal (SIGABRT,ViewerRT::main_signalHandler);
			//-> Access to an undefined portion of a memory object
			signal (SIGBUS,ViewerRT::main_signalHandler);
			//-> Erroneous arithmetic operation
			signal (SIGFPE,ViewerRT::main_signalHandler);
			//-> Illegal instruction
			signal (SIGILL,ViewerRT::main_signalHandler);
			//-> Terminal quit signal
			signal (SIGQUIT,ViewerRT::main_signalHandler);
			// -> Invalid memory reference
			signal (SIGSEGV,ViewerRT::main_signalHandler);
			//-> Bad system call
			signal (SIGSYS,ViewerRT::main_signalHandler);
			//-> Trace/breakpoint trap
			signal (SIGTRAP,ViewerRT::main_signalHandler);
			//-> CPU time limit exceeded
			signal (SIGXCPU,ViewerRT::main_signalHandler);
			//-> File size limit exceeded.
			signal (SIGXFSZ,ViewerRT::main_signalHandler);
			
			
			
			//**STORE CHILD PID**//
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =pid;
			new_pid_info.process_name ="ViewerRT";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(pid);}
		
			

			
		//**CHILD EXECUTION; MAIN PROCESS OF THE VIEWER WINDOW**//
		else if (pid == 0){
			
			
			//**ACTIVE SIGNAL INTERRUPTIONs**//
			//-> Termination signal
			signal (SIGTERM,ViewerRT::signalHandler);
			//-> Process abort signal
			signal (SIGABRT,ViewerRT::signalHandler);
			//-> Access to an undefined portion of a memory object
			signal (SIGBUS,ViewerRT::signalHandler);
			//-> Erroneous arithmetic operation
			signal (SIGFPE,ViewerRT::signalHandler);
			//-> Illegal instruction
			signal (SIGILL,ViewerRT::signalHandler);
			//-> Terminal quit signal
			signal (SIGQUIT,ViewerRT::signalHandler);
			// -> Invalid memory reference
			signal (SIGSEGV,ViewerRT::signalHandler);
			//-> Bad system call
			signal (SIGSYS,ViewerRT::signalHandler);
			//-> Trace/breakpoint trap
			signal (SIGTRAP,ViewerRT::signalHandler);
			//-> CPU time limit exceeded
			signal (SIGXCPU,ViewerRT::signalHandler);
			//-> File size limit exceeded.
			signal (SIGXFSZ,ViewerRT::signalHandler);
			
			
			
			//**INICIALIZE THE BUCKLE CONDITION**//
			bool reset_viewer(true);
			float degree_advanced(0), module_advanced(0);

			
			pcl::visualization::PCLVisualizer viewer ("vista 3D");
			
			while (reset_viewer){
				//**CONFIGURE THE VIEWER WINDOW**//
				viewer.initCameraParameters(); 
				
				//->Configure windows size
				if (!viewer_config.fullscreen){
					viewer.setFullScreen(false);
					viewer.setSize(viewer_config.win_size.x, viewer_config.win_size.y);}
				
				else if (viewer_config.fullscreen)
					viewer.setFullScreen(true);
					
					
				//**Configure the number of windows
				int v1(0), v2(0), v3(0), v4(0);
				unsigned int n1(0), n2(0), n3(0), n4(0);
				
				//-> Delete all clouds
				viewer.removeAllPointClouds(v1);
				viewer.removeAllPointClouds(v2);
				viewer.removeAllPointClouds(v3);
				viewer.removeAllPointClouds(v4);
				
				//->One windows
				if (viewer_config.n_windows < 2){
					viewer.createViewPort(0, 0, 1, 1, v1);
					viewer_config.n_windows = 1;}
				
				//->Two windows	
				else if (viewer_config.n_windows == 2){
					viewer.createViewPort(0.0, 0.0, 1, 0.5, v2);
					viewer.createViewPort(0.0, 0.5, 1, 1, v1);}
				
				//->Three windows
				else if (viewer_config.n_windows == 3 && !viewer_config.special_3_windows){
					viewer.createViewPort(0.0, 0.66, 1, 1, v1);
					viewer.createViewPort(0.0, 0.33, 1, 0.66, v2);
					viewer.createViewPort(0.0, 0.0, 1, 0.33, v3);}
				
				//->Alternative three windows
				else if (viewer_config.n_windows == 3 && viewer_config.special_3_windows){
					viewer.createViewPort(0, 0.5, 1, 1, v1);				
					viewer.createViewPort(0, 0, 0.5, 0.5, v2);
					viewer.createViewPort(0.5, 0, 1, 0.5, v3);}
				
				//->Four windows
				else if (viewer_config.n_windows > 3){
					viewer.createViewPort(0.0, 0.5, 0.5, 1.0, v1);
					viewer.createViewPort(0.5, 0.5, 1, 1, v2);
					viewer.createViewPort(0.0, 0.0, 0.5, 0.5, v3);
					viewer.createViewPort(0.5, 0.0, 1.0, 0.5, v4);
					viewer_config.n_windows = 4;}
				
				//->Configure the camara position
				viewer.setCameraPosition(viewer_config.view_point.x0,
										 viewer_config.view_point.y0,
										 viewer_config.view_point.z0,
										 viewer_config.view_point.x1,
										 viewer_config.view_point.y1,
										 viewer_config.view_point.z1);

				
				//->Configure cordenation system
				if (viewer_config.show_cord_syst){
					viewer.addCoordinateSystem(viewer_config.dim_cord_syst);}
				
				//-> Configure background color
				if (viewer_config.back_ground_color.R > 255) viewer_config.back_ground_color.R  = 255;
				if (viewer_config.back_ground_color.G > 255) viewer_config.back_ground_color.G  = 255;
				if (viewer_config.back_ground_color.B > 255) viewer_config.back_ground_color.B  = 255;
				viewer.setBackgroundColor (viewer_config.back_ground_color.R,
										   viewer_config.back_ground_color.G,
										   viewer_config.back_ground_color.B);
				
				
				
				//->Restart the reset value
				reset_viewer = false;
				
		

			
				//** PRINCIPAL LOOP ON THE PARALEL PROCCES**//
				bool run(true);
				while (run){
					//**REFRESH THE VIEWER DISPLAY**//
					viewer.spinOnce (100);
					boost::this_thread::sleep (boost::posix_time::microseconds (1000));// 10000
					
					
					
					//**ROTATE DE VIEW IF IS ACTIVATE**//
					if (viewer_config.rotation_view_point.kind == 1
					||	viewer_config.rotation_view_point.kind == 2
					||	viewer_config.rotation_view_point.kind == 3
					||	viewer_config.rotation_view_point.kind == 4
					||	viewer_config.rotation_view_point.kind == 5
					||	viewer_config.rotation_view_point.kind == 6
					||	viewer_config.rotation_view_point.kind == 7
					||	viewer_config.rotation_view_point.kind == 8)
						degree_advanced = degree_advanced + viewer_config.rotation_view_point.degree_inc * (3.1416/180);
					
					if (viewer_config.rotation_view_point.kind == 2 
					||	viewer_config.rotation_view_point.kind == 3
					||	viewer_config.rotation_view_point.kind == 4
					||	viewer_config.rotation_view_point.kind == 5
					||	viewer_config.rotation_view_point.kind == 6
					||	viewer_config.rotation_view_point.kind == 7
					||	viewer_config.rotation_view_point.kind == 8)
						module_advanced = module_advanced  + viewer_config.rotation_view_point.module_inc * (3.1416/180);
					
					//-> Rotate 1 OK
					if (viewer_config.rotation_view_point.kind == 1){
						viewer.setCameraPosition(viewer_config.view_point.x0 * cos(degree_advanced),
												 viewer_config.view_point.y0 * sin(degree_advanced),
												 viewer_config.view_point.z0,
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					
					//-> Rotate 2 OK
					else if (viewer_config.rotation_view_point.kind == 2){
						viewer.setCameraPosition(viewer_config.view_point.x0 * cos(module_advanced) * cos(degree_advanced),
												 viewer_config.view_point.y0 * cos(module_advanced) * sin(degree_advanced),
												 viewer_config.view_point.z0 * cos(module_advanced),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					 
					//-> Rotate 3 OK
					else if (viewer_config.rotation_view_point.kind == 3){
						viewer.setCameraPosition(viewer_config.view_point.x0 * (viewer_config.rotation_view_point.min_module) * cos(degree_advanced),
												 viewer_config.view_point.y0 * (viewer_config.rotation_view_point.min_module) * sin(degree_advanced),
												 viewer_config.view_point.z0 * (viewer_config.rotation_view_point.min_module),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					
					//-> Rotate 4 OK
					else if (viewer_config.rotation_view_point.kind == 4){
						double alfa (0.45 * 3.1418 * sin(module_advanced));
						viewer.setCameraPosition(viewer_config.view_point.x0 * viewer_config.rotation_view_point.min_module * (1 / cos(alfa)) * cos(degree_advanced),
												 viewer_config.view_point.y0 * viewer_config.rotation_view_point.min_module * (1 / cos(alfa)) * sin(degree_advanced),
												 viewer_config.view_point.z0 * viewer_config.rotation_view_point.min_module * (1 / cos(alfa)),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					
					//-> Rotate 5 OK
					else if (viewer_config.rotation_view_point.kind == 5){
						double alfa (0.45 * 3.1418 * sin(module_advanced));
						viewer.setCameraPosition(viewer_config.view_point.x0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * cos(degree_advanced),
												 viewer_config.view_point.y0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * sin(degree_advanced),
												 viewer_config.view_point.z0 * viewer_config.rotation_view_point.min_module * 0.5 * (1 / cos(alfa)),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					
					//-> Rotate 6 OK
					else if (viewer_config.rotation_view_point.kind == 6){
						double alfa (0.45 * 3.1418 * sin(module_advanced));
						viewer.setCameraPosition(viewer_config.view_point.x0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * cos(degree_advanced),
												 viewer_config.view_point.y0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * sin(degree_advanced),
												 viewer_config.view_point.z0 * viewer_config.rotation_view_point.min_module *  sin(module_advanced) * (1 / cos(alfa)),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					
					//-> Rotate 7 OK
					else if (viewer_config.rotation_view_point.kind == 7){
						double alfa (viewer_config.rotation_view_point.range_module * 3.1418 * sin(module_advanced));
						viewer.setCameraPosition(viewer_config.view_point.x0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * cos(degree_advanced),
												 viewer_config.view_point.y0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * sin(degree_advanced),
												 viewer_config.view_point.z0 * viewer_config.rotation_view_point.min_module *  0.5 * (1 + sin(module_advanced)) * (1 / cos(alfa)),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					
					//-> Rotate 8 OK
					else if (viewer_config.rotation_view_point.kind == 8){
						double alfa (viewer_config.rotation_view_point.range_module * 3.1418 * sin(module_advanced));
						viewer.setCameraPosition(viewer_config.view_point.x0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * cos(degree_advanced),
												 viewer_config.view_point.y0 * viewer_config.rotation_view_point.min_module *  (1 / cos(alfa)) * sin(degree_advanced),
												 viewer_config.view_point.z0 * viewer_config.rotation_view_point.min_module *  0.5 * (1 + sin(module_advanced*2)) * (1 / cos(alfa)),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}
					
					//-> Not working
					else if (viewer_config.rotation_view_point.kind == 9 && false){
						viewer.setCameraPosition(viewer_config.view_point.x0 * (viewer_config.rotation_view_point.min_module + sqrt(cos(module_advanced) * cos(module_advanced))) * cos(degree_advanced),
												 viewer_config.view_point.y0 * (viewer_config.rotation_view_point.min_module + sqrt(cos(module_advanced) * cos(module_advanced))) * sin(degree_advanced),
												 viewer_config.view_point.z0 * (viewer_config.rotation_view_point.min_module + sqrt(cos(module_advanced) * cos(module_advanced))),
												 viewer_config.view_point.x1 * cos(degree_advanced),
												 viewer_config.view_point.y1 * sin(degree_advanced),
												 viewer_config.view_point.z1 );}	

												 
												 
					//**CHECK IF IT HAS RECEIVED AN INSTRUCTION SIGNAL**//
					if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > 0){
						//**RESET THE SEMAPHORE**//
						int semaphore_value;
						semaphore_value = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) -1;
						semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,semaphore_value);
						
						
						
						//**READ THE INSTRUCTION PIPE**//
						instruction instruction_received;
						read(instructions_pipe[0],&instruction_received,sizeof(instruction_received));	

						
						
						//**MANAGE INSTRUCTIONS**//
						//->Close viewer
						if (instruction_received.instruction == CLOSE_VIEWER) {
							run = false;}
						
						
						//->Delete last colud for one window
						else if (instruction_received.instruction == DELETE_LAST_ONE){
							unsigned int window;
							int *v;
							read(info_pipe[0],&window, sizeof (window));
							
							char cloud_name[10];
							if (window == 1){ 
								v = &v1; 
								sprintf(cloud_name,"w1-%d", n1);
								if (viewer.removePointCloud(cloud_name,*v)) n1--;}
								
							else if (window == 2){ 
								v = &v2; 
								sprintf(cloud_name,"w2-%d", n2);
								if (viewer.removePointCloud(cloud_name,*v)) n2--;}
								
							else if (window == 3){ 
								v = &v3; 
								sprintf(cloud_name,"w3-%d", n3);
								if (viewer.removePointCloud(cloud_name,*v)) n3--;}
								
							else if (window == 4){ 
								v = &v4; 
								sprintf(cloud_name,"w4-%d", n4);
								if (viewer.removePointCloud(cloud_name,*v)) n4--;}}
						
												
						//->Delete concrete object
						else if (instruction_received.instruction == DELETE_CONCRETE_OBJECT){
							unsigned int window;
							char cloud_name[10];
							int *v;
							int id;
							read(info_pipe[0],&window, sizeof (window));
							read(info_pipe[0],&id, sizeof (id));
							
							sprintf(cloud_name,"%d", id);

							viewer.removePointCloud(cloud_name,v1);
							viewer.removePointCloud(cloud_name,v2);
							viewer.removePointCloud(cloud_name,v3);
							viewer.removePointCloud(cloud_name,v4);}
						
												
						//->Delete all object for one window
						else if (instruction_received.instruction == DELETE_ALL_ONE){
							unsigned int window;
							int *v;
							read(info_pipe[0],&window, sizeof (window));
							if      (window == 1){ v = &v1; n1 = 0;}
							else if (window == 2){ v = &v2; n2 = 0;}
							else if (window == 3){ v = &v3; n3 = 0;}
							else if (window == 4){ v = &v4; n4 = 0;}
							viewer.removeAllPointClouds(*v);}
												
						
						//->Delate all object for all windows
						else if (instruction_received.instruction == DELETE_ALL_ALL){
							n1 = 0; n2 = 0; n3 = 0; n4 = 0;
							//-> Delete all clouds
							viewer.removeAllPointClouds(v1);
							viewer.removeAllPointClouds(v2);
							viewer.removeAllPointClouds(v3);
							viewer.removeAllPointClouds(v4);}
												
						
						//->Load XYX cloud	
						else if (instruction_received.instruction == LOAD_XYZ){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							read(info_pipe[0],&window, sizeof (window));
							
							
							//->Read cloud
							pcl::PointXYZ point_recived;
							pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
							for (int i=0; i <instruction_received.bytes_in_info_pipe; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"w1-%d", ++n1);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"w2-%d", ++n2);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"w3-%d", ++n3);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"w4-%d", ++n4);}
							
							
							
							//->Load cloud on viewer
							viewer.addPointCloud<pcl::PointXYZ> (cloud, cloud_name,*v);}
						
						
						//->(2)Load XYX cloud "Named"
						else if (instruction_received.instruction == LOAD_XYZ_2){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							int id;
							read(info_pipe[0],&window, sizeof (window));
							read(info_pipe[0],&id, sizeof (id));
							
							//->Read cloud
							pcl::PointXYZ point_recived;
							pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
							for (int i=0; i <instruction_received.bytes_in_info_pipe; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"%d", id);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"%d", id);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"%d", id);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"%d", id);}
							
							
							
							//->Load cloud on viewer
							viewer.addPointCloud<pcl::PointXYZ> (cloud, cloud_name,*v);}
						
						
						//->(3)Load XYX cloud "color"	
						else if (instruction_received.instruction == LOAD_XYZ_COLOR){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							read(info_pipe[0],&window, sizeof (window));
							
							//->Read colors
							float R,B,G;
							read(info_pipe[0],&R, sizeof (R));
							read(info_pipe[0],&G, sizeof (G));
							read(info_pipe[0],&B, sizeof (B));
							
							
							//->Read cloud
							pcl::PointXYZ point_recived;
							pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
							for (int i=0; i <instruction_received.bytes_in_info_pipe; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"w1-%d", ++n1);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"w2-%d", ++n2);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"w3-%d", ++n3);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"w4-%d", ++n4);}
							
							
							//->Set color
							pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, R, G, B);
								
							
							
							//->Load cloud on viewer
							viewer.addPointCloud<pcl::PointXYZ> (cloud,single_color, cloud_name,*v);}
						
						
						//->(4)Load XYX cloud "color" "Named"	
						else if (instruction_received.instruction == LOAD_XYZ_COLOR_2){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							int id;
							read(info_pipe[0],&window, sizeof (window));
							read(info_pipe[0],&id, sizeof (id));
							
							//->Read colors
							float R,B,G;
							read(info_pipe[0],&R, sizeof (R));
							read(info_pipe[0],&G, sizeof (G));
							read(info_pipe[0],&B, sizeof (B));
							
							
							//->Read cloud
							pcl::PointXYZ point_recived;
							pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
							for (int i=0; i <instruction_received.bytes_in_info_pipe; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"%d", id);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"%d", id);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"%d", id);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"%d", id);}
							
							
							//->Set color
							pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, R, G, B);
								
							
							
							//->Load cloud on viewer
							viewer.addPointCloud<pcl::PointXYZ> (cloud,single_color, cloud_name,*v);}
						
						
						//->Load XYX RGB cloud	
						else if (instruction_received.instruction == LOAD_RGB_XYZ){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							read(info_pipe[0],&window, sizeof (window));
							
							
							//->Read cloud
							pcl::PointXYZRGB point_recived;
							pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
							for (int i=0; i <instruction_received.bytes_in_info_pipe; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"w1-%d", ++n1);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"w2-%d", ++n2);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"w3-%d", ++n3);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"w4-%d", ++n4);}
							
							
							
							//->Load cloud on viewer
							viewer.addPointCloud<pcl::PointXYZRGB> (cloud, cloud_name,*v);}
						
						
						//->(2)Load XYX RGB cloud "Named"
						else if (instruction_received.instruction == LOAD_RGB_XYZ_2){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							int id;
							read(info_pipe[0],&window, sizeof (window));
							read(info_pipe[0],&id, sizeof (id));
							
							//->Read cloud
							pcl::PointXYZRGB point_recived;
							pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
							for (int i=0; i <instruction_received.bytes_in_info_pipe; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"%d", id);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"%d", id);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"%d", id);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"%d", id);}
							
							
							
							//->Load cloud on viewer
							viewer.addPointCloud<pcl::PointXYZRGB> (cloud, cloud_name,*v);}
						
						
						//->Load SLT file	
						else if (instruction_received.instruction == LOAD_STL){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							read(info_pipe[0],&window, sizeof (window));
							
							//->Read mesh
							pcl::PolygonMesh polymesh;
							//->Read vertices
							int size_i;
							read(info_pipe[0], &size_i, sizeof(size_i));
							for (int i=0; i < size_i; i++){
								int size_j;
								pcl::Vertices vertices;
								read(info_pipe[0], &size_j, sizeof(size_j));
								for(int j=0; j < size_j; j++){
									uint32_t v;
									read(info_pipe[0], &v, sizeof(v));
									vertices.vertices.push_back(v);}
								polymesh.polygons.push_back(vertices);}
							
							//->Read cloud
							pcl::PointXYZ point_recived;
							pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
							int size_i2;
							read(info_pipe[0], &size_i2, sizeof(size_i2));
							for (int i=0; i < size_i2; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
								
							//->Convert cloud
							pcl::PCLPointCloud2 cloud2;
							pcl::toPCLPointCloud2(*cloud, cloud2);
							
							//->Store cloud
							polymesh.cloud = cloud2;
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"w1-%d", ++n1);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"w2-%d", ++n2);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"w3-%d", ++n3);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"w4-%d", ++n4);}
							
							
							//->Display mesh on the screen
							viewer.addPolygonMesh (polymesh, cloud_name,*v);}

						
						//->(2)Load STL file
						else if (instruction_received.instruction == LOAD_STL_2){
							//**READ ADDITIONAL INFO**//
							//-> read window
							unsigned int window;
							int id;
							read(info_pipe[0],&window, sizeof (window));
							read(info_pipe[0],&id, sizeof (id));
							
							//->Read mesh
							pcl::PolygonMesh polymesh;
							//->Read vertices
							int size_i;
							read(info_pipe[0], &size_i, sizeof(size_i));
							for (int i=0; i < size_i; i++){
								int size_j;
								pcl::Vertices vertices;
								read(info_pipe[0], &size_j, sizeof(size_j));
								for(int j=0; j < size_j; j++){
									uint32_t v;
									read(info_pipe[0], &v, sizeof(v));
									vertices.vertices.push_back(v);}
								polymesh.polygons.push_back(vertices);}
							
							//->Read cloud
							pcl::PointXYZ point_recived;
							pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
							int size_i2;
							read(info_pipe[0], &size_i2, sizeof(size_i2));
							for (int i=0; i < size_i2; i++){
								read(info_pipe[0],&point_recived,sizeof (point_recived));
								cloud->push_back(point_recived);}
								
							//->Convert cloud
							pcl::PCLPointCloud2 cloud2;
							pcl::toPCLPointCloud2(*cloud, cloud2);
							
							//->Store cloud
							polymesh.cloud = cloud2;
							
							
							//->Analize the window
							int *v;
							char cloud_name[10];
							while (window > viewer_config.n_windows) window = window - viewer_config.n_windows;
							if (window < 1) window = 1;
							if      (window == 1){ v = &v1; sprintf(cloud_name,"%d", id);}
							else if (window == 2){ v = &v2; sprintf(cloud_name,"%d", id);}
							else if (window == 3){ v = &v3; sprintf(cloud_name,"%d", id);}
							else if (window == 4){ v = &v4; sprintf(cloud_name,"%d", id);}
							
							
							//->Display mesh on the screen
							viewer.addPolygonMesh (polymesh, cloud_name,*v);}
							
							
						//->Set configuration and restart	
						else if (instruction_received.instruction == SET_CONFIGURATION_R){
							//**READ ADDITIONAL INFO**//
							read(info_pipe[0],&viewer_config,instruction_received.bytes_in_info_pipe);
							reset_viewer = true;
							run = false;}
						
						
						//->Set configuration but do not restart	
						else if (instruction_received.instruction == SET_CONFIGURATION_NR){
							//**READ ADDITIONAL INFO**//
							read(info_pipe[0],&viewer_config,instruction_received.bytes_in_info_pipe);}
						
						
						//->Send configuration
						else if (instruction_received.instruction == GET_CONFIGURATION){
							//**SEND ADDITIONAL INFO**//
							write(info_pipe[1],&viewer_config,sizeof(viewer_config));}}}}
			
			
			
			//**KILL THE SEMAPHORE**//
			semctl(semid,0,IPC_RMID,0);
		
	
	
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);	
				
				
				
			//**SHOW SUCCESS MESSAGE**//
			if(sh_exit) std::cout << "\033[1;32mViewer closed successful\033[0m" << std::endl;
			
				
				
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
			
			
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}

	
	//**PRIORITY INSTRUCTION -> CLOSE VIEWER_WINDOW**//
	bool ViewerRT::close_viewer_process (bool priority){		
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::close_viewer_process] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::close_viewer_process] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="CLOSE_VIEWER";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
		
	
							
			
			//**WRITE THE INSTRUCTION**//
			instruction instruction_to_send;
			instruction_to_send.instruction = CLOSE_VIEWER;
			instruction_to_send.bytes_in_info_pipe = 0;
			
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}			
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		running = false;
		return(true);}
	

	//**Give the running state**//
	bool ViewerRT::viewer_state(){
		return(running);}
	
	
	//**INSTRUCTION -> SET_PARAMETERS**//
	bool ViewerRT::set_parameters(struct config_parameters viewer_config_in, bool restart, bool priority){			
		
		//**STORE LOCAL PARAMETERS**//
		viewer_config = viewer_config_in;
		
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::set_parameters] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::set_parameters] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			if (restart) new_pid_info.process_name ="SET_CONFIGURATION_R";	
			else new_pid_info.process_name ="SET_CONFIGURATION_NR";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION**//
			instruction instruction_to_send;
			if (restart) instruction_to_send.instruction = SET_CONFIGURATION_R;
			else instruction_to_send.instruction = SET_CONFIGURATION_NR;
			instruction_to_send.bytes_in_info_pipe = sizeof(viewer_config_in);
			
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			
			
			//**SEND ADDITIONAL INFO**//
			write(info_pipe[1], &viewer_config_in, sizeof(viewer_config_in));
			
			
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}


	//**INSTRUCTION -> LOAD_XYZ**//
	bool ViewerRT::load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, bool priority){			
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (cloud->size() <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No cloud data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_XYZ";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = cloud->size();
			instruction_to_send.instruction = LOAD_XYZ;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			
			//->Send points 
			int i;
			pcl::PointXYZ point_to_send;
			for (i=0; i < cloud->size(); i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}


	//**(2)INSTRUCTION -> LOAD_XYZ**//
	bool ViewerRT::load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, int id, bool priority){			
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (cloud->size() <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No cloud data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_XYZ";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = cloud->size();
			instruction_to_send.instruction = LOAD_XYZ_2;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			write(info_pipe[1], &id, sizeof(window));
			
			
			//->Send points 
			int i;
			pcl::PointXYZ point_to_send;
			for (i=0; i < cloud->size(); i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}

	
	//**(3)INSTRUCTION -> LOAD_XYZ**//
	bool ViewerRT::load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, float R, float G, float B, bool priority){			
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (cloud->size() <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No cloud data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_XYZ_COLOR";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = cloud->size();
			instruction_to_send.instruction = LOAD_XYZ_COLOR;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			
			//->Send color
			write(info_pipe[1],&R, sizeof (R));
			write(info_pipe[1],&G, sizeof (G));
			write(info_pipe[1],&B, sizeof (B));
			
			
			//->Send points 
			int i;
			pcl::PointXYZ point_to_send;
			for (i=0; i < cloud->size(); i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}

	//**(4) INSTRUCTION -> lOAD_XYZ DIFF **//
	bool ViewerRT::load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, unsigned int n_cloud, unsigned int t_clouds, bool priority){
		float R (255), G(0), B(0);
		
		int color;
		int scale(255*5);

		
		color = n_cloud * (scale / t_clouds);
		
			
		//-> Green 0-255
		while (G < 255 && color > 0) {
			G++;
			color--;}			
		//-> Red 255 - 0
		while (R > 0 && color > 0) {
			R--;
			color--;}				
		//-> Blue 0 - 255
		while (B < 255 && color > 0) {
			B++;
			color--;}				
		//-> Green 255 - 0 
		while (G > 0 && color > 0) {
			G--;
			color--;}				
		//-> Red 0 -255
		while (R < 255 && color > 0) {
			R++;
			color--;}				
		
		return(load(cloud, window, R, G, B, priority));}

	
	//**(4)INSTRUCTION -> LOAD_XYZ**//
	bool ViewerRT::load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, int id, float R, float G, float B, bool priority){			
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (cloud->size() <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No cloud data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_XYZ";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = cloud->size();
			instruction_to_send.instruction = LOAD_XYZ_2;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			write(info_pipe[1], &id, sizeof(window));
			
			//->Send color
			write(info_pipe[1],&R, sizeof (R));
			write(info_pipe[1],&G, sizeof (G));
			write(info_pipe[1],&B, sizeof (B));
			
			
			//->Send points 
			int i;
			pcl::PointXYZ point_to_send;
			for (i=0; i < cloud->size(); i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}
	
	
	//**INSTRUCTION -> LOAD_RBG_XYZ**//
	bool ViewerRT::load(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, unsigned int window, bool priority){			
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (cloud->size() <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No cloud data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_RGB_XYZ";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = cloud->size();
			instruction_to_send.instruction = LOAD_RGB_XYZ;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			
			//->Send points 
			int i;
			pcl::PointXYZRGB point_to_send;
			for (i=0; i < cloud->size(); i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}


	//**(2)INSTRUCTION -> LOAD_RGB_XYZ**//
	bool ViewerRT::load(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, unsigned int window, int id, bool priority){			
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (cloud->size() <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No cloud data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_RGB_XYZ_2";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = cloud->size();
			instruction_to_send.instruction = LOAD_RGB_XYZ_2;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			write(info_pipe[1], &id, sizeof(window));
			
			
			//->Send points 
			int i;
			pcl::PointXYZRGB point_to_send;
			for (i=0; i < cloud->size(); i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}

	
	//**INSTRUCTION -> LOAD STL**//
	bool ViewerRT::load(pcl::PolygonMesh polymesh, unsigned int window,  bool priority){
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (sizeof(polymesh) <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No mesh data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_STL";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid == 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = polymesh.polygons.size();
			instruction_to_send.instruction = LOAD_STL;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			
			
			
			//*********************************************************************************************
			//**SEND MESH**//
			//-> Send vertices
			int size_i(polymesh.polygons.size());
			write(info_pipe[1], &size_i, sizeof(size_i));
			for (int i=0; i < size_i; i++){
				int size_j(polymesh.polygons[i].vertices.size());
				write(info_pipe[1], &size_j, sizeof(size_j));
				for(int j=0; j < size_j; j++){
				uint32_t v(polymesh.polygons[i].vertices[j]);
				write(info_pipe[1], &v, sizeof(v));}}
	
			
			//->Send point cloud
			//->Convert it to standard type
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
			pcl::PCLPointCloud2 cloud2(polymesh.cloud);
			pcl::fromPCLPointCloud2 (cloud2, *cloud);
			pcl::PointXYZ point_to_send;
			int size_i2(cloud->size());
			write(info_pipe[1], &size_i2, sizeof(size_i2));
			for (int i=0; i < size_i2; i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}		
		
			
			
			//***********************************************************************************************
			
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}
	
	
	//**(2)INSTRUCTION -> LOAD STL**//
	bool ViewerRT::load(pcl::PolygonMesh polymesh, unsigned int window, int id, bool priority){
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
		
		//**CHECK IF THE COLUD INFO IS CORRECT**//
		if (sizeof(polymesh) <= 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] No mesh data to send to viewer\033[0m" << std::endl;
			return(false);}
			
		
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::load] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="LOAD_STL_2";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid == 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = polymesh.polygons.size();
			instruction_to_send.instruction = LOAD_STL_2;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			write(info_pipe[1], &id, sizeof(window));
			
			
			//**SEND MESH**//
			//-> Send vertices
			int size_i(polymesh.polygons.size());
			write(info_pipe[1], &size_i, sizeof(size_i));
			for (int i=0; i < size_i; i++){
				int size_j(polymesh.polygons[i].vertices.size());
				write(info_pipe[1], &size_j, sizeof(size_j));
				for(int j=0; j < size_j; j++){
				uint32_t v(polymesh.polygons[i].vertices[j]);
				write(info_pipe[1], &v, sizeof(v));}}
	
			
			//->Send point cloud
			//->Convert it to standard type
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
			pcl::PCLPointCloud2 cloud2(polymesh.cloud);
			pcl::fromPCLPointCloud2 (cloud2, *cloud);
			pcl::PointXYZ point_to_send;
			int size_i2(cloud->size());
			write(info_pipe[1], &size_i2, sizeof(size_i2));
			for (int i=0; i < size_i2; i++){
				point_to_send = cloud->points[i];
				write(info_pipe[1], &point_to_send, sizeof (point_to_send));}		
		
			
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}
	
		
	//**INSTRUCTION -> DELETE ALL CLOUDS**//
	bool ViewerRT::delete_all_objets (int window, bool priority){
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_all_objets] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
	
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_all_objets] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="DELETE_ALL_ONE";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = sizeof(window);
			instruction_to_send.instruction = DELETE_ALL_ONE;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}
	

	//**INSTRUCTION -> DELETE LAST CLOUDS**//
	bool ViewerRT::delete_last_objets (int window, bool priority){
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_last_objets] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
	
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_last_objets] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="DELETE_LAST_ONE";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = sizeof(window);
			instruction_to_send.instruction = DELETE_LAST_ONE;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &window, sizeof(window));
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}
	
	
	//**INSTRUCTION -> DELETE ALL CLOUDS FROM ALL WINDOWS**//
	bool ViewerRT::delete_all_objets (bool priority){
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_all_objets] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
	
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_all_objets] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="DELETE_ALL_ALL";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.instruction = DELETE_ALL_ALL;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		}
	

	//**INSTRUCTION -> DELETE CONCRETE CLOUDS**//
	bool ViewerRT::delete_concrete_objets (int id, bool priority){
		//**check if the viewer is not running**//
		if (!running){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::ViewerRT] The viewer is not running\033[0m" << std::endl;
			return(false);}
		
		
		
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_concrete_objets] The semaphore is offline\033[0m" << std::endl;
			return(false);}
		
	
		
		//**FORK THE EXECUTION**//
		int instruction_pid;
		instruction_pid = fork();
		
		
		
		//**CHECK ERROR IN FORK**//
		if (instruction_pid == -1) {    
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::delete_concrete_objets] Can't fork program to send instruction\033[0m" << std::endl;
			return(false);}
		
		
		
		//**MAIN EXECUTION; STORE CHILD PID**//
		else if (instruction_pid > 0){
			//-> "static_pid_vector" in static declarations
			//-> "proccess_vector" in public declaration
			struct pid_info new_pid_info;
			new_pid_info.pid =instruction_pid;
			new_pid_info.process_name ="DELETE_CONCRETE_OBJECT";	
			proccess_vector.push_back(new_pid_info);
			static_pid_vector.push_back(instruction_pid);}
		
		
		
		//**CHILD EXECUTION; MAIN PROCESS OF THE INSTRUCTION**//
		else if (instruction_pid== 0){
			
			//**WRITE THE INSTRUCTION AND THE ADITIONAL INFO**//
			
			instruction instruction_to_send;
			//->Points of the cloud and the shower window
			instruction_to_send.bytes_in_info_pipe = sizeof(id);
			instruction_to_send.instruction = DELETE_CONCRETE_OBJECT;
			
			
			//*WAIT FOR THE TURN TO COMMUNICATE TO THE MAIN VIEWER-PROCESS TO SEND THE INSTRUCTION IF IS NOT A PRIORITY INSTRUCTION**//
			if  (!priority) {
				struct sembuf operation;
				operation.sem_num = SEM_TURN_TO_SEND_THE_INSTRUCTION;
				operation.sem_op = -1;
				operation.sem_flg = SEM_UNDO;
				semop(semid, &operation, 1);}				
			
					
			//**STORE THE SEMAPHORE VALUE**//
			int ticket;
			ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
			//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
			semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
			//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
			while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
			//**SEND THE INSTRUCTION BY THE PIPE**//
			write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			

			//**SEND ADDITIONAL INFO**//
			//->Send window number
			write(info_pipe[1], &id, sizeof(id));
			
		
			
			//**CLOSE PIPES**//
			close(instructions_pipe[1]);
			close(instructions_pipe[0]);
			close(info_pipe[1]);
			close(info_pipe[0]);
			
			
		
			//**END EXECUTION**//
			exit(EXIT_SUCCESS);}
		
		
		
		//**RETURN TO MAIN PROCESS**//
		return(true);}
		
	
	//**PRIORITY INSTRUCTION -> GET_PARAMETERS**//
	bool ViewerRT::get_parameters(struct config_parameters* config){
		//**check if the viewer is not running**//
		if (!running){
			*config = viewer_config;
			return(true);}
		
			
			
		//**CHECK IF SEMAPHORE STILL WORKING**//
		if (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) < 0){
			if (sh_log) std::cout << "\033[1;31m[ViewerRT::get_parameters] The semaphore is offline\033[0m" << std::endl;
			return(false);}
	
							
			
		//**WRITE THE INSTRUCTION**//
		instruction instruction_to_send;
		instruction_to_send.instruction = GET_CONFIGURATION;
						
			
					
		//**STORE THE SEMAPHORE VALUE**//
		int ticket;
		ticket = semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL);
			
			
			
		//**INCREASE THE SEMAPHORE VALUE IN ONE UNIT**//
		semctl(semid,SEM_CHECK_INSTRUCTION,SETVAL,ticket + 1);
			
			
			
		//**WAIT UNTIL THE SEMAPHORE VALUE IS EQUAL TO STORED VALUE**//
		while (semctl(semid,SEM_CHECK_INSTRUCTION,GETVAL) > ticket){}
			
			
			
		//**SEND THE INSTRUCTION BY THE PIPE**//
		write(instructions_pipe[1], &instruction_to_send, sizeof(instruction_to_send));
			
			
			
		//**READ ADDITIONAL INFO**//
		read(info_pipe[0], config, sizeof(*config));
			

		//**RETURN TO MAIN PROCESS**//
		return(true);}
	
#endif
