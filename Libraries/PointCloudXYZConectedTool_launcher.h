#ifndef PointCloudXYZConectedTool_LAUNCHER_H
#define PointCloudXYZConectedTool_LAUNCHER_H

#include "PointCloudXYZConectedTool.h"
#include "ViewerRT.h"




	class PointCloudXYZConectedTool_launcher
		{
		
		public:

			PointCloudXYZConectedTool_launcher (PointCloudXYZConected *cloud_in, ViewerRT *viewer_in);	
			~PointCloudXYZConectedTool_launcher ();	

			//Public launchers
			void launcher_1 ();
		
		
		private:
			PointCloudXYZConectedTool *PointCloudXYZConectedTool_ob;
			PointCloudXYZConected *cloud;
			pcl::PolygonMesh *polymesh;
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_XYZ;
			ViewerRT *viewer;
			bool viewer_shared;
			
			
			int get_display_window();

};	
	#include "PointCloudXYZConectedTool_launcher.hpp"
#endif

