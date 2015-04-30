#ifndef PCL_TOOLS_H
#define PCL_TOOLS_H
	
	//-> Libraries
	#include <pcl/io/vtk_lib_io.h>


	class PCLtools{
		
		public:

			 
			
			
			//**CONSTRUCTOR AND DESTRUCTOR**//
			PCLtools();
			~PCLtools();
		
		
			//**FOR DELETE DE VALUE FROM THE VECTOR POSITION I (INT VECTOR)**//
			bool delete_i_vector_value(std::vector<int> vector_in, int position, std::vector<int> *vector_out);
			bool delete_i_vector_value(std::vector<float> vector_in, int position, std::vector<float> *vector_out);
			
			
			//**COMPARE ARRAY**//
			bool compare_array(std::vector<int> vector_A, std::vector<int> vector_B);
			
			
			//**CONVERT ARRAY**//
			//**CONVERT ARRAY**//
			bool int_2_bool(std::vector<int> vector_in, std::vector<bool> *vector_out);
			bool int_2_double(std::vector<int> vector_in, std::vector<double> *vector_out);
			bool int_2_float(std::vector<int> vector_in, std::vector<float> *vector_out);
			bool double_2_int(std::vector<double> vector_in, std::vector<int> *vector_out);
			bool double_2_float(std::vector<double> vector_in, std::vector<float> *vector_out);
			bool double_2_bool(std::vector<double> vector_in, std::vector<bool> *vector_out);
			bool float_2_int(std::vector<float> vector_in, std::vector<int> *vector_out);
			bool float_2_double(std::vector<float> vector_in, std::vector<double> *vector_out);
			bool float_2_bool(std::vector<float> vector_in, std::vector<bool> *vector_out);
			bool bool_2_int(std::vector<bool> vector_in, std::vector<int> *vector_out);
			bool bool_2_float(std::vector<bool> vector_in, std::vector<float> *vector_out);
			bool bool_2_double(std::vector<bool> vector_in, std::vector<double> *vector_out);
			
			
			//**DELETE DUPLICATED VALUES**//
			bool delete_duplicated_values(std::vector<int> vector_in, std::vector<int> *vector_out);
			bool delete_duplicated_values(std::vector<float> vector_in, std::vector<float> *vector_out);
			
			
			//**ORGANIZE VECTOR IN DESCENDING MODE**//
			bool organize_vector_descending(std::vector<int> vector_in, std::vector<int> *vector_out);
			bool organize_vector_descending(std::vector<float> vector_in, std::vector<float> *vector_out);			
			bool organize_vector_descending(std::vector<double> vector_in, std::vector<double> *vector_out);						
			bool organize_vector_descending(std::vector<double> vector_in, std::vector<int> reference_in, std::vector<double> *vector_out);
			bool organize_vector_descending(std::vector<double> vector_in, std::vector<float> reference_in, std::vector<double> *vector_out);
			bool organize_vector_descending(std::vector<double> vector_in, std::vector<double> reference_in, std::vector<double> *vector_out);
			bool organize_vector_descending(std::vector<int> vector_in, std::vector<int> reference_in, std::vector<int> *vector_out);
			bool organize_vector_descending(std::vector<int> vector_in, std::vector<double> reference_in, std::vector<int> *vector_out);
			bool organize_vector_descending(std::vector<int> vector_in, std::vector<float> reference_in, std::vector<int> *vector_out);
			bool organize_vector_descending(std::vector<float> vector_in, std::vector<double> reference_in, std::vector<float> *vector_out);
			bool organize_vector_descending(std::vector<float> vector_in, std::vector<float> reference_in, std::vector<float> *vector_out);
			bool organize_vector_descending(std::vector<float> vector_in, std::vector<int> reference_in, std::vector<float> *vector_out);	
			bool organize_vector_descending(std::vector<bool> vector_in, std::vector<float> reference_in, std::vector<bool> *vector_out);
			bool organize_vector_descending(std::vector<bool> vector_in, std::vector<double> reference_in, std::vector<bool> *vector_out);
			bool organize_vector_descending(std::vector<bool> vector_in, std::vector<int> reference_in, std::vector<bool> *vector_out);
			
			
			//**ORGANIZE VECTOR IN ASCENDING MODE**//
			bool organize_vector_ascending(std::vector<int> vector_in, std::vector<int> *vector_out);
			bool organize_vector_ascending(std::vector<float> vector_in, std::vector<float> *vector_out);			
			bool organize_vector_ascending(std::vector<double> vector_in, std::vector<double> *vector_out);						
			bool organize_vector_ascending(std::vector<double> vector_in, std::vector<int> reference_in, std::vector<double> *vector_out);
			bool organize_vector_ascending(std::vector<double> vector_in, std::vector<float> reference_in, std::vector<double> *vector_out);
			bool organize_vector_ascending(std::vector<double> vector_in, std::vector<double> reference_in, std::vector<double> *vector_out);
			bool organize_vector_ascending(std::vector<int> vector_in, std::vector<int> reference_in, std::vector<int> *vector_out);
			bool organize_vector_ascending(std::vector<int> vector_in, std::vector<double> reference_in, std::vector<int> *vector_out);
			bool organize_vector_ascending(std::vector<int> vector_in, std::vector<float> reference_in, std::vector<int> *vector_out);
			bool organize_vector_ascending(std::vector<float> vector_in, std::vector<double> reference_in, std::vector<float> *vector_out);
			bool organize_vector_ascending(std::vector<float> vector_in, std::vector<float> reference_in, std::vector<float> *vector_out);
			bool organize_vector_ascending(std::vector<float> vector_in, std::vector<int> reference_in, std::vector<float> *vector_out);	
			bool organize_vector_ascending(std::vector<bool> vector_in, std::vector<float> reference_in, std::vector<bool> *vector_out);
			bool organize_vector_ascending(std::vector<bool> vector_in, std::vector<double> reference_in, std::vector<bool> *vector_out);
			bool organize_vector_ascending(std::vector<bool> vector_in, std::vector<int> reference_in, std::vector<bool> *vector_out);
			
			
			
			//**ANGLE_BETWEEN_TWO_VECTORS **//
			bool angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, double *angle);
			bool angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, float *angle);			
			bool angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, double *angle);
			bool angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, float *angle);
			
			
			//**FULL ANGLE_BETWEEN_TWO_VECTORS **//
			bool full_angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, double *angle);
			bool full_angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, float *angle);
			bool full_angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, double *angle);
			bool full_angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, float *angle);
			
		
			//**GET VECTOR PRODUCT**//
			bool vector_procuct(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ *product_out);
			
			
			//**GET SCALAR PRODUCT**//
			bool scalar_product(pcl::PointXYZ v1, pcl::PointXYZ v2, float *product_out);
			bool scalar_product(pcl::PointXYZ v1, pcl::PointXYZ v2, double *product_out);
			
			
			//**GET VECTOR MODULE**//
			bool vector_module(pcl::PointXYZ v1, pcl::PointXYZ reference, float *module_out);
			bool vector_module(pcl::PointXYZ v1, pcl::PointXYZ reference, double *module_out);
			bool vector_module(pcl::PointXYZ v1, float *module_out);
			bool vector_module(pcl::PointXYZ v1, double *module_out);
			
			
			//**NORMALIZE VECTOR**//
			bool normalize_vector(pcl::PointXYZ V, pcl::PointXYZ *Vn);
			
			
			//**GET CDM (centre of gravity)**//
			bool get_CDM(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointXYZ *cdm);
			
			
			//**GET THE TWO FARTHEST POINTS IN A CLOUD**//
			bool Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match, int *index1, int *index2);
			bool Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match_exceptions, pcl::PointXYZ *P1, pcl::PointXYZ *P2);
			bool Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, int *index1, int *index2);
			bool Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointXYZ *P1, pcl::PointXYZ *P2);
			
			
			
			
			//**GET THE TWO CLOSEST POINTS**//
			bool Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match, int *index1, int *index2);
			bool Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match_exceptions, pcl::PointXYZ *P1, pcl::PointXYZ *P2);
			bool Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, int *index1, int *index2);
			bool Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointXYZ *P1, pcl::PointXYZ *P2);
			
			
			
			//**MAKE A POINTS MESH INSIDE A POLYGON**//
			bool make_point_mesh_inside_polygon(pcl::PolygonMesh *polymesh_in, float density, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out);
			
			
			//**MAKE A POINT MESH WITH TWO POINTS AND THE NUMER OF DIVISIONS**//
			bool mesh_line_with_divisions(pcl::PointXYZ point_A, pcl::PointXYZ point_B, float div, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out);
	
	
			//**MAKE A POINT MESH WITH TWO POINTS AND THE DISTANCE BETWEEN THE POINTS**//
			bool mesh_line_with_gap(pcl::PointXYZ point_A, pcl::PointXYZ point_B, float gap, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out);
			bool mesh_line_with_gap(pcl::PointXYZ point_A, pcl::PointXYZ point_B, float gap, float *div_out, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out);
			
			
			//** GET INTERSECTION BETWEEN LINE AND PLANE**//
			bool inter_with_line_and_plane(std::vector <float> plane_in, std::vector <float> line_in, pcl::PointXYZ *point_out);
			
			
			//**GET THE POINT FOR AN INTERCEPTION OF THREE PLANES**//
			bool inter_with_three_planes (std::vector <float> *plane_A, std::vector <float> *plane_B, std::vector <float> *plane_C, pcl::PointXYZ *intersection);
			bool inter_with_three_planes (std::vector <float> plane_A, std::vector <float> plane_B, std::vector <float> plane_C, pcl::PointXYZ *intersection);
			
		
			//**GET THE LINE COEFICIENTS FROM AN INTERSECPTION OF TWO PLANES**//
			bool inter_with_two_planes (std::vector <float> *plane_A, std::vector <float> *plane_B, std::vector <float> *line_out);
			bool inter_with_two_planes (std::vector <float> plane_A, std::vector <float> plane_B, std::vector <float> *line_out);

			
			//**GET THE PLANE COEFFICIONES **//
			bool get_plane_coefficients (pcl::PointXYZ point_A, pcl::PointXYZ point_B, pcl::PointXYZ point_C, std::vector <float> *plane_coeficcients);
			bool get_plane_coefficients (pcl::PointXYZ point_a, pcl::PointXYZ normal_vector, std::vector <float> *plane_coeficcients);
			
			
			//**DISTANCE BETWEEN POINT TO PLANE**//
			bool distance_between_point_2_plane(std::vector <float> plane_coeficcients_in, pcl::PointXYZ point_in, float *distance);
			bool distance_between_point_2_plane(std::vector <float> plane_coeficcients_in, pcl::PointXYZ point_in, double *distance);
			
			
			//**EXTRACT A POINTS FROM A POINT CLOUUD**//
			bool extract_point_from_the_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, int index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out);
			
			
			//**EXTRACT INDEX FROM CLOUD**//
			bool extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<int> *index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out);
			bool extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<int> *index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, bool invert_index);
			bool extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointIndices::Ptr index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out);
			bool extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointIndices::Ptr index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, bool invert_index);
			
			
			//**CONVERT POINTINDICES TO VECTOR INT**//
			bool convert_pointindices_2_int_vector(pcl::PointIndices::Ptr index_in, std::vector<int> *index_out);
			
			//**PUBLIC VARIABLES**//
			bool sh_log;
			bool sh_Wlog;
	
			
		private:
		
			//**CONSTANTS**//
			#define double_PI  3.14159265358979323846 
			#define float_PI   3.14159
			#define allowed_error 1e-5
};	
	
	
	#include "PCLtools.hpp"
#endif

