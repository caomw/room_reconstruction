#ifndef POINT_CLOUD_XYZ_CONECTED_H
#define POINT_CLOUD_XYZ_CONECTED_H
	
	//-> Libraries
	#include <pcl/point_types.h>

	struct PointXYZC {
		pcl::PointXYZ p;
		std::vector <int> linear_conexion_index;
		std::vector <int> plane_index;
		std::vector <int> line_index;
		std::vector <int> segment_index;};


	struct Plane_coef {
		float a;
		float b;
		float c;
		float d;
		int type;
		float SE_relation;
		bool valid;
		float Zangle;};


	struct line_coef {
		float x;
		float y;
		float z;
		float vx;
		float vy;
		float vz;
		std::vector <int> plane_index;};

		
	struct segment_description{
		int density;
		pcl::PointXYZ start_point;
		pcl::PointXYZ end_point;
		std::vector <int> plane_index;
		std::vector <int> line_index;};

		
	class PointCloudXYZConected{
		
		public:
		PointCloudXYZConected();
		~PointCloudXYZConected();
		int size();
		void clear();
		
		bool CheckPointLineIndexStatus();
		bool CheckPointPlaneIndexStatus();
		bool CheckPointSegmentIndexStatus();
		bool CheckPointConexionsStatus();
		
		bool CheckLinePlaneIndexStatus();
		bool CheckSegmentPlaneIndexStatus();
		bool CheckSegmentLineIndexStatus();
		
		bool CheckConnecctedPointStatus();
		bool CheckConnecctedPointStatus(bool *PointPlaneIndexStatus, bool *PointLineIndexStatu, bool *PointSegmentIndexStatus, bool *PointConexionsStatus);	
		
		bool CheckAllStatus();
		bool CheckAllStatus(bool *PointPlaneIndexStatus, bool *PointLineIndexStatus, bool *PointSegmentIndexStatus, bool *PointConexionsStatus, bool *LinePlaneIndexStatus, bool *SegmentPlaneIndexStatus, bool *SegmentLineIndexStatus);
		
		
		std::vector <PointXYZC> Points;
		std::vector <Plane_coef> plane;
		std::vector <line_coef> line;
		std::vector <segment_description> segment;
		
		private:
	};


	#include "PointCloudXYZConected.hpp"
#endif
