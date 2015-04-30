#ifndef PointCloudXYZConectedTool_H
#define PointCloudXYZConectedTool_H
	//-> local libraries
	#include "PointCloudXYZConected.h"
	#include "PCLtools.h"
	
	
	//-> PCL libraries
	#include <pcl/io/vtk_io.h>
	#include <pcl/filters/project_inliers.h>
	
	
	class PointCloudXYZConectedTool{
		
		public:

			PointCloudXYZConectedTool();
			~PointCloudXYZConectedTool();
		
			//**SAVE CONECTED POINTS FILE**// 
			bool save_shape_as_vtk_file(PointCloudXYZConected conected_cloud, const char* name);
			bool save_shape_as_vtk_file(PointCloudXYZConected conected_cloud, const char* name, int recurrent);
			
			
			//**SAVE SHAHPE AS A STL FILE**//
			bool save_shape_as_STL_file(PointCloudXYZConected conected_cloud,const char* name);
			bool save_shape_as_STL_file(PointCloudXYZConected conected_cloud,const char* name, int recurrent);
			
	
			//**LOAD CONECTED FILE**//
			bool load_shape_from_vtk_fie(PointCloudXYZConected *conected_cloud, const char* name);
	
			
			//**CONVERT FROM PointXYZC TO PolygonMesh**//
			bool PointXYZC_2_PolygonMesh(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out);
			bool PointXYZC_2_PolygonMesh(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out, int recurrent);
			
			
			//**CONVERT FROM PointXYZC to PolygonMesh_STL**//
			bool PointXYZC_2_PolygonMesh_STL(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out);
			bool PointXYZC_2_PolygonMesh_STL(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out, int recurrent);
	
	
			//**CONVERT FROM PolygonMesh TO PointXYZC**//
			bool PolygonMesh_2_PointXYZC(pcl::PolygonMesh *polymesh_in, PointCloudXYZConected *conected_cloud_out);
			
			
			//**CONVERT FROM PointXYZC TO PointCloudXYZ**//
			bool PointXYZC_2_PointCloudXYZ(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
			
			
			//**CONVERT FROM PolygonMesh to PolygonMesh_STL**//
			bool PolygonMesh_2_PolygonMesh_STL(pcl::PolygonMesh *polymesh_in, pcl::PolygonMesh *polymesh_out);
			
			
			//**CONVERT FROM PointXYZC to edge_point_mesh**//
			bool PointXYZC_2_Edge_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float gap);
			bool PointXYZC_2_Edge_Point_Mesh(PointCloudXYZConected conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float gap);
			bool PointXYZC_2_Edge_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, bool one_mesh_direction, float gap);
			
			
			//**CONVERT FROM PointXYZC TO Point_mesh**//
			bool PointXYZC_2_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float density);
			bool PointXYZC_2_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float density, int recurrent);

			
			//**CONVERT FROM PLANE_COEF STRUCTURE TO PLANE VECTOR COEFFICIENTS **//
			bool PlaneCoef_2_vector_coefficients(Plane_coef Plane_coef_in, std::vector<float> *vector_coeff);
			

			//**CONVERT FROM PLANE VECTOR COEFFICIENTS  TO PLANE_COEF STRUCTURE**//	
			bool vector_coefficients_2_PlaneCoef(std::vector<float> vector_coeff_in, Plane_coef *Plane_coef_out);

			
			//**CONVERT FROM PLANE_COEF STRUCTURE TO PLANE VECTOR COEFFICIENTS **//
			bool line_coef_2_vector_coefficients(line_coef line_coef_in, std::vector<float> *vector_coeff_out);
	
	
			//**CONVERT FROM PLANE VECTOR COEFFICIENTS  TO PLANE_COEF STRUCTURE**//
			bool vector_coefficients_2_line_coef(std::vector<float> vector_coeff_in, line_coef *line_coef_out);
			
			
			//**EXTRACT INDEX FROM POINTCLOUD XYZ CONNECTED**//
			bool extract_index_from_pointcloudXYZC(PointCloudXYZConected *conected_cloud_in, std::vector<int> *index, PointCloudXYZConected *conected_cloud_out, bool invert_index);
			bool extract_index_from_pointcloudXYZC(PointCloudXYZConected *conected_cloud_in, std::vector<int> *index, PointCloudXYZConected *conected_cloud_out);
			bool extract_index_from_pointcloudXYZC(PointCloudXYZConected conected_cloud_in, std::vector<int> index, PointCloudXYZConected *conected_cloud_out);
				
			
			//**COMBINE CONNECTED POINT CLOUDS**//
			bool combine_connected_point_clouds(PointCloudXYZConected cloud_in1, PointCloudXYZConected cloud_in2, PointCloudXYZConected *cloud_out);
			bool combine_connected_point_clouds(PointCloudXYZConected *cloud_in1, PointCloudXYZConected *cloud_in2, PointCloudXYZConected *cloud_out);
			bool combine_connected_point_clouds(std::vector<PointCloudXYZConected> clouds, PointCloudXYZConected *cloud_out);
			bool combine_connected_point_clouds(std::vector<PointCloudXYZConected> *clouds, PointCloudXYZConected *cloud_out);
			
			
			//**DELETE DUPLICATED PLANES**//
			bool delete_duplicated_planes(std::vector <Plane_coef> planes_in, std::vector<int> *mapping, std::vector <Plane_coef> *planes_out);
			bool delete_duplicated_planes(std::vector <Plane_coef> *planes_in, std::vector<int> *mapping, std::vector <Plane_coef> *planes_out);
			
			
			//**DELETE DUPLICATED LINES**//
			bool delete_duplicated_lines(std::vector <line_coef> lines_in, std::vector<int> *mapping, std::vector <line_coef> *lines_out);
			bool delete_duplicated_lines(std::vector <line_coef> *lines_in, std::vector<int> *mapping, std::vector <line_coef> *lines_out);
			
			
			//**DELETE DUPLICATED SEGMENT**//
			bool delete_duplicated_segments(std::vector <segment_description> segments_in, std::vector<int> *mapping, std::vector <segment_description> *segments_out);
			bool delete_duplicated_segments(std::vector <segment_description> *segments_in, std::vector<int> *mapping, std::vector <segment_description> *segments_out);
			
			
			//**COMPARE PLANES**//
			bool compare_planes(Plane_coef plane1, Plane_coef plane2);
	
	
			//**COMPARE LINES**//
			bool compare_lines(line_coef line1, line_coef line2);
	
	
			//**COMPARE PLANES**//
			bool compare_segments(segment_description segment1, segment_description segment2);
			
			
			//**DISPLAY CONNECTED CLOUD INFO**//
			bool display_points_info(PointCloudXYZConected cloud, bool color);
			bool display_plane_info(PointCloudXYZConected cloud, bool color);
			bool display_line_info(PointCloudXYZConected cloud, bool color);
			bool display_segment_info(PointCloudXYZConected cloud, bool color);
			
			
			//**PUBLIC VARIABLES**//
			bool sh_log;
			std::vector<float>  *develop_float;
			std::vector<int>  *develop_int;};
		

	#include "PointCloudXYZConectedTool.hpp"
#endif

