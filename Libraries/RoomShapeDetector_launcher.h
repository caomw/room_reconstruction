#ifndef ROOMSHAPEDETECTOR_LAUNCHER_H
#define ROOMSHAPEDETECTOR_LAUNCHER_H

#include "RoomShapeDetector.h"
#include "ViewerRT_launcher.h"
#include "PointCloudXYZConectedTool.h"
#include "PointCloudXYZConectedTool_launcher.h"
#include "ViewerRT.h" 


	class RoomShapeDetector_launcher{
		
		public:

			RoomShapeDetector_launcher(ViewerRT *viewer_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected *cloudC_in);	
			~RoomShapeDetector_launcher();	
			
			void launcher_1();
			
			
		private:
			
			ViewerRT *viewer;
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
			PointCloudXYZConected *cloudC;
			RoomShapeDetector *Detector;
			RoomShapeDetector::process_data* data_out;
			RoomShapeDetector::config_parameters *config;
			
			int get_display_window();
			
			bool rotation_enable;
			
			//-> Process sub menu
			void sub_launcher_1();
			void sub_launcher_2();
			
			
			//-> Phases sub menus
			void sub_launcher_phase1();
			void sub_launcher_phase2();
			void sub_launcher_phase3();
			void sub_launcher_phase4();
			void sub_launcher_phase5();
			void sub_launcher_phase6();
			void sub_launcher_phase7();
			void sub_launcher_results();};
		
	
	#include "RoomShapeDetector_launcher.hpp"
#endif

