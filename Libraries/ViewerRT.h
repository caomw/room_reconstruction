#ifndef ViewerRT_H
#define ViewerRT_H

	//-> Libraries
	#include <sys/wait.h> 
	#include <sys/sem.h>
	#include <pcl/visualization/cloud_viewer.h>
	#include <pcl/io/vtk_lib_io.h>

 
	class ViewerRT{
		
		//**PUBLIC**//
		public:
			
			//**PUBLIC STRUCTURES**//
			struct pid_info{
				int pid;
				const char* process_name;};
			
			//->Config components
			struct back_ground_color{
				unsigned int R;
				unsigned int G;
				unsigned int B;};	
			struct win_size{
				unsigned int x;
				unsigned int y;};	
			struct view_point{
				int x0;
				int x1;
				int y0;
				int y1;
				int z0;
				int z1;};
			struct rotation_view_point{
				unsigned int kind;
				float degree_inc;
				float module_inc;
				float min_module;
				float range_module;};
			
			
			
			struct config_parameters{
				unsigned int n_windows;
				bool special_3_windows;
				unsigned int dim_cord_syst;
				bool show_cord_syst;
				struct back_ground_color back_ground_color;
				struct win_size win_size;
				bool fullscreen;
				struct view_point view_point;
				struct rotation_view_point rotation_view_point;};
			
			
			//**CONSTRUCTOR AND DESTRUCTOR**//
			ViewerRT ();	
			~ViewerRT ();
			
			
			//**RUN VIEWER**//
			bool run_viewer();
			
			
			//**CLOSE VIEWER**//
			bool close_viewer_process (bool priority);
			
			
			//**VIEWER STATE OK/OFF**//
			bool viewer_state();
			
			
			//**SET STRUCT CONFIGURATION**//
			bool set_parameters(struct config_parameters viewer_config, bool restart, bool priority);
			
			
			//**GET STRUCT CONFIGURATION**//
			bool get_parameters(struct config_parameters* config);
			
			
			//**LOAD OBJECTS**//
			bool load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, bool priority);
			bool load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, unsigned int n_cloud, unsigned int t_clouds, bool priority);
			bool load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, int id, bool priority);
			bool load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, float R, float G, float B, bool priority);
			bool load(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, unsigned int window, int id, float R, float G, float B, bool priority);
			bool load(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, unsigned int window, bool priority);
			bool load(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, unsigned int window, int id, bool priority);
			bool load(pcl::PolygonMesh polymesh, unsigned int window, bool priority);
			bool load(pcl::PolygonMesh polymesh, unsigned int window, int id, bool priority);
			
			
			//**DELETE OBJECTS**//
			bool delete_all_objets (int window, bool priority);
			bool delete_last_objets (int window, bool priority);
			bool delete_all_objets (bool priority);
			bool delete_concrete_objets (int id, bool priority);
			
			
			//**PUBLIC VECTORS**//
			std::vector <pid_info> proccess_vector;
			
			//**PUBLIC VARIABLES**//
			bool sh_log;
			bool sh_exit;
		
			
		
		
		
		//**PRIVATE**//
		private:
			
			//**INTERRUPTION HANDLER**//
			static void signalHandler(int signum);
			static void main_signalHandler(int signum);
			
			
			//**GENERAL CONTANTS**//
			bool running;
			
			//1.- Semaphore
			#define SEM_CHECK_INSTRUCTION 0
			#define SEM_TURN_TO_SEND_THE_INSTRUCTION 1
			
			
			//2.- Instructions
			#define CLOSE_VIEWER 100
			#define SET_CONFIGURATION_R 200
			#define SET_CONFIGURATION_NR 250
			#define GET_CONFIGURATION 300
			#define LOAD_XYZ 400
			#define LOAD_XYZ_2 500
			#define LOAD_XYZ_COLOR 600
			#define LOAD_XYZ_COLOR_2 700
			#define LOAD_RGB_XYZ 800
			#define LOAD_RGB_XYZ_2 900
			#define LOAD_STL 1000
			#define LOAD_STL_2 1100
			#define DELETE_LAST_ONE 1200
			#define DELETE_ALL_ONE 1300
			#define DELETE_ALL_ALL 1400
			#define DELETE_CONCRETE_OBJECT 1500
			
			
			
			
			//**GENERAL VARIABLES**//
			//-> Pipes
			int instructions_pipe[2];
			int info_pipe[2];
			//-> Main proccess
			pid_t pid;
			//->general configuration
			config_parameters viewer_config;
			
			
			//**PRIVATE STRUCTURES**// 
			struct instruction{
				int instruction;
				int bytes_in_info_pipe;
				int bytes_in_info_pipe2;
				};
			
			//**PRIVATE FUNCTIONS**//
			config_parameters inicialize_data ();};

	#include "ViewerRT.hpp"
#endif
