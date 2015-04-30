#ifndef ROOMSHAPEDETECTOR_H
#define ROOMSHAPEDETECTOR_H
	//-> Own libraries
	#include "PointCloudXYZConectedTool.h"
	
	
	//-> libraries	
	#include <pcl/filters/voxel_grid.h>
	#include <pcl/filters/extract_indices.h>
	#include <pcl/console/time.h>
	#include <pcl/surface/concave_hull.h>
	#include <pcl/segmentation/sac_segmentation.h>


	class RoomShapeDetector{
		
		public:
			//***PUBLIC VARIABLES***//
			bool sh_log;
			bool developer;
			
			
			//***PUBLIC STRUCTURES***//
			
				//-> USED STRUCTURES	
				struct projection{
					pcl::PointCloud<pcl::PointXYZ> projection;
					std::vector <int> plane_index;};
				
				struct projection_density{
					pcl::PointCloud<pcl::PointXYZ> projection;
					std::vector <int> density;
					std::vector <int> plane_index;};
				
				
				//-> GENERAL 
					//-> Particular phase data info
					struct phase_general_info{
						bool complete;
						double time;};
					
					
					//-> Configuration
					struct general_config{
						pcl::PointXYZ laser_z_axis;
						pcl::PointXYZ laser_ref_axis;
						pcl::PointXYZ laser_origen;
						std::vector <float> laser_xy_plane;};				
				
				
				
				//-> PHASE 1, Reduce the number of points in the cloud and set a lower bound of the distance between points for the next process
					//-> Data info
					struct phase1_info{
						pcl::PointCloud<pcl::PointXYZ> cloud_filtered;};
					
					
					//-> Configuration
					struct phase1_config{
						float grid;
						int min_filter_cloud;};
					
				//-> PHASE 2, Find the wall planes and classify them as lateral, upper or lower. Discard those that are no valid for the model
					//-> Data info
					struct phase2_info{
						bool process_over_cycles;
						bool cloud_left_under_limit;
						std::vector <pcl::PointCloud<pcl::PointXYZ> > found_plane_points;
						std::vector <pcl::PointIndices>  I_found_plane_points;
						PointCloudXYZConected planes;};
					
					
					//-> Configuration
					struct phase2_config{
						int max_cycles;
						int min_point_left;
						int min_extracted_points;
						float min_relation_SE;
						bool SACSegmentation_OptimizeCoefficients;
						int SACSegmentation_MaxIterations;
						float SACSegmentation_DistanceThreshold;
						float Concave_Hull_Alpha;
						pcl::PointXYZ Z_refence_dir;
						float L_plane_angle_allowed;
						float U_plane_angle_allowed;};			
					
				
				//-> PHASE 3, Get the line coefficients for all the horizontal intersections of the model
					//-> Data info
					struct phase3_info{
						std::vector<int> lateral_planes;
						PointCloudXYZConected lines;};		

					
					
					//-> Configuration
					struct phase3_config{
						int min_allowed_planes;};
					
				
				//-> PHASE 4, Get a first approximation for the lateral shape of the room
					//-> Data info
					struct phase4_info{
						std::vector <int> filter_values;
						int commnon_filter_value;
						std::vector <projection> projections;
						std::vector <projection_density> filter_projections; 
						PointCloudXYZConected segments;
						PointCloudXYZConected no_filtered_segments;};
					
					
					//-> configuration
					struct phase4_config{
						double grid_error;
						bool common_filter_activate;
						float percentil;
						int min_percentil_val;};			
					
				
				//-> PHASE 5, Identify and erase incoherent segments for the calculated lateral shape	
					//-> Data info
					struct phase5_info{
						std::vector <int> deleted_index;
						std::vector <int> deleted_segments;
						std::vector <int> added_segments;
						std::vector <int> added_index;
						PointCloudXYZConected initial_segments;
						PointCloudXYZConected segments;};
					
					
					//-> configuration
					struct phase5_config{};			
					
				
				//-> PHASE 6, Use the lateral shape to generate the connected points that will describe the room shape
					//-> Data info
					struct phase6_info{
						std::vector <int> plane_sequence;
						PointCloudXYZConected V_lines;
						PointCloudXYZConected reconstruction_points;};
					
					
					//-> Configuration
					struct phase6_config{
						float case_1_angle;};
					
				
				//-> PHASE 7, Complete the missing connections of the connected points and create new connected points using the horizontal planes
					//-> Data info
					struct phase7_info{
						std::vector<int> upper_points_index;
						std::vector<int> lower_points_index;
						PointCloudXYZConected H_lines;
						PointCloudXYZConected reconstruction_points;};
					
					
					//-> Configuration
					struct phase7_config{};
				
			
				//-> Bulk structures
					//-> Data info
					struct process_data{
						//-> General data
						pcl::PointCloud<pcl::PointXYZ> cloud;
						
						phase_general_info GI_phase0;
					
						phase_general_info GI_phase1;
						phase1_info phase1;
						
						phase_general_info GI_phase2;
						phase2_info phase2;
						
						phase_general_info GI_phase3;
						phase3_info phase3;
						
						phase_general_info GI_phase4;
						phase4_info phase4;
						
						phase_general_info GI_phase5;
						phase5_info phase5;
						
						phase_general_info GI_phase6;
						phase6_info phase6;
						
						phase_general_info GI_phase7;
						phase7_info phase7;};
				
					
					//-> Configuration
					struct config_parameters{
						general_config general;
						phase1_config phase1;
						phase2_config phase2;
						phase3_config phase3;
						phase4_config phase4;
						phase5_config phase5;
						phase6_config phase6;
						phase7_config phase7;};
				

			
			//***PUBLIC FUNCTIONS***//
			
			RoomShapeDetector();
			~RoomShapeDetector();
			
			bool get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected* conected_cloud_out);
			bool get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, struct config_parameters* config_in, PointCloudXYZConected* conected_cloud_out);
			bool get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected* conected_cloud_out, struct process_data* data_out);
			bool get_room_shape(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, struct config_parameters* config_in,  PointCloudXYZConected* conected_cloud_out, struct process_data* data_out);
			
			bool set_default_configuration();
			bool get_default_configuration(struct config_parameters* config_out);
		

		
		private:
			//***PRIVATE STRUCTURES***//
			process_data *data;
			config_parameters *config;
			
			
			
			//***PRIVATE FUCNTIONS***//
			//-> Manage process phases
			bool manage_process(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, PointCloudXYZConected* conected_cloud_out);
			
			
			//-> Initialize store data
			bool initialize_stored_data();
			
			//-> PHASE 0: Check if the configuration values are ok. Set the default values for the wrong values
			bool phase0();
			
			//-> PHASE 1: Reduce the number of points in the cloud and set a lower bound of the distance between points for the next process
			bool phase1();
			
			//-> PHASE 2: Find the wall planes and classify them as lateral, upper or lower. Discard those that are no valid for the model
			bool phase2();
			
			//-> PHASE 3: Get the line coefficients for all the horizontal intersections of the model
			bool phase3();
			
			//-> PHASE 4: Get a first approximation for the lateral shape of the room
			bool phase4();
			
			//-> PHASE 5: Identify and erase incoherent segments for the calculated lateral shape
			bool phase5();
			
			//-> PHASE 6: Use the lateral shape to generate the connected points that will describe the room shape
			bool phase6();
			
			//-> PHASE 7: Complete the missing connections of the connected points and create new connected points using the horizontal planes
			bool phase7();
			
			//-> END PROCESS
			bool release_memory();};
			
	
	#include "RoomShapeDetector.hpp"
#endif
