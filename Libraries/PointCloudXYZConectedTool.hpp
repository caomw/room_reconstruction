#ifndef PointCloudXYZConectedTool_HPP
#define PointCloudXYZConectedTool_HPP

	//**CONSTRUCTOR (PRINCIPAL MENU)**//
	PointCloudXYZConectedTool::PointCloudXYZConectedTool(){
		std::vector<float>  *develop_float_s (new std::vector<float>);
		std::vector<int>  *develop_int_s (new std::vector<int>);
		develop_float = develop_float_s;
		develop_int = develop_int_s;
		sh_log = true;
		return;}

		
	//**DESTRUCTOR**//
	PointCloudXYZConectedTool::~PointCloudXYZConectedTool(){
		return;}
	
	
	//**MAIN FUCNTIONS**//
	//**SAVE CONECTED POINTS FILE**// 
	bool PointCloudXYZConectedTool::save_shape_as_vtk_file(PointCloudXYZConected conected_cloud, const char* name){
		return(save_shape_as_vtk_file(conected_cloud, name, 0));}
	bool PointCloudXYZConectedTool::save_shape_as_vtk_file(PointCloudXYZConected conected_cloud, const char* name, int recurrent){
		
		//** CHECK IF THE CLOUD IS EMPTY **//
		if (conected_cloud.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_vtk_file] Failed to save the file,the cloud is empty\033[0m" << std::endl;
			return(false);}
		
		if (name == ""){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_vtk_file] Failed to save the file,the name variable is empty\033[0m" << std::endl;
			return(false);}
		
		//**CONVERTE PONITXYZC TO POLYMESH**//
		pcl::PolygonMesh polymesh;
		if (!PointXYZC_2_PolygonMesh(&conected_cloud, &polymesh,recurrent)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_vtk_file] Failed, can't convert to polygonmesh\033[0m" << std::endl;
			return(false);}
		
		//**SAVE THE MESH**//
		if (pcl::io::saveVTKFile (name, polymesh) < 0) {
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_vtk_file] Failed to save the VTK file\033[0m" << std::endl;
			return(false);}

		
		return(true);}
	
	
	//**SAVE SHAHPE AS A STL FILE**//
	bool PointCloudXYZConectedTool::save_shape_as_STL_file(PointCloudXYZConected conected_cloud,const char* name){
		return(save_shape_as_STL_file(conected_cloud, name, 0));}
	bool PointCloudXYZConectedTool::save_shape_as_STL_file(PointCloudXYZConected conected_cloud,const char* name, int recurrent){	
		//** CHECK IF THE CLOUD IS EMPTY **//
		if (conected_cloud.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_STL_file] Failed to save the file,the cloud is empty\033[0m" << std::endl;
			return(false);}
		
		if (name == ""){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_STL_file] Failed to save the file,the name variable is empty\033[0m" << std::endl;
			return(false);}
		
		//**CONVERTE PONITXYZC TO POLYMESH**//
		pcl::PolygonMesh polymesh;
		if (!PointXYZC_2_PolygonMesh_STL(&conected_cloud, &polymesh,recurrent)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_STL_file] Failed, can't convert to STL\033[0m" << std::endl;
			return(false);}
		
		//**SAVE THE MESH**//
		if (pcl::io::savePolygonFileSTL (name, polymesh) < 0) {
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_STL_file] Failed to save the STL file\033[0m" << std::endl;
			return(false);}

		
		return(true);}
	
	
	//**LOAD CONECTED FILE**//
	bool PointCloudXYZConectedTool::load_shape_from_vtk_fie(PointCloudXYZConected *conected_cloud_out, const char* name){
		
		
		//**LOAD vtk file**//
		pcl::PolygonMesh polymesh;
		if (pcl::io::loadPolygonFileVTK(name, polymesh) < 0) {
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_vtk_file] Failed to load the VTK file\033[0m" << std::endl;
			return(false);}
		
		
		//-> Concert to point connected
		PointCloudXYZConected conected_cloud;
		if (!PolygonMesh_2_PointXYZC(&polymesh, &conected_cloud)) {
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::save_shape_as_vtk_file] Failed, can't convert to point connected\033[0m" << std::endl;
			return(false);}
		
		*conected_cloud_out = conected_cloud;
		
		return(true);}

		
	//**CONVERT FROM PointXYZC TO PolygonMesh**//
	bool PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out){	
		return(PointXYZC_2_PolygonMesh(conected_cloud_in,polymesh_out, 0));}
	bool PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out, int recurrent){
		
		//-> check if the cloud is empty
		if (conected_cloud_in->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh] Failed to convert PointCloudXYZConected. The cloud is empty\033[0m" << std::endl;
			return(false);}
		
		
		PCLtools PCLtools;
		PointCloudXYZConected conected_cloud(*conected_cloud_in);
		pcl::PolygonMesh polymesh;
		pcl::PolygonMesh polymesh_real;
		
		
		//->For store cloud (convert to a regular cloud and transform to a cloud2)
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	

		
		//-> Check if there are any errors
		if (!PointXYZC_2_PointCloudXYZ(&conected_cloud, cloud)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh] Failed to convert PointCloudXYZConected to PointCloudXYZ.\033[0m" << std::endl;
			return(false);}
		
		//-> Get the number of recurrence if is not set or is too hight
		if (recurrent < 1 || recurrent > 999)
			for (int i=0; i < conected_cloud.size(); i++)
				if (conected_cloud.Points[i].linear_conexion_index.size() > recurrent + 2)
					recurrent = conected_cloud.Points[i].linear_conexion_index.size();
				
		
		//-> Explore the connection points (repeat the explorer action recurrent times)
		
		for (int repeat=0; repeat < recurrent; repeat++)
		for (int i=0; i < conected_cloud.size(); i++){
			
			
			//->For check if save the vertices
			bool save(true);
			
			
			//-> Check if the starting point has free connections
			if (conected_cloud.Points[i].linear_conexion_index.size() > 0){
				int start_index, find_index, last_index;
				pcl::Vertices  vertices;
				pcl::PointXYZ v1, v2;
				pcl::PointXYZ plane_normal;
				
				//->Find new combination of points 
				int frs(0);
				int scd(0);
				bool found;
				do{
					//-> Set start values
					start_index = i;
					find_index = conected_cloud.Points[i].linear_conexion_index[frs];
					last_index = i;
					
					
					//-> set false if the second poins have to be discard
					found = false;
					
									
				
					//->Reset data
					pcl::Vertices  vertices_new;
					vertices = vertices_new;
					conected_cloud = *conected_cloud_in;
					found = true;
					
					
					//**FIRST POINT**//
					//-> Store first conected point
					vertices.vertices.push_back(start_index);
					
					
					//-> Extract first conected point
					PCLtools.delete_i_vector_value(conected_cloud.Points[i].linear_conexion_index, frs, &conected_cloud.Points[i].linear_conexion_index);
					
					
					
					//**SECOND POINT**//
					//-> Store second conected point
					vertices.vertices.push_back(find_index);
					
				
					//-> Extract the before index
					for (int j=0; j < conected_cloud.Points[find_index].linear_conexion_index.size(); j++)
						if (conected_cloud.Points[find_index].linear_conexion_index[j] == last_index)
							PCLtools.delete_i_vector_value(conected_cloud.Points[find_index].linear_conexion_index, j, &conected_cloud.Points[find_index].linear_conexion_index);
					
					
					//->Find the after index
					//-> Check if there are any error
					if (conected_cloud.Points[find_index].linear_conexion_index.size() < 1){
						if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh] Failed to create the polygon from the connected points cloud (769)\033[0m" << std::endl;
						return(false);}
					
					
					//->Find next index 
					last_index = find_index;
					find_index = conected_cloud.Points[last_index].linear_conexion_index[scd];
					
					
					//-> Extract the next index from last index
					PCLtools.delete_i_vector_value(conected_cloud.Points[last_index].linear_conexion_index, scd, &conected_cloud.Points[last_index].linear_conexion_index);

					
					//**THIRD POINT**//
					//->Store the third point
					vertices.vertices.push_back(find_index);

					
					//-> Extract the before index
					for (int j=0; j < conected_cloud.Points[find_index].linear_conexion_index.size(); j++)
						if (conected_cloud.Points[find_index].linear_conexion_index[j] == last_index)
							PCLtools.delete_i_vector_value(conected_cloud.Points[find_index].linear_conexion_index, j, &conected_cloud.Points[find_index].linear_conexion_index);
					
					
					//->Get reference normal of the plane with start_index point, last_index point and find_index point
					
					v1.x = conected_cloud.Points[start_index].p.x - conected_cloud.Points[last_index].p.x;
					v1.y = conected_cloud.Points[start_index].p.y - conected_cloud.Points[last_index].p.y;
					v1.z = conected_cloud.Points[start_index].p.z - conected_cloud.Points[last_index].p.z;
					
					v2.x = conected_cloud.Points[find_index].p.x - conected_cloud.Points[last_index].p.x;
					v2.y = conected_cloud.Points[find_index].p.y - conected_cloud.Points[last_index].p.y;
					v2.z = conected_cloud.Points[find_index].p.z - conected_cloud.Points[last_index].p.z;
					
					
					//->Get normal for compare
					PCLtools.vector_procuct(v1, v2, &plane_normal);
					
					
					//->Check
					for (int j = 0; j < polymesh.polygons.size(); j++){
						//->Dublicate
						std::vector<int> vertices_compare;
						for (int k = 0; k < polymesh.polygons[j].vertices.size()-1; k++)
							vertices_compare.push_back(polymesh.polygons[j].vertices[k]);
						for (int k = 0; k < polymesh.polygons[j].vertices.size()-1; k++)
							vertices_compare.push_back(polymesh.polygons[j].vertices[k]);
						
						
						//->Check combinations
						if (start_index == find_index)
							found = false;
						
						for (int k = 1; k < vertices_compare.size()-1; k++) 
							if (vertices_compare[k] == last_index){
								if(vertices_compare[k+1] == start_index)
									if (vertices_compare[k-1] == find_index)
										found = false;
								
								if (vertices_compare[k+1] == find_index)
									if (vertices_compare[k-1] == start_index)
										found = false;}}
						
					
					
					//-> This module if for trying all possible combination between  the start_index connexion and the find_index connexions
					if (!found){
						if(frs < 2) frs++;
						else { 
							if (scd < 2){
								scd++;
								frs = 0;}
							else {
								save = false;
								found = true;}}}	
					
					
				}while(!found); 
				
				
				//-> Get plane coefficients
				float a,b,c,d;
				a=plane_normal.x;
				b=plane_normal.y;
				c=plane_normal.z;
				d=-conected_cloud.Points[start_index].p.x*a - conected_cloud.Points[start_index].p.y*b - conected_cloud.Points[start_index].p.z*c;
				
				
				//-> Identify the index of the polygons that belong to that plane
				std::vector<int> indices;
				Eigen::Vector4f model_coefficients (a , b , c , d);
				pcl::SampleConsensusModelPlane<pcl::PointXYZ>::Ptr Sample_Consensus_Model_Plane (new pcl::SampleConsensusModelPlane<pcl::PointXYZ>(cloud));
				Sample_Consensus_Model_Plane->selectWithinDistance (model_coefficients , 0.1, indices);
								
								
				//->Complete the polygon
				int count(0);
				while (start_index != find_index){					
					//-> Check if the conexions are wrong [error]
					if (conected_cloud.Points[find_index].linear_conexion_index.size() < 1){
						if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh] Failed to create the polygon from the connected points cloud (647)\033[0m" << std::endl;
						return(false);}
					

					
					//->Find possible next index (find index)
					int possible_index(-1);
					for (int j=0; j < conected_cloud.Points[find_index].linear_conexion_index.size(); j++){
						for (int k=0; k<indices.size(); k++)
							if(conected_cloud.Points[find_index].linear_conexion_index[j] == indices[k])
								if (indices[k] != find_index)
									possible_index = conected_cloud.Points[find_index].linear_conexion_index[j];}
					
						
					
					//-> check if the found index is correct
					if (possible_index > -1 || possible_index < conected_cloud.Points.size()){
					
						//**NEXT POINT**//
						//->change parameters
						last_index = find_index;
						find_index = possible_index;
						
							
						//->Store the next point
						vertices.vertices.push_back(find_index);
							
							
						//-> Extract the next index from last index
						for (int j=0; j < conected_cloud.Points[last_index].linear_conexion_index.size(); j++)
							if (conected_cloud.Points[last_index].linear_conexion_index[j] == find_index)
								PCLtools.delete_i_vector_value(conected_cloud.Points[last_index].linear_conexion_index, j, &conected_cloud.Points[last_index].linear_conexion_index);
							
							
						//-> Extract the before index
						for (int j=0; j < conected_cloud.Points[find_index].linear_conexion_index.size(); j++)
							if (conected_cloud.Points[find_index].linear_conexion_index[j] == last_index)
								PCLtools.delete_i_vector_value(conected_cloud.Points[find_index].linear_conexion_index, j, &conected_cloud.Points[find_index].linear_conexion_index);}
					
					
					//-> do not save the polygon if the index is not correct.
					else save = false;
					
					
					//-> Check cycles [error]
					if (count++ > conected_cloud.size()){
						save = false;
						start_index = find_index;}}
					
				
				//->Store vertices in polymesh
				if (save) {
					polymesh.polygons.push_back(vertices);
					vertices.vertices.pop_back();
					polymesh_real.polygons.push_back(vertices);}}}
		
				
		
		
		//Convert the points
		pcl::PCLPointCloud2 cloud2;
		pcl::toPCLPointCloud2(*cloud, cloud2);
		polymesh_real.cloud = cloud2;
		*polymesh_out = polymesh_real;
		
		
		return(true);}
	
	
	//**CONVERT FROM PointXYZC to PolygonMesh_STL**//
	bool PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh_STL(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out){
		return(PointXYZC_2_PolygonMesh_STL(conected_cloud_in, polymesh_out, 0));}
	bool PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh_STL(PointCloudXYZConected *conected_cloud_in, pcl::PolygonMesh *polymesh_out, int recurrent){
		
		pcl::PolygonMesh polymesh;
		pcl::PolygonMesh polymesh_stl;
		
		if (!PointXYZC_2_PolygonMesh(conected_cloud_in, &polymesh, recurrent)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh_STL] Failed to convert PointCloudXYZConected to PolygonMesh.\033[0m" << std::endl;
			return(false);}
		if (!PolygonMesh_2_PolygonMesh_STL(&polymesh, &polymesh_stl)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_PolygonMesh_STL] Failed to convert PolygonMesh to PolygonMesh_STL.\033[0m" << std::endl;
			return(false);}
	
		*polymesh_out = polymesh_stl;
		
		return(true);}	

		
	//**CONVERT FROM PolygonMesh TO PointXYZC**//
	bool PointCloudXYZConectedTool::PolygonMesh_2_PointXYZC(pcl::PolygonMesh *polymesh_in, PointCloudXYZConected *conected_cloud_out){
				
		//-> Declare objects
		PointCloudXYZConected conected_cloud;
		pcl::PolygonMesh polymesh(*polymesh_in);
		PCLtools PCLtools; 
		
		
		//-> Convert the cloud2 to standard cloud
		pcl::PointCloud<pcl::PointXYZ> cloud;
		pcl::fromPCLPointCloud2(polymesh.cloud,cloud);
		
		//-> Store all points without connexions
		PointXYZC conected_point;
		for (int i=0; i < cloud.size(); i++){
			conected_point.p = cloud.points[i];
			conected_cloud.Points.push_back(conected_point);}
			
		
		//-> Add connexions
		for (int i=0; i<polymesh.polygons.size(); i++){
			for (int j=0; j < polymesh.polygons[i].vertices.size(); j++){
				
				//-> get connexions
				std::vector<int> conexions_to_add;
				
				if (j+1 >= polymesh.polygons[i].vertices.size()) conexions_to_add.push_back(polymesh.polygons[i].vertices[0]);
				else conexions_to_add.push_back(polymesh.polygons[i].vertices[j+1]);				
				
				if (j-1 < 0) conexions_to_add.push_back(polymesh.polygons[i].vertices[polymesh.polygons[i].vertices.size()-1]);
				else conexions_to_add.push_back(polymesh.polygons[i].vertices[j-1]);
				
				
				//->Check if the connexions are connected
				for (int k=0; k < conexions_to_add.size(); k++){
					for (int l=0; l < conected_cloud.Points[polymesh.polygons[i].vertices[j]].linear_conexion_index.size(); l++)
						if (conected_cloud.Points[polymesh.polygons[i].vertices[j]].linear_conexion_index[l] == conexions_to_add[k]){
							if (!PCLtools.delete_i_vector_value(conexions_to_add, k--, &conexions_to_add)){
								if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PolygonMesh_2_PointXYZC] Failed, can't extract value from array\033[0m" << std::endl;
								return(false);}}}
						
				
				
				//-> Add the connexions
				for (int k=0; k < conexions_to_add.size(); k++){
					conected_cloud.Points[polymesh.polygons[i].vertices[j]].linear_conexion_index.push_back(conexions_to_add[k]);}}}
			
			
		//-> return data
		*conected_cloud_out = conected_cloud;
		
		return(true);}
		
	
	//**CONVERT FROM PointXYZC TO PointCloudXYZ**//
	bool PointCloudXYZConectedTool::PointXYZC_2_PointCloudXYZ(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){
		
		if (conected_cloud_in->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_PointCloudXYZ] Failed to convert PointCloudXYZConected. The cloud is empty\033[0m" << std::endl;
			return(false);}
		
		
		for (int i=0; i < conected_cloud_in->size(); i++)
			cloud_out->push_back(conected_cloud_in->Points[i].p);
		
	
		
		return (true);}
			
	
	//**CONVERT FROM PolygonMesh to PolygonMesh_STL**//
	bool PointCloudXYZConectedTool::PolygonMesh_2_PolygonMesh_STL(pcl::PolygonMesh *polymesh_in, pcl::PolygonMesh *polymesh_out){
		
		//-> Aux objects
		PCLtools PCLtools;
		pcl::PolygonMesh polymesh (*polymesh_in);
		pcl::PolygonMesh polymesh_finally;
		
		//-> Check if there are any polygons
		if (polymesh.polygons.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PolygonMesh_2_PolygonMesh_STL] Failed to convert PolygonMesh to PolygonMesh_STL. There is not polygons\033[0m" << std::endl;
			return(false);}
		
		//->Convert Pointcloud2 to Pointcloud
		pcl::PointCloud<pcl::PointXYZ> cloud;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cdm (new pcl::PointCloud<pcl::PointXYZ>);
		pcl::fromPCLPointCloud2(polymesh.cloud,cloud);
		
		//-> check if the cloud is not empty
		if (cloud.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PolygonMesh_2_PolygonMesh_STL] Failed to convert PolygonMesh to PolygonMesh_STL. There is points\033[0m" << std::endl;
			return(false);}
		
		
		//-> go through each polygon
		for (int i=0; i<polymesh.polygons.size(); i++){
			//-> Get the points in ordet to calculate the cdm.
			pcl::PointXYZ cdm_point;
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_vertices (new pcl::PointCloud<pcl::PointXYZ>);
			
			for (int j=0; j < polymesh.polygons[i].vertices.size(); j++)
				cloud_vertices->push_back(cloud.points[polymesh.polygons[i].vertices[j]]);

			
			//-> Get the cdm for the i polygon, save the points and make triangles with it.
			if (PCLtools.get_CDM(cloud_vertices, &cdm_point)){
				//Save the CDM
				cloud_cdm->push_back(cdm_point);
				
				
				//make the first triangle
				pcl::Vertices  vertices_initial;
				vertices_initial.vertices.push_back(polymesh.polygons[i].vertices[0]);
				vertices_initial.vertices.push_back(cloud_cdm->size() + cloud.size() - 1);
				vertices_initial.vertices.push_back(polymesh.polygons[i].vertices[polymesh.polygons[i].vertices.size() - 1]);
				
				//-> store the triangle
				polymesh_finally.polygons.push_back(vertices_initial);
				
				//make the rest of the triangle connexions
				for (int j=0; j<polymesh.polygons[i].vertices.size()-1; j++){
					pcl::Vertices  vertices;
					vertices.vertices.push_back(polymesh.polygons[i].vertices[j]);
					vertices.vertices.push_back(cloud_cdm->size() + cloud.size() - 1);
					vertices.vertices.push_back(polymesh.polygons[i].vertices[j+1]);
					
			polymesh_finally.polygons.push_back(vertices);}}}
			
		
		//-> Save the CDM vertices in the finally cloud
		for (int j=0; j <  cloud_cdm->size(); j++)
			cloud.push_back(cloud_cdm->points[j]);
	
		
		//-> check if everything was ok
		if (cloud_cdm->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PolygonMesh_2_PolygonMesh_STL] Failed to convert PolygonMesh to PolygonMesh_STL. No CDM points were saved\033[0m" << std::endl;
			return(false);}	
		if (cloud.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PolygonMesh_2_PolygonMesh_STL] Failed to convert PolygonMesh to PolygonMesh_STL. No points were saved\033[0m" << std::endl;
			return(false);}	
		if (polymesh_finally.polygons.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PolygonMesh_2_PolygonMesh_STL] Failed to convert PolygonMesh to PolygonMesh_STL. No polygons were made\033[0m" << std::endl;
			return(false);}
				
		//->convert and return the data
		pcl::PCLPointCloud2 cloud2;	
		pcl::toPCLPointCloud2(cloud, cloud2);
		polymesh_finally.cloud = cloud2;
		*polymesh_out = polymesh_finally;
		
		
	return (true);}
	

	//**CONVERT FROM PointXYZC to edge_point_mesh**//
	bool PointCloudXYZConectedTool::PointXYZC_2_Edge_Point_Mesh(PointCloudXYZConected conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float gap){
		return(PointXYZC_2_Edge_Point_Mesh(&conected_cloud_in, cloud_out,gap));}
	bool PointCloudXYZConectedTool::PointXYZC_2_Edge_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float gap){
		return(PointXYZC_2_Edge_Point_Mesh(conected_cloud_in, cloud_out, true, gap));}
	bool PointCloudXYZConectedTool::PointXYZC_2_Edge_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out,bool one_mesh_direction, float gap){
		
		
		PointCloudXYZConected conected_cloud (*conected_cloud_in);
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_edge_point_mesh (new pcl::PointCloud<pcl::PointXYZ>);
		PCLtools PCLtools;
		std::vector< std::vector<int> > v_pair;
		
		
		//-> Check if the cloud is empty
		if (conected_cloud.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_Edge_Point_Mesh] Failed to make the mesh line, the connected cloud is empty\033[0m" << std::endl;
			return(false);}
		
		
		//-> Go thought the connected points
		for (int i=0; i<conected_cloud.size(); i++){
			
			//-> Go thought the points connected
			for (int j=0; j < conected_cloud.Points[i].linear_conexion_index.size() > 0; j++){
				
				//->This is for avoid errors
				if (i != conected_cloud.Points[i].linear_conexion_index[j] ){
				
					//-> get the index to connect
					int index_to_conect(conected_cloud.Points[i].linear_conexion_index[j]);
					
					
					//-> Check if the index is out of range
					if (index_to_conect < 0 || index_to_conect >= conected_cloud_in->size()){
						if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_Edge_Point_Mesh] Failed, the connected index is out of range\033[0m" << std::endl;
						return(false);}
					
					
					
					//-> check if the pairs is already done
					bool ok(true);
					if (one_mesh_direction){
						for (int k=0; k < v_pair.size(); k++){
							if (v_pair[k][0] == i && v_pair[k][1] == index_to_conect) ok = false;
							else if (v_pair[k][1] == i && v_pair[k][0] == index_to_conect) ok = false;}}
				
					
					//-> make the mesh for the i-index_to_conect line.
					if (ok){
					pcl::PointCloud<pcl::PointXYZ>::Ptr mesh_point_line (new pcl::PointCloud<pcl::PointXYZ>);
					bool sh_log_aux(PCLtools.sh_log);
					PCLtools.sh_log = false;
					if (!PCLtools.mesh_line_with_gap(conected_cloud_in->Points[i].p, conected_cloud_in->Points[index_to_conect].p, gap, mesh_point_line)){
						mesh_point_line->push_back(conected_cloud_in->Points[i].p);
						mesh_point_line->push_back(conected_cloud_in->Points[index_to_conect].p);}
					PCLtools.sh_log = sh_log_aux;
					
					
					//-> store the pairs to check later
					std::vector<int> aux;
					aux.push_back(i);
					aux.push_back(index_to_conect);
					v_pair.push_back(aux);
					
					
					//-> store the mesh
					for (int k=0; k < mesh_point_line->size(); k++)
						cloud_edge_point_mesh->push_back(mesh_point_line->points[k]);}}}}
				
				

				
		
		//-> Sen the cloud with the point mesh edge
		*cloud_out = *cloud_edge_point_mesh;
	
		return(true);}
	
	
	//**CONVERT FROM PointXYZC TO Point_mesh**//
	bool PointCloudXYZConectedTool::PointXYZC_2_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float density){
		return(PointXYZC_2_Point_Mesh(conected_cloud_in, cloud_out, density, 0));}
	bool PointCloudXYZConectedTool::PointXYZC_2_Point_Mesh(PointCloudXYZConected *conected_cloud_in, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, float density, int recurrent){
		
		//-> check density
		if (density <= 0 ){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_Point_Mesh] Failed,the density is not correct\033[0m" << std::endl;
			return(false);}
		
		
		//-> Check if the cloud is empty
		if (conected_cloud_in->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_Point_Mesh] Failed to make the mesh line, the connected cloud is empty\033[0m" << std::endl;
			return(false);}
		
		
		//-> Get the STL polygons
		pcl::PolygonMesh polymesh;
		if (!PointXYZC_2_PolygonMesh(conected_cloud_in, &polymesh, recurrent)){
		//if (!PointXYZC_2_PolygonMesh_STL(conected_cloud_in, &polymesh, recurrent)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_Point_Mesh] Failed getting the STL polygons\033[0m" << std::endl;
			return(false);}

			
		//-> Create the PCL-tool
		PCLtools PCLtools;
		
		
		//-> Make the point-mesh with the polygons
		pcl::PointCloud<pcl::PointXYZ>::Ptr point_mesh_cloud (new pcl::PointCloud<pcl::PointXYZ>);
		if (!PCLtools.make_point_mesh_inside_polygon(&polymesh, density, point_mesh_cloud)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_Point_Mesh] Failed getting the point-mesh polygons\033[0m" << std::endl;
			return(false);}
		
		
		//-> Check if the cloud is OK
		if (point_mesh_cloud->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::PointXYZC_2_Point_Mesh] Failed, the returned cloud is empty\033[0m" << std::endl;
			return(false);}
		
		
		//-> Return data
		*cloud_out = *point_mesh_cloud;
		
		
		return(true);}
	
	
	//**CONVERT FROM PLANE_COEF STRUCTURE TO PLANE VECTOR COEFFICIENTS **//
	bool PointCloudXYZConectedTool::PlaneCoef_2_vector_coefficients(Plane_coef Plane_coef_in, std::vector<float> *vector_coeff_out){
		vector_coeff_out->push_back(Plane_coef_in.a);
		vector_coeff_out->push_back(Plane_coef_in.b);
		vector_coeff_out->push_back(Plane_coef_in.c);
		vector_coeff_out->push_back(Plane_coef_in.d);
		return(true);}	
	
	
	//**CONVERT FROM PLANE VECTOR COEFFICIENTS  TO PLANE_COEF STRUCTURE**//
	bool PointCloudXYZConectedTool::vector_coefficients_2_PlaneCoef(std::vector<float> vector_coeff_in, Plane_coef *Plane_coef_out){
		//-> Check
		if (vector_coeff_in.size() < 4){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::vector_coefficients_2_PlaneCoef] Failed, the coefficients vector size is not correct\033[0m" << std::endl;
			return(false);}
		
		Plane_coef Plane_coef_aux;
		Plane_coef_aux.a = vector_coeff_in[0];
		Plane_coef_aux.b = vector_coeff_in[1];
		Plane_coef_aux.c = vector_coeff_in[2];
		Plane_coef_aux.d = vector_coeff_in[3];
		
		*Plane_coef_out = Plane_coef_aux;
		
		
		return(true);}
	
	
	//**CONVERT FROM LINE_COEF STRUCTURE TO LINE VECTOR COEFFICIENTS **//	
	bool PointCloudXYZConectedTool::line_coef_2_vector_coefficients(line_coef line_coef_in, std::vector<float> *vector_coeff_out){
		vector_coeff_out->push_back(line_coef_in.x);
		vector_coeff_out->push_back(line_coef_in.y);
		vector_coeff_out->push_back(line_coef_in.z);
		vector_coeff_out->push_back(line_coef_in.vx);
		vector_coeff_out->push_back(line_coef_in.vy);
		vector_coeff_out->push_back(line_coef_in.vz);

		return(true);}	
	
	
	//**CONVERT FROM LINE VECTOR COEFFICIENTS  TO LINE_COEF STRUCTURE**//
	bool PointCloudXYZConectedTool::vector_coefficients_2_line_coef(std::vector<float> vector_coeff_in, line_coef *line_coef_out){
		//-> Check
		if (vector_coeff_in.size() < 6){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::vector_coefficients_2_line_coef] Failed, the coefficients vector size is not correct\033[0m" << std::endl;
			return(false);}
		
		line_coef line_coef_aux;
		line_coef_aux.x = vector_coeff_in[0];
		line_coef_aux.y = vector_coeff_in[1];
		line_coef_aux.z = vector_coeff_in[2];
		line_coef_aux.vx = vector_coeff_in[3];
		line_coef_aux.vy = vector_coeff_in[4];
		line_coef_aux.vz = vector_coeff_in[5];
		
		*line_coef_out = line_coef_aux;
		
		
		return(true);}
	
	
	//**EXTRACT INDEX FROM POINTCLOUD XYZ CONNECTED**//
	bool PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC(PointCloudXYZConected *conected_cloud_in, std::vector<int> *index, PointCloudXYZConected *conected_cloud_out, bool invert_index){
		//-> Declare array
		std::vector<int> out_index;
		
		
		//-> Return value if the index array is empty
		if (index->size() < 1 && invert_index){
			*conected_cloud_out = *conected_cloud_in;
			return (true);}
		
		
		//-> Return value if the index array is empty
		if (index->size() < 1 && !invert_index){
			PointCloudXYZConected conected_cloud;
			*conected_cloud_out = conected_cloud;
			return (true);}
		
		//-> Invert index
		if (invert_index){
			
			//-> Organize index array
			PCLtools PCLtools;
			std::vector<int> organized_index(*index);
			if (!PCLtools.organize_vector_ascending(organized_index, &organized_index)){
				if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC] Failed, can't organize the invert index array\033[0m" << std::endl;
				return(false);}	
		
		
			//-> Generate the negative index array
			int last_value(-1);
			for (int i=0; i < organized_index.size(); i++){
				for (int j=	last_value+1; j < organized_index[i]; j++)
					out_index.push_back(j);
				
				last_value	= organized_index[i];}
				
				
			for (int i=last_value +1; i < conected_cloud_in->size(); i++){
				out_index.push_back(i);}}
		
		
		//-> Do not invert index			
		else {out_index = *index;}
		
		return(extract_index_from_pointcloudXYZC(conected_cloud_in, &out_index, conected_cloud_out));}
	bool PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC(PointCloudXYZConected conected_cloud_in, std::vector<int> index, PointCloudXYZConected *conected_cloud_out){
		return(extract_index_from_pointcloudXYZC(&conected_cloud_in, &index, conected_cloud_out));}
	bool PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC(PointCloudXYZConected *conected_cloud_in, std::vector<int> *index, PointCloudXYZConected *conected_cloud_out){
		
		//-> Check if the cloud is empty
		if (conected_cloud_in->size() < 1){
			PointCloudXYZConected conected_cloud;
			*conected_cloud_out = conected_cloud;
			return (true);}
			
			
		//-> Check if the number of index is empty
		if (index->size() < 1){
			PointCloudXYZConected aux_conected_cloud_out;
			*conected_cloud_out = aux_conected_cloud_out;
			return(true);}		
		
		
		//-> Load common objects
		PCLtools PCLtools;
		
		
		//-> Organize index
		std::vector<int> organized_index;
		organized_index = *index;
		if (!PCLtools.organize_vector_ascending(organized_index, &organized_index)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC] Failed, can't organize the index vector\033[0m" << std::endl;
			return(false);}
		
		
		//-> Check if the lowest index is ok
		if (organized_index[0] < 0){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC] Failed, the lowest index is out of range\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Check if the highest index is ok
		if (organized_index[organized_index.size()-1] >= conected_cloud_in->size()){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC] Failed, the highest index is out of range\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Construct the mapping vector
		PointCloudXYZConected conected_cloud;
		std::vector <int> origen;
		std::vector <int> destiny;

		
		//-> Store the index in the new cloud and generate the mapping vector
		int last_index(-1);
		for (int i=0; i < organized_index.size(); i++){
			if (organized_index[i] != last_index){
				last_index = organized_index[i];
				conected_cloud.Points.push_back(conected_cloud_in->Points[organized_index[i]]);
				origen.push_back(organized_index[i]);
				destiny.push_back(i);}}
		
		
		//-> Readjust the mapping of the connected index
		for (int i=0; i < conected_cloud.size(); i++){
			for (int j=0; j < conected_cloud.Points[i].linear_conexion_index.size(); j++){
				bool found(false);
				for (int k=0; k < origen.size(); k++){
					if (conected_cloud.Points[i].linear_conexion_index[j] == origen[k]){
						conected_cloud.Points[i].linear_conexion_index[j] = destiny[k];
						found = true;
						k = origen.size();}
					
					if (found == false && k == origen.size()-1){
						std::vector<int> new_vector_index;
						if (!PCLtools.delete_i_vector_value(conected_cloud.Points[i].linear_conexion_index, k, &new_vector_index)){
							if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::extract_index_from_pointcloudXYZC] Failed, can't extract index\033[0m" << std::endl;
							return(false);}		
						conected_cloud.Points[i].linear_conexion_index = new_vector_index;}}}}
		
		
		//-> Store planes
		conected_cloud.plane = conected_cloud_in->plane;
		
		
		//-> Store lines
		conected_cloud.line = conected_cloud_in->line;
		
		
		//-> Store segments
		conected_cloud.segment = conected_cloud_in->segment;
		
		
		//-> Return value
		*conected_cloud_out = conected_cloud;
									
		
		return(true);}
	
	
	//**COMBINE CONNECTED POINT CLOUDS**//
	bool PointCloudXYZConectedTool::combine_connected_point_clouds(PointCloudXYZConected cloud_in1, PointCloudXYZConected cloud_in2, PointCloudXYZConected *cloud_out){
		return(combine_connected_point_clouds(&cloud_in1, &cloud_in2, cloud_out));}
	bool PointCloudXYZConectedTool::combine_connected_point_clouds(PointCloudXYZConected *cloud_in1, PointCloudXYZConected *cloud_in2, PointCloudXYZConected *cloud_out){
		std::vector<PointCloudXYZConected> clouds;
		clouds.push_back(*cloud_in1);
		clouds.push_back(*cloud_in2);
		return(combine_connected_point_clouds(&clouds, cloud_out));}
	bool PointCloudXYZConectedTool::combine_connected_point_clouds(std::vector<PointCloudXYZConected> *clouds, PointCloudXYZConected *cloud_out){
			return (combine_connected_point_clouds(*clouds, cloud_out));}
	bool PointCloudXYZConectedTool::combine_connected_point_clouds(std::vector<PointCloudXYZConected> clouds, PointCloudXYZConected *cloud_out){
		
		//-> Check the number of cloud to address
		if (clouds.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::combine_connected_point_clouds] Failed, there are not connected clouds to combine\033[0m" << std::endl;
			return(false);}
		
		
		//-> If there is just one connected cloud, return it
		if (clouds.size() == 1){
		*cloud_out =  clouds[0];
		return(true);}
		
		
		//-> Get the connexions status
		bool plane_status(true);
		bool line_status(true); 
		bool segment_status(true);
		for (int i=0; i < clouds.size(); i++){
			if (!clouds[i].CheckPointPlaneIndexStatus())
				plane_status = false;
			if (!clouds[i].CheckPointLineIndexStatus())
				line_status = false;
			if (!clouds[i].CheckPointSegmentIndexStatus())
				segment_status = false;
			if (!clouds[i].CheckPointConexionsStatus()){
				if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::combine_connected_point_clouds] Failed, the connected point index are not OK\033[0m" << std::endl;
				return(false);}}

		
		//-> Declare cloud to return
		PointCloudXYZConected combined_cloud;
		
		
		//-> Generate the combined cloud
		int connected_point_readjust(0);
		int plane_readjust(0);
		int line_readjust(0);
		int segment_readjust(0);
		for (int i=0; i < clouds.size(); i++){		
			
			//-> Add planes
			if (plane_status)
			for (int j=0; j < clouds[i].plane.size(); j++){
				combined_cloud.plane.push_back(clouds[i].plane[j]);}
				
				
			//-> Add lines
			if (line_status)
			for (int j=0; j < clouds[i].line.size(); j++){
				combined_cloud.line.push_back(clouds[i].line[j]);}
			
			
			//-> Add segment
			if (segment_status)	
			for (int j=0; j < clouds[i].segment.size(); j++){
				combined_cloud.segment.push_back(clouds[i].segment[j]);}	
			
			
			//-> Add points
			for (int j=0; j < clouds[i].Points.size(); j++){
				combined_cloud.Points.push_back(clouds[i].Points[j]);
				
				//-> Readjust connected index
				for (int k=0; k < combined_cloud.Points[combined_cloud.Points.size()-1].linear_conexion_index.size(); k++){
					combined_cloud.Points[combined_cloud.Points.size()-1].linear_conexion_index[k] = combined_cloud.Points[combined_cloud.Points.size()-1].linear_conexion_index[k] + connected_point_readjust;}
				connected_point_readjust = combined_cloud.Points.size();
				
				
				//-> Readjust plane index
				for (int k=0; k < combined_cloud.Points[combined_cloud.Points.size()-1].plane_index.size(); k++){
					combined_cloud.Points[combined_cloud.Points.size()-1].plane_index[k] = combined_cloud.Points[combined_cloud.Points.size()-1].plane_index[k] + plane_readjust;}
				if (plane_status) plane_readjust = combined_cloud.plane.size();
				
				
				//-> Readjust line index
				for (int k=0; k < combined_cloud.Points[combined_cloud.Points.size()-1].line_index.size(); k++){
					combined_cloud.Points[combined_cloud.Points.size()-1].line_index[k] = combined_cloud.Points[combined_cloud.Points.size()-1].line_index[k] + line_readjust;}
				if (line_status) line_readjust = combined_cloud.line.size();
				
				
				
				//-> Readjust line index
				for (int k=0; k < combined_cloud.Points[combined_cloud.Points.size()-1].segment_index.size(); k++){
					combined_cloud.Points[combined_cloud.Points.size()-1].segment_index[k] = combined_cloud.Points[combined_cloud.Points.size()-1].segment_index[k] + segment_readjust;}
				if (segment_readjust) segment_readjust = combined_cloud.line.size();}}
				
				
		//-> Delete duplicated planes
		std::vector <Plane_coef> planes_out;
		std::vector<int> plane_mapping;
		if (!delete_duplicated_planes(combined_cloud.plane, &plane_mapping, &planes_out)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::combine_connected_point_clouds] Failed, can't delete duplicated planes\033[0m" << std::endl;
			return(false);}
		combined_cloud.plane = planes_out;
		
		
		//-> Delete duplicated lines
		std::vector <line_coef> line_out;
		std::vector<int> line_mapping;
		if (!delete_duplicated_lines(combined_cloud.line, &line_mapping, &line_out)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::combine_connected_point_clouds] Failed, can't delete duplicated lines\033[0m" << std::endl;
			return(false);}
		combined_cloud.line = line_out;
		
		
		//-> Delete duplicated segments
		std::vector <segment_description> segments_out;
		std::vector<int> segments_mapping;
		if (!delete_duplicated_segments(combined_cloud.segment, &segments_mapping, &segments_out)){
			if (sh_log) std::cout << "\033[1;31m[PointCloudXYZConectedTool::combine_connected_point_clouds] Failed, can't delete duplicated segments\033[0m" << std::endl;
			return(false);}
		combined_cloud.segment = segments_out;
		
	
		return (false);}
	
	
	//**DELETE DUPLICATED PLANES**//
	bool PointCloudXYZConectedTool::delete_duplicated_planes(std::vector <Plane_coef> *planes_in, std::vector<int> *mapping, std::vector <Plane_coef> *planes_out){
		return(delete_duplicated_planes(planes_in, mapping, planes_out));}
	bool PointCloudXYZConectedTool::delete_duplicated_planes(std::vector <Plane_coef> planes_in, std::vector<int> *mapping, std::vector <Plane_coef> *planes_out){
		
		
		std::vector <Plane_coef> planes;
		std::vector <int> mapping_vector;
		
		
		for (int i=0; i < planes_in.size(); i++){
			bool found (false);
			int mapping(i);
			for (int j=0; j < planes.size(); j++){
				if (compare_planes(planes_in[i], planes[j])){
					mapping = j;
					found = true;}}
			
			mapping_vector.push_back(mapping);
			if (!found) planes.push_back(planes_in[i]);}
			
		*mapping = 	mapping_vector;
		*planes_out = planes;
		// Not tested
		return(false);}
		
	
	//**DELETE DUPLICATED LINES**//
	bool PointCloudXYZConectedTool::delete_duplicated_lines(std::vector <line_coef> *lines_in, std::vector<int> *mapping, std::vector <line_coef> *lines_out){
		return(delete_duplicated_lines(lines_in, mapping, lines_out));}
	bool PointCloudXYZConectedTool::delete_duplicated_lines(std::vector <line_coef> lines_in, std::vector<int> *mapping, std::vector <line_coef> *lines_out){
		std::vector <line_coef> lines;
		std::vector <int> mapping_vector;
		
		
		for (int i=0; i < lines_in.size(); i++){
			bool found (false);
			int mapping(i);
			for (int j=0; j < lines.size(); j++){
				if (compare_lines(lines_in[i], lines[j])){
					mapping = j;
					found = true;}}
			
			mapping_vector.push_back(mapping);
			if (!found) lines.push_back(lines_in[i]);}
		
		*mapping = 	mapping_vector;
		*lines_out = lines;

		// Not tested
		return(false);}
	
	
	//**DELETE DUPLICATED SEGMENTS**//
	bool PointCloudXYZConectedTool::delete_duplicated_segments(std::vector <segment_description> *segmnets_in, std::vector<int> *mapping, std::vector <segment_description> *segmnets_out){
		return(delete_duplicated_segments(segmnets_in, mapping, segmnets_out));}
	bool PointCloudXYZConectedTool::delete_duplicated_segments(std::vector <segment_description> segmnets_in, std::vector<int> *mapping, std::vector <segment_description> *segmnets_out){
		std::vector <segment_description> segmnets;
		std::vector <int> mapping_vector;
		
		
		for (int i=0; i < segmnets_in.size(); i++){
			bool found (false);
			int mapping(i);
			for (int j=0; j < segmnets.size(); j++){
				if (compare_segments(segmnets_in[i], segmnets[j])){
					mapping = j;
					found = true;}}
			
			mapping_vector.push_back(mapping);
			if (!found) segmnets.push_back(segmnets_in[i]);}
		
		
		*mapping = 	mapping_vector;
		*segmnets_out = segmnets;

		// Not tested
		return(false);}
	
	
	//**COMPARE PLANES**//
	bool PointCloudXYZConectedTool::compare_planes(Plane_coef plane1, Plane_coef plane2){
		
		bool similar(true);
		
		if (plane1.a != plane2.a)
			similar = false;
		if (plane1.b != plane2.b)
			similar = false;
		if (plane1.c != plane2.c)
			similar = false;
		if (plane1.d != plane2.d)
			similar = false;
		if (plane1.type != plane2.type)
			similar = false;
		if (plane1.SE_relation != plane2.SE_relation)
			similar = false;
		if (plane1.valid != plane2.valid)
			similar = false;		
		if (plane1.Zangle != plane2.Zangle)
			similar = false;
		
		return(similar);}
	
	
	//**COMPARE LINES**//
	bool PointCloudXYZConectedTool::compare_lines(line_coef line1, line_coef line2){
		
		bool similar(true);
		
		if (line1.x != line2.x)
			similar = false;
		if (line1.y != line2.y)
			similar = false;
		if (line1.z != line2.z)
			similar = false;
		if (line1.vx != line2.vx)
			similar = false;
		if (line1.vy != line2.vy)
			similar = false;
		if (line1.vz != line2.vz)
			similar = false;
		
		PCLtools PCL_tools;
		if (!PCL_tools.compare_array(line1.plane_index, line2.plane_index))
			similar = false;
		
		return(similar);}
	
	
	//**COMPARE PLANES**//
	bool PointCloudXYZConectedTool::compare_segments(segment_description segment1, segment_description segment2){
		bool similar(true);
		
		if (segment1.density != segment2.density)
			similar = false;
		if (segment1.start_point.x != segment2.start_point.x)
			similar = false;		
		if (segment1.start_point.y != segment2.start_point.y)
			similar = false;		
		if (segment1.start_point.z != segment2.start_point.z)
			similar = false;
		if (segment1.end_point.x != segment2.end_point.x)
			similar = false;		
		if (segment1.end_point.y != segment2.end_point.y)
			similar = false;		
		if (segment1.end_point.z != segment2.end_point.z)
			similar = false;

		
		PCLtools PCL_tools;
		if (!PCL_tools.compare_array(segment1.plane_index, segment2.plane_index))
			similar = false;
		
		return(similar);}
		

	//**DISPLAY CONNECTED CLOUD INFO**//
	bool PointCloudXYZConectedTool::display_points_info(PointCloudXYZConected cloud, bool color){
		if (color) std::cout << "\033[0m";
		std::cout << "\nNumber of connected points (" << cloud.size() << "):" << std::endl << std::endl;			
		for (int i=0; i<cloud.size(); i++){
			if (color) std::cout << "\033[0m";
			std::cout << "\nPoint " << i << ":\t" << cloud.Points[i].p;
			
			//-> Check conexion status
			if (color){
				if (cloud.CheckPointConexionsStatus()) std::cout << "\033[0m";
				else std::cout << "\033[0;33m";}
			std::cout << "\n\t\tConected to (" << cloud.Points[i].linear_conexion_index.size() << "): ";
			for (int j=0; j < cloud.Points[i].linear_conexion_index.size(); j++){
				if (j != 0) std::cout << ", ";
				std::cout << cloud.Points[i].linear_conexion_index[j];}
			
			//-> Check plane status
			if (color){
				if (cloud.CheckPointPlaneIndexStatus()) std::cout << "\033[0m";
				else std::cout << "\033[0;33m";}
			std::cout << "\n\t\tBelongs to planes(" << cloud.Points[i].plane_index.size() << "): ";
			for (int j=0; j < cloud.Points[i].plane_index.size(); j++){
				if (j != 0) std::cout << ", ";
				std::cout << cloud.Points[i].plane_index[j];}
			

			//-> Check line status
			if (color){
				if (cloud.CheckPointLineIndexStatus()) std::cout << "\033[0m";
				else std::cout << "\033[0;33m";	}	
			std::cout << "\n\t\tBelongs to lines(" << cloud.Points[i].line_index.size() << "): ";
			for (int j=0; j < cloud.Points[i].line_index.size(); j++){
				if (j != 0) std::cout << ", ";
				std::cout << cloud.Points[i].line_index[j];}
			
			
			//-> Check segment status
			if (color){
				if (cloud.CheckPointSegmentIndexStatus()) std::cout << "\033[0m";
				else std::cout << "\033[0;33m";}
			
			std::cout << "\n\t\tBelongs to segments(" << cloud.Points[i].segment_index.size() << "): ";
			for (int j=0; j < cloud.Points[i].segment_index.size(); j++){
				if (j != 0) std::cout << ", ";
				std::cout << cloud.Points[i].segment_index[j];}
			std::cout << std::endl;}

			
		//-> Restart font color
		std::cout << "\033[0m" << std::endl;
		
		return(true);}
	bool PointCloudXYZConectedTool::display_plane_info(PointCloudXYZConected cloud,  bool color){
		//-> Check plane status
		if (color) std::cout << "\033[0m";
		
		
		std::cout << "\nNumber of planes (" << cloud.plane.size() << ")" << std::endl << std::endl;
		for (int i=0; i < cloud.plane.size(); i++)
			std::cout << "\nPlane " << i << ":\ta: " << cloud.plane[i].a 
									   << "\n\t\tb: "  << cloud.plane[i].b 
									   << "\n\t\tc: " << cloud.plane[i].c 
									   << "\n\t\td: " << cloud.plane[i].d  
									   << "\n\t\ttype: " << cloud.plane[i].type 
									   << "\n\t\tS/E: " << cloud.plane[i].SE_relation 
									   << "\n\t\tvalid: " << cloud.plane[i].valid  
									   << "\n\t\tZ angle: " << cloud.plane[i].Zangle
									   << std::endl;
		
		//-> Restart font color
		std::cout << "\033[0m"<< std::endl;
		
		return(true);}
	bool PointCloudXYZConectedTool::display_line_info(PointCloudXYZConected cloud,  bool color){		
			
		if (color) std::cout << "\033[0m";
		std::cout << "\nNumber of lines (" << cloud.line.size() << ")" << std::endl << std::endl;
		for (int i=0; i < cloud.line.size(); i++){
			if (color) std::cout << "\033[0m";
			std::cout << "Line " << i <<  ":\t\tx: " << cloud.line[i].x 
									  << "\n\t\ty:  "  << cloud.line[i].y 
									  << "\n\t\tz: "   << cloud.line[i].z 
									  << "\n\t\tvx: "  << cloud.line[i].vx 
									  << "\n\t\tvy: "  << cloud.line[i].vy 
									  << "\n\t\tvz: "  << cloud.line[i].vz;
			
			if (color){
				if (cloud.CheckLinePlaneIndexStatus()) std::cout << "\033[0m";
				else std::cout << "\033[0;33m";}	
			std::cout << "\n\t\tBelong to plane(" << cloud.line[i].plane_index.size() << "): ";
			for (int j=0; j < cloud.line[i].plane_index.size() ; j++){
				if (j != 0) std::cout << ", ";
				std::cout << cloud.line[i].plane_index[j];}
			std::cout << std::endl;
			std::cout << std::endl;}
			
		

		//-> Restart font color
		std::cout << "\033[0m"<< std::endl;
		
		return(true);}
	bool PointCloudXYZConectedTool::display_segment_info(PointCloudXYZConected cloud,  bool color){
		
		if (color) std::cout << "\033[0m";
		std::cout << "\nNumber of segments (" << cloud.segment.size() << ")" << std::endl << std::endl;
		for (int i=0; i < cloud.segment.size(); i++){
			if (color) std::cout << "\033[0m";
			std::cout << "Segment " << i << ":\tStart: " << cloud.segment[i].start_point 
										 << "\n\t\tEnd: "      << cloud.segment[i].end_point 
										 << "\n\t\tDensity : " << cloud.segment[i].density;
			
			if (color){
				if (cloud.CheckSegmentPlaneIndexStatus()) std::cout << "\033[0m";
				else std::cout << "\033[0;33m";}	
			std::cout << "\n\t\tPlane index(" << cloud.segment[i].plane_index.size() << "): ";
			for (int j=0; j < cloud.segment[i].plane_index.size() ; j++){
				if (j != 0) std::cout << ", ";
				std::cout << cloud.segment[i].plane_index[j];}
			
			if (color){
				if (cloud.CheckSegmentLineIndexStatus()) "\033[0m";
				else std::cout << "\033[0;33m";}	
			std::cout << "\n\t\tLine index(" << cloud.segment[i].line_index.size() << "): ";
			for (int j=0; j < cloud.segment[i].line_index.size() ; j++){
				if (j != 0) std::cout << ", ";
				std::cout << cloud.segment[i].line_index[j];}
			std::cout << std::endl;
			std::cout << std::endl;
			
			}

		//-> Restart font color
		std::cout << "\033[0m"<< std::endl;
		
		return(true);}
		
#endif