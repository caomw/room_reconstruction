#ifndef PCL_TOOLS_HPP
#define PCL_TOOLS_HPP

	//**CONSTRUCTOR (PRINCIPAL MENU)**//
	PCLtools::PCLtools(){
		sh_log = true;
		sh_Wlog = true;
	
		return;}

		
	//**DESTRUCTOR**//
	PCLtools::~PCLtools(){}
	
	
	//**DELETE VALUE FROM I VECTOR POSITION ((INT VECTOR))**//
	bool PCLtools::delete_i_vector_value(std::vector<int> vector_in, int position, std::vector<int> *vector_out){
		std::vector<float> aux_vector_in;
		if (!int_2_float(vector_in, &aux_vector_in)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::delete_i_vector_value] Failed, can't convert int vector to float\033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<float> aux_vector_out;
		if (!delete_i_vector_value(aux_vector_in, position, &aux_vector_out)){
			return(false);}
		
		
		std::vector<int> aux_vector_out2;
		if (!float_2_int(aux_vector_out, &aux_vector_out2)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::delete_i_vector_value] Failed, can't convert float vector to int\033[0m" << std::endl;
			return(false);}	
		
		
		return(true);}	
	bool PCLtools::delete_i_vector_value(std::vector<float> vector_in, int position, std::vector<float> *vector_out){
		std::vector<float> vector;
		for (int i=0; i < vector_in.size(); i++)
			if (i != position)
				vector.push_back(vector_in[i]);
		
		*vector_out = vector;
		
		return (true);}
	
	
	//**COMPARE ARRAY**//
	bool PCLtools::compare_array(std::vector<int> vector_A, std::vector<int> vector_B){
		for (int i=0; i < vector_A.size(); i++){
			bool found(false);
			
			
			for (int j=0; j < vector_B.size(); j++){
				if (vector_A[i] == vector_B[j])
					found = true;}
			
			if (!found)
				return(false);}
		return(true);}
	
	
	//**CONVERT ARRAY**//
	bool PCLtools::int_2_bool(std::vector<int> vector_in, std::vector<bool> *vector_out){
		std::vector<bool> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((bool)vector_in[i]);
		
		*vector_out = vector;
		return(true);}
	bool PCLtools::int_2_double(std::vector<int> vector_in, std::vector<double> *vector_out){
		std::vector<double> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((double)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::int_2_float(std::vector<int> vector_in, std::vector<float> *vector_out){
		std::vector<float> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((float)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::double_2_int(std::vector<double> vector_in, std::vector<int> *vector_out){
		std::vector<int> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((int)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::double_2_float(std::vector<double> vector_in, std::vector<float> *vector_out){
		std::vector<float> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((float)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::double_2_bool(std::vector<double> vector_in, std::vector<bool> *vector_out){
		std::vector<bool> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((bool)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::float_2_int(std::vector<float> vector_in, std::vector<int> *vector_out){
		std::vector<int> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((int)vector_in[i]);
		
		*vector_out = vector;
		return(true);}
	bool PCLtools::float_2_double(std::vector<float> vector_in, std::vector<double> *vector_out){
		std::vector<double> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((double)vector_in[i]);
		
		*vector_out = vector;
		return(true);}
	bool PCLtools::float_2_bool(std::vector<float> vector_in, std::vector<bool> *vector_out){
		std::vector<bool> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((bool)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::bool_2_int(std::vector<bool> vector_in, std::vector<int> *vector_out){
		std::vector<int> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((int)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::bool_2_float(std::vector<bool> vector_in, std::vector<float> *vector_out){
		std::vector<float> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((float)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	
	bool PCLtools::bool_2_double(std::vector<bool> vector_in, std::vector<double> *vector_out){
		std::vector<double> vector;
		for (int i=0; i < vector_in.size(); i++)
			vector.push_back((double)vector_in[i]);
		
		*vector_out = vector;
		return(true);}	

	
	
	//**CONVERT POINTINDICES TO VECTOR INT**//
	bool PCLtools::convert_pointindices_2_int_vector(pcl::PointIndices::Ptr index_in, std::vector<int> *index_out){
		
		std::vector <int> index;
		for (int i=0; i < index_in->indices.size(); i++)
			index.push_back(index_in->indices[i]);
		
		//-> Return value
		*index_out = index;
		
		return(true);}
	
	
	//**DELETE DUPLICATED VALUES**//
	bool PCLtools::delete_duplicated_values(std::vector<int> vector_in, std::vector<int> *vector_out){
		std::vector<float> aux_vector_in;
		if (!int_2_float(vector_in, &aux_vector_in)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::delete_duplicated_values] Failed, can't convert int vector to float\033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<float> aux_vector_out;
		if (!delete_duplicated_values(aux_vector_in, &aux_vector_out)){
			return(false);}
	
		
		std::vector<int> aux_vector_out2;
		if (!float_2_int(aux_vector_out, &aux_vector_out2)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::delete_duplicated_values] Failed, can't convert float vector to int\033[0m" << std::endl;
			return(false);}	
		
		
		*vector_out = aux_vector_out2;
		
		return(true);}
	bool PCLtools::delete_duplicated_values(std::vector<float> vector_in, std::vector<float> *vector_out){
		std::vector <float> aux_vector(vector_in);
		for (int i=0; i< aux_vector.size(); i++){
			for (int j=i+1; j< aux_vector.size(); j++)
				if (aux_vector[i] == aux_vector[j])
					if (!delete_i_vector_value(aux_vector, j, &aux_vector)){
						if (sh_log) std::cout << "\033[1;31m[PCLtools::delete_duplicated_values] Failed, can't eliminate the duplicated index\033[0m" << std::endl;
						return(false);}}
				
		
		*vector_out =  aux_vector;
		return(true);}
	
	
	
	//**ORGANIZE VECTOR IN DESCENDING MODE**//
	bool PCLtools::organize_vector_descending(std::vector<int> vector_in, std::vector<int> *vector_out){
		return(organize_vector_descending(vector_in, vector_in, vector_out));}	
	bool PCLtools::organize_vector_descending(std::vector<float> vector_in, std::vector<float> *vector_out){
		return(organize_vector_descending(vector_in, vector_in, vector_out));}			
	bool PCLtools::organize_vector_descending(std::vector<double> vector_in, std::vector<double> *vector_out){
		return(organize_vector_descending(vector_in, vector_in, vector_out));}
	bool PCLtools::organize_vector_descending(std::vector<int> vector_in, std::vector<int> reference_in, std::vector<int> *vector_out){
		std::vector<double> vector_in_double;
		if (!int_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<int> vector_out_int;
		if (!double_2_int(vector_out_double, &vector_out_int)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to int array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_int;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<int> vector_in, std::vector<double> reference_in, std::vector<int> *vector_out){
		std::vector<double> vector_in_double;
		if (!int_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_in, &vector_out_double)){
			return(false);}
		
		
		std::vector<int> vector_out_int;
		if (!double_2_int(vector_out_double, &vector_out_int)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to int array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_int;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<int> vector_in, std::vector<float> reference_in, std::vector<int> *vector_out){
		std::vector<double> vector_in_double;
		if (!int_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<int> vector_out_int;
		if (!double_2_int(vector_out_double, &vector_out_int)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to int array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_int;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<float> vector_in, std::vector<double> reference_in, std::vector<float> *vector_out){
		std::vector<double> vector_in_double;
		if (!float_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_in, &vector_out_double)){
			return(false);}
		
		
		std::vector<float> vector_out_float;
		if (!double_2_float(vector_out_double, &vector_out_float)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to float array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_float;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<float> vector_in, std::vector<float> reference_in, std::vector<float> *vector_out){
		std::vector<double> vector_in_double;
		if (!float_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<float> vector_out_float;
		if (!double_2_float(vector_out_double, &vector_out_float)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to float array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_float;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<float> vector_in, std::vector<int> reference_in, std::vector<float> *vector_out){
		std::vector<double> vector_in_double;
		if (!float_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<float> vector_out_float;
		if (!double_2_float(vector_out_double, &vector_out_float)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to float array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_float;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<bool> vector_in, std::vector<float> reference_in, std::vector<bool> *vector_out){
		std::vector<double> vector_in_double;
		if (!bool_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the bool array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the float array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<bool> vector_out_bool;
		if (!double_2_bool(vector_out_double, &vector_out_bool)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to bool array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_bool;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<bool> vector_in, std::vector<double> reference_in, std::vector<bool> *vector_out){
		std::vector<double> vector_in_double;
		if (!bool_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the bool array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}		
		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_in, &vector_out_double)){
			return(false);}
		
		
		std::vector<bool> vector_out_bool;
		if (!double_2_bool(vector_out_double, &vector_out_bool)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to bool array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_bool;
		
		return(true);}
	bool PCLtools::organize_vector_descending(std::vector<bool> vector_in, std::vector<int> reference_in, std::vector<bool> *vector_out){
		std::vector<double> vector_in_double;
		if (!bool_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the bool array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the int array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_descending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<bool> vector_out_bool;
		if (!double_2_bool(vector_out_double, &vector_out_bool)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the double array to bool array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_bool;
		
		return(true);}	
	bool PCLtools::organize_vector_descending(std::vector<double> vector_in, std::vector<int> reference_in, std::vector<double> *vector_out){
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		if (!organize_vector_descending(vector_in, reference_double, vector_out)){
			return(false);}
			
		
		return(true);}	
	bool PCLtools::organize_vector_descending(std::vector<double> vector_in, std::vector<float> reference_in, std::vector<double> *vector_out){
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		if (!organize_vector_descending(vector_in, reference_double, vector_out)){
			return(false);}
			

		
		return(true);}	
	bool PCLtools::organize_vector_descending(std::vector<double> vector_in, std::vector<double> reference_in, std::vector<double> *vector_out){
		//-> Check the the size of the vectors are the same
		if (vector_in.size() != reference_in.size()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] Failed, The reference and the in vector do not have the same size\033[0m" << std::endl;
			return(false);}		
		
		
		//-> Check if the vector is empty
		if (reference_in.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_descending] The vector is empty\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Organize vector
		std::vector<double> reference (reference_in);
		std::vector<double> vector_aux = (vector_in);
		
		for (int i=0; i < reference.size(); i++){
			for (int j=i+1; j < reference.size(); j++){
				if (reference[i] < reference[j]){
					//-> Move the reference order
					double aux;
					aux = reference[i];
					reference[i] = reference[j];
					reference[j] = aux;
					
					
					//-> Move the vector order
					double aux2;
					aux2 = vector_aux[i];
					vector_aux[i] = vector_aux[j];
					vector_aux[j] = aux2;}}}
		
		
		//-> Return value
		*vector_out = vector_aux;
		

		return(true);}


	//**ORGANIZE VECTOR IN ASCENDING MODE**//
	bool PCLtools::organize_vector_ascending(std::vector<int> vector_in, std::vector<int> *vector_out){
		return(organize_vector_ascending(vector_in, vector_in, vector_out));}	
	bool PCLtools::organize_vector_ascending(std::vector<float> vector_in, std::vector<float> *vector_out){
		return(organize_vector_ascending(vector_in, vector_in, vector_out));}			
	bool PCLtools::organize_vector_ascending(std::vector<double> vector_in, std::vector<double> *vector_out){
		return(organize_vector_ascending(vector_in, vector_in, vector_out));}
	bool PCLtools::organize_vector_ascending(std::vector<int> vector_in, std::vector<int> reference_in, std::vector<int> *vector_out){
		std::vector<double> vector_in_double;
		if (!int_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<int> vector_out_int;
		if (!double_2_int(vector_out_double, &vector_out_int)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to int array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_int;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<int> vector_in, std::vector<double> reference_in, std::vector<int> *vector_out){
		std::vector<double> vector_in_double;
		if (!int_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_in, &vector_out_double)){
			return(false);}
		
		
		std::vector<int> vector_out_int;
		if (!double_2_int(vector_out_double, &vector_out_int)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to int array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_int;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<int> vector_in, std::vector<float> reference_in, std::vector<int> *vector_out){
		std::vector<double> vector_in_double;
		if (!int_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<int> vector_out_int;
		if (!double_2_int(vector_out_double, &vector_out_int)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to int array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_int;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<float> vector_in, std::vector<double> reference_in, std::vector<float> *vector_out){
		std::vector<double> vector_in_double;
		if (!float_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_in, &vector_out_double)){
			return(false);}
		
		
		std::vector<float> vector_out_float;
		if (!double_2_float(vector_out_double, &vector_out_float)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to float array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_float;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<float> vector_in, std::vector<float> reference_in, std::vector<float> *vector_out){
		std::vector<double> vector_in_double;
		if (!float_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<float> vector_out_float;
		if (!double_2_float(vector_out_double, &vector_out_float)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to float array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_float;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<float> vector_in, std::vector<int> reference_in, std::vector<float> *vector_out){
		std::vector<double> vector_in_double;
		if (!float_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<float> vector_out_float;
		if (!double_2_float(vector_out_double, &vector_out_float)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to float array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_float;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<bool> vector_in, std::vector<float> reference_in, std::vector<bool> *vector_out){
		std::vector<double> vector_in_double;
		if (!bool_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the bool array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the float array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<bool> vector_out_bool;
		if (!double_2_bool(vector_out_double, &vector_out_bool)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to bool array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_bool;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<bool> vector_in, std::vector<double> reference_in, std::vector<bool> *vector_out){
		std::vector<double> vector_in_double;
		if (!bool_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the bool array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}		
		
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_in, &vector_out_double)){
			return(false);}
		
		
		std::vector<bool> vector_out_bool;
		if (!double_2_bool(vector_out_double, &vector_out_bool)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to bool array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_bool;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<bool> vector_in, std::vector<int> reference_in, std::vector<bool> *vector_out){
		std::vector<double> vector_in_double;
		if (!bool_2_double(vector_in, &vector_in_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the bool array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}		
		
		
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the int array to double array " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}	
		
		
		std::vector<double> vector_out_double;
		if (!organize_vector_ascending(vector_in_double, reference_double, &vector_out_double)){
			return(false);}
		
		
		std::vector<bool> vector_out_bool;
		if (!double_2_bool(vector_out_double, &vector_out_bool)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the double array to bool array \033[0m" << std::endl;
			return(false);}		
		
		
		*vector_out = vector_out_bool;
		
		return(true);}
	bool PCLtools::organize_vector_ascending(std::vector<double> vector_in, std::vector<int> reference_in, std::vector<double> *vector_out){
		std::vector<double> reference_double;
		if (!int_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the int array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		if (!organize_vector_ascending(vector_in, reference_double, vector_out)){
			return(false);}
			
		
		return(true);}	
	bool PCLtools::organize_vector_ascending(std::vector<double> vector_in, std::vector<float> reference_in, std::vector<double> *vector_out){
		std::vector<double> reference_double;
		if (!float_2_double(reference_in, &reference_double)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, can't convert the float array to double array \033[0m" << std::endl;
			return(false);}		
		
		
		if (!organize_vector_ascending(vector_in, reference_double, vector_out)){
			return(false);}
			

		
		return(true);}	
	bool PCLtools::organize_vector_ascending(std::vector<double> vector_in, std::vector<double> reference_in, std::vector<double> *vector_out){
		//-> Check the the size of the vectors are the same
		if (vector_in.size() != reference_in.size()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] Failed, The reference and the in vector do not have the same size\033[0m" << std::endl;
			return(false);}		
		
		
		//-> Check if the vector is empty
		if (reference_in.size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::organize_vector_ascending] The vector is empty\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Organize vector
		std::vector<double> reference (reference_in);
		std::vector<double> vector_aux = (vector_in);
		
		for (int i=0; i < reference.size(); i++){
			for (int j=i+1; j < reference.size(); j++){
				if (reference[i] > reference[j]){
					//-> Move the reference order
					double aux;
					aux = reference[i];
					reference[i] = reference[j];
					reference[j] = aux;
					
					
					//-> Move the vector order
					double aux2;
					aux2 = vector_aux[i];
					vector_aux[i] = vector_aux[j];
					vector_aux[j] = aux2;}}}
		
		
		//-> Return value
		*vector_out = vector_aux;
		

		return(true);}
	
	
	//**ANGLE_BETWEEN_TWO_VECTORS **//
	bool PCLtools::angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, double *angle){
		pcl::PointXYZ Vector1;
		pcl::PointXYZ Vector2;
		
		Vector1.x = v1.x - reference.x;
		Vector1.y = v1.y - reference.y;
		Vector1.z = v1.z - reference.z;		
		
		Vector2.x = v2.x - reference.x;
		Vector2.y = v2.y - reference.y;
		Vector2.z = v2.z - reference.z;
		
		return(angle_between_two_vetors(Vector1, Vector2, angle));}
	bool PCLtools::angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, float *angle){
		pcl::PointXYZ Vector1;
		pcl::PointXYZ Vector2;
		
		Vector1.x = v1.x - reference.x;
		Vector1.y = v1.y - reference.y;
		Vector1.z = v1.z - reference.z;		
		
		Vector2.x = v2.x - reference.x;
		Vector2.y = v2.y - reference.y;
		Vector2.z = v2.z - reference.z;
		
		return(angle_between_two_vetors(Vector1, Vector2, angle));}
	bool PCLtools::angle_between_two_vetors(pcl::PointXYZ v1_in, pcl::PointXYZ v2_in, float *angle_out){
		double double_angle;
		if (!angle_between_two_vetors(v1_in, v2_in, &double_angle)){
			return(false);}
		*angle_out = (float) double_angle;
		return(true);}
	bool PCLtools::angle_between_two_vetors(pcl::PointXYZ v1_in, pcl::PointXYZ v2_in, double *angle_out){
		
		pcl::PointXYZ v1(v1_in); 
		pcl::PointXYZ v2(v2_in); 
		
		//-> Check if any of the vector is not null
		if (sqrt(v1.x*v1.x) < std::numeric_limits<double>::min() && sqrt(v1.y*v1.y) < std::numeric_limits<double>::min() && sqrt(v1.z*v1.z) < std::numeric_limits<double>::min()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::angle_between_two_vetors] Failed, the values of the v1 array are lower than " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}	
		if (sqrt(v2.x*v2.x) < std::numeric_limits<double>::min() && sqrt(v2.y*v2.y) < std::numeric_limits<double>::min() && sqrt(v2.z*v2.z) < std::numeric_limits<double>::min()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::angle_between_two_vetors] Failed, the values of the v2 array are lower than " << std::numeric_limits<float>::min()<< "\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get scalar product
		double escalar_AB;
		if (!scalar_product(v1, v2, &escalar_AB)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::angle_between_two_vetors] Failed, can't get scalar product\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get vector modules
		double module_A; 
		if (!vector_module(v1, &module_A)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::scalar_product] Failed, can't get vector module\033[0m" << std::endl;
			return(false);}		
		if (module_A <= std::numeric_limits<double>::min()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::angle_between_two_vetors] Failed, module A is too low\033[0m" << std::endl;
			return(false);}		
			
		
		double module_B;
		if (!vector_module(v2, &module_B)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::scalar_product] Failed, can't get vector module\033[0m" << std::endl;
			return(false);}	
		if (module_B <= std::numeric_limits<double>::min()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::angle_between_two_vetors] Failed, module B is too low\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get cos
		double cos_alfa;
		cos_alfa = module_A * module_B;
		cos_alfa = escalar_AB / cos_alfa;

		
		//-> Get angle
		double angle;
		if (cos_alfa > 1 - std::numeric_limits<double>::min() )
			angle = 0;
		else 
			angle = acos(cos_alfa);
		
		
		*angle_out = angle;
		
		
		return (true);}
	
	
	//**FULL ANGLE_BETWEEN_TWO_VECTORS **//
	bool PCLtools::full_angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, double *angle){
		pcl::PointXYZ Vector1;
		pcl::PointXYZ Vector2;
		
		Vector1.x = v1.x - reference.x;
		Vector1.y = v1.y - reference.y;
		Vector1.z = v1.z - reference.z;		
		
		Vector2.x = v2.x - reference.x;
		Vector2.y = v2.y - reference.y;
		Vector2.z = v2.z - reference.z;
		
		return(full_angle_between_two_vetors(Vector1, Vector2, angle));}
	bool PCLtools::full_angle_between_two_vetors(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ reference, float *angle){
		pcl::PointXYZ Vector1;
		pcl::PointXYZ Vector2;
		
		Vector1.x = v1.x - reference.x;
		Vector1.y = v1.y - reference.y;
		Vector1.z = v1.z - reference.z;		
		
		Vector2.x = v2.x - reference.x;
		Vector2.y = v2.y - reference.y;
		Vector2.z = v2.z - reference.z;
		
		return(full_angle_between_two_vetors(Vector1, Vector2, angle));}
	bool PCLtools::full_angle_between_two_vetors(pcl::PointXYZ v1_in, pcl::PointXYZ v2_in, float *angle_out){
		double double_angle;
		if (!full_angle_between_two_vetors(v1_in, v2_in, &double_angle)){
			return(false);}
		*angle_out = (float) double_angle;
		return(true);}
	bool PCLtools::full_angle_between_two_vetors(pcl::PointXYZ v1_in, pcl::PointXYZ v2_in, double *angle_out){
		
		pcl::PointXYZ v1(v1_in); 
		pcl::PointXYZ v2(v2_in); 
		
		
		//-> Get not full angle
		double angle;
		if (!angle_between_two_vetors(v1, v2, &angle)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::full_angle_between_two_vetors] Failed, can't get angle\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Check if the angles are in the limit (0 or 180)
		if (angle <= allowed_error || sqrt((angle - double_PI)*(angle - double_PI)) <= allowed_error){ 
			 *angle_out = angle;
			return(true);}
		
		
		//-> Get vector product
		pcl::PointXYZ vector_procuct_value;
		if (!vector_procuct(v1, v2, &vector_procuct_value)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::full_angle_between_two_vetors] Failed, can't get vector product\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get not null direction
		double not_null_VP;
		double vpvd_x(sqrt(vector_procuct_value.x * vector_procuct_value.x));
		double vpvd_y(sqrt(vector_procuct_value.y * vector_procuct_value.y));
		double vpvd_z(sqrt(vector_procuct_value.z * vector_procuct_value.z));
		if (vpvd_x > vpvd_y && vpvd_x > vpvd_z){
			not_null_VP = vector_procuct_value.x;}
		else{
			if (vpvd_y > vpvd_z){
				not_null_VP = vector_procuct_value.y;}
			else{
				not_null_VP = vector_procuct_value.z;}}
		
		
		//-> Get full angle
		double full_angle(angle);
		if (not_null_VP < 0)
			full_angle = 2*double_PI - full_angle;
		
		
		//-> Return value
		*angle_out = full_angle;

		
		return(true);}
	
	
	//**GET VECTOR PRODUCT**//
	bool PCLtools::vector_procuct(pcl::PointXYZ v1, pcl::PointXYZ v2, pcl::PointXYZ *product_out){
		
		//-> Check if any of the vector is not null
		if ((v1.x == 0 && v1.y == 0 && v1.z == 0) || (v2.x == 0 && v2.y == 0 && v2.z == 0)) {
			if (sh_log) std::cout << "\033[1;31m[PCLtools::vector_procuct] Failed, one of the vectors is (0,0,0)\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get scalar product
		float angle;
		if (!angle_between_two_vetors(v1, v2, &angle)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::angle_between_two_vetors] Failed, can't get angle between vectors\033[0m" << std::endl;
			return(false);}	
			
		
		//-> Check if the vector are equal
		pcl::PointXYZ vproduct;
		if (angle <= allowed_error || sqrt((angle - double_PI)*(angle - double_PI)) <= allowed_error){ 
			vproduct.x = 0;
			vproduct.y = 0;
			vproduct.z = 0;}
		
		
		//-> If not, get the product vector
		else {
			vproduct.x  = (v1.y * v2.z); 
			vproduct.x -= (v1.z * v2.y);
					
			vproduct.y  = (v1.z * v2.x);  
			vproduct.y -= (v1.x * v2.z);
		
			vproduct.z  = (v1.x * v2.y);     
			vproduct.z -= (v1.y * v2.x);}
		
		
		//-> Return value
		*product_out = vproduct;
		
		return(true);}
	
	
	//**GET SCALAR PRODUCT**//
	bool PCLtools::scalar_product(pcl::PointXYZ v1, pcl::PointXYZ v2, float *product_out){
		double product_out_double;
		if (!scalar_product(v1, v2, &product_out_double)){
			return(false);}
		*product_out = (float) product_out_double;	
		return(true);}
	bool PCLtools::scalar_product(pcl::PointXYZ v1, pcl::PointXYZ v2, double *product_out){
		
		double module_A; 
		if (!vector_module(v1, &module_A)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::scalar_product] Failed, can't get vector module\033[0m" << std::endl;
			return(false);}		
		
		
		double module_B;
		if (!vector_module(v2, &module_B)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::scalar_product] Failed, can't get vector module\033[0m" << std::endl;
			return(false);}	
		
		double escalar_AB;
		escalar_AB  = v1.x * v2.x;
		escalar_AB += v1.y * v2.y;
		escalar_AB += v1.z * v2.z;
		
		*product_out = escalar_AB;
		
		return(true);}
	
	
	//**GET VECTOR MODULE**//
	bool PCLtools::vector_module(pcl::PointXYZ v1, pcl::PointXYZ reference, float *module_out){
		pcl::PointXYZ Vector1;
		
		Vector1.x = v1.x - reference.x;
		Vector1.y = v1.y - reference.y;
		Vector1.z = v1.z - reference.z;		
		
		return (vector_module(Vector1, module_out));}	
	bool PCLtools::vector_module(pcl::PointXYZ v1, pcl::PointXYZ reference, double *module_out){
		pcl::PointXYZ Vector1;
		
		Vector1.x = v1.x - reference.x;
		Vector1.y = v1.y - reference.y;
		Vector1.z = v1.z - reference.z;		
		
		return (vector_module(Vector1, module_out));}
	bool PCLtools::vector_module(pcl::PointXYZ v1, float *module_out){
		double module_out_double;
		if (!vector_module(v1, &module_out_double)){
			return(false);}
		*module_out = (float)module_out_double;
		return(true);}
	bool PCLtools::vector_module(pcl::PointXYZ v1, double *module_out){
		double module_A;
		
		module_A = v1.x * v1.x;
		module_A += v1.y * v1.y;
		module_A += v1.z * v1.z;
		module_A = sqrt(module_A);
		
		*module_out = module_A;
		
		return (true);}
	
	
	//**NORMALIZE VECTOR**//
	bool PCLtools::normalize_vector(pcl::PointXYZ V, pcl::PointXYZ *Vn_out){
		
		//->Get module
		float module; 
		if (!vector_module(V, &module)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::normalize_vector] Failed, can't get vector module\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Check if errors
		if (module == 0){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::normalize_vector] Failed, the module is 0\033[0m" << std::endl;
			return(false);}	
		
		
		//Normalize
		pcl::PointXYZ Vn(V);
		Vn.x = Vn.x / module;
		Vn.y = Vn.y / module;
		Vn.z = Vn.z / module;
		
		
		//-> Return value
		*Vn_out = Vn;
		
		
		return(true);}
	
	
	//**GET CDM**//
	bool PCLtools::get_CDM(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointXYZ *cdm){
	
		//-> check if the are points
		if (cloud_in->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::get_CDM] Failed to calculate de CDM. There are no points\033[0m" << std::endl;
			return(false);}	
		
		//-> Objects
		pcl::PointXYZ cdm_aux(0,0,0);
		
		
		//->calculate the CDM
		for (int i=0; i < cloud_in->size(); i++){

			cdm_aux.x = cdm_aux.x + cloud_in->points[i].x;
			cdm_aux.y = cdm_aux.y + cloud_in->points[i].y;
			cdm_aux.z = cdm_aux.z + cloud_in->points[i].z;}
		
		cdm_aux.x = cdm_aux.x / cloud_in->size();
		cdm_aux.y = cdm_aux.y / cloud_in->size();
		cdm_aux.z = cdm_aux.z / cloud_in->size();

			
		//-> return value
		*cdm = cdm_aux;
		
		
		return (true);}
	
	
	//**GET THE TWO FARTHEST POINTS IN A CLOUD**//
	bool PCLtools::Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointXYZ *P1, pcl::PointXYZ *P2){
		int index1;
		int index2;
		if (!Get_the_two_farthest_points(cloud_in, &index1, &index2)){
			return(false);}
		*P1 = cloud_in->points[index1];
		*P2 = cloud_in->points[index2];
		return(true);}
	bool PCLtools::Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, int *index1, int *index2){
		std::vector<std::vector<int> > list_exceptions;
		return(Get_the_two_farthest_points(cloud_in, list_exceptions, index1, index2));}
	bool PCLtools::Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match_exceptions, pcl::PointXYZ *P1, pcl::PointXYZ *P2){
		int index1;
		int index2;
		if (!Get_the_two_farthest_points(cloud_in, match_exceptions, &index1, &index2)){
			return(false);}
		*P1 = cloud_in->points[index1];
		*P2 = cloud_in->points[index2];
		
		return (true);}
	bool PCLtools::Get_the_two_farthest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match_exceptions, int *index1, int *index2){
		
		//-> Check if the data is correct
		if (cloud_in->size() < 2){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_farthest_points] The cloud given has less that 2 points\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get the index of the farthest points
		int rmax(0),tmax(0);
		float module_max(-1);
		for (int r=0; r < cloud_in->size () ; r++){
			for (int t=r; t < cloud_in->size () ; t++){
				
				//-> Check combination
				bool ok(true);
				
				//-> Check if the index is the same
				if (t == r){
					ok = false;}
				
				//-> Check if the index are in the same group
				if (ok){
					for (int i=0; i < match_exceptions.size(); i++){
						bool t_found(false);
						bool r_found(false);
						for (int j=0; j < match_exceptions[i].size(); j++){
							if (match_exceptions[i][j] == t) 
								t_found = true;		
							if (match_exceptions[i][j] == r) 
								r_found = true;	}			
						if (t_found && r_found)
							ok = false;}}
						
							
				//-> If the index are ok	
				if (ok){
					float module,x,y,z;
							
					x=cloud_in->points[r].x - cloud_in->points[t].x;
					y=cloud_in->points[r].y - cloud_in->points[t].y;
					z=cloud_in->points[r].z - cloud_in->points[t].z;
					module = x*x + y*y + z*z;
							
					if ( module > module_max ) {
						module_max = module;
						tmax=t;
						rmax=r;}}}}		
		
		
		//-> Check if the data is correct
		if (tmax < 0 || rmax < 0 || tmax >= cloud_in->size() || rmax >= cloud_in->size()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_farthest_points] The solution is out of range\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Check result	
		if (module_max == -1){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_farthest_points] no solution were calculated\033[0m" << std::endl;
			return(false);}		
		
		//-> Check
		if (rmax == tmax){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_farthest_points] Failed, the returned index are de same\033[0m" << std::endl;
			return(false);}
		
		//-> Return the values
		*index1 = tmax;
		*index2 = rmax;
		
		
		
		return (true);}
	
	
	
	//**GET THE TWO CLOSEST POINTS**//
	bool PCLtools::Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointXYZ *P1, pcl::PointXYZ *P2){
		int index1;
		int index2;
		if (!Get_the_two_closest_points(cloud_in, &index1, &index2)){
			return(false);}
		*P1 = cloud_in->points[index1];
		*P2 = cloud_in->points[index2];
		return(true);}
	bool PCLtools::Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, int *index1, int *index2){
		std::vector<std::vector<int> > list_exceptions;
		return(Get_the_two_closest_points(cloud_in, list_exceptions, index1, index2));}
	bool PCLtools::Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match_exceptions, pcl::PointXYZ *P1, pcl::PointXYZ *P2){
		int index1;
		int index2;
		if (!Get_the_two_closest_points(cloud_in, match_exceptions, &index1, &index2)){
			return(false);}
		*P1 = cloud_in->points[index1];
		*P2 = cloud_in->points[index2];
		
		return (true);}
	bool PCLtools::Get_the_two_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<std::vector<int> > match_exceptions, int *index1, int *index2){
		
		//-> Check if the data is correct
		if (cloud_in->size() < 2){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_closest_points] The cloud given has less that 2 points\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get the index of the farthest points
		int rmin(0),tmin(0);
		float module_min(std::numeric_limits<float>::max());
		for (int r=0; r < cloud_in->size () ; r++){
			for (int t=r; t < cloud_in->size () ; t++){
				
				//-> Check combination
				bool ok(true);
				
				//-> Check if the index is the same
				if (t == r){
					ok = false;}
				
				//-> Check if the index are in the same group
				if (ok){
					for (int i=0; i < match_exceptions.size(); i++){
						bool t_found(false);
						bool r_found(false);
						for (int j=0; j < match_exceptions[i].size(); j++){
							if (match_exceptions[i][j] == t) 
								t_found = true;		
							if (match_exceptions[i][j] == r) 
								r_found = true;	}			
						if (t_found && r_found)
							ok = false;}}
						
							
				//-> If the index are ok	
				if (ok){
					float module,x,y,z;
							
					x=cloud_in->points[r].x - cloud_in->points[t].x;
					y=cloud_in->points[r].y - cloud_in->points[t].y;
					z=cloud_in->points[r].z - cloud_in->points[t].z;
					module = x*x + y*y + z*z;
							
					if ( module < module_min ) {
						module_min = module;
						tmin=t;
						rmin=r;}}}}		
		
		
		//-> Check if the data is correct
		if (tmin < 0 || rmin < 0 || tmin >= cloud_in->size() || rmin >= cloud_in->size()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_closest_points] The solution is out of range\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Check result	
		if (module_min == std::numeric_limits<float>::max()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_closest_points] Failed, no solution were calculated\033[0m" << std::endl;
			return(false);}		
	
	
		//-> check if the index are the same
		if (tmin == rmin){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::Get_the_two_closest_points] Failed, the returned index are de same\033[0m" << std::endl;
			return(false);}
		
		//-> Return the values
		*index1 = tmin;
		*index2 = rmin;
		
		return (true);}
	
	
	
	//**MAKE A POINTS MESH INSIDE A POLYGON**//
	bool PCLtools::make_point_mesh_inside_polygon(pcl::PolygonMesh *polymesh_in, float density, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){
		
		
		//-> check if the dentity is correct
		if (density <= 0 ){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed,the density is not correct\033[0m" << std::endl;
			return(false);}
		
		
		//-> Temp store of the polygon mesh
		pcl::PolygonMesh polymesh;
		polymesh = *polymesh_in;
		
		
		//-> Convert the cloud2 to standard cloud
		pcl::PointCloud<pcl::PointXYZ> cloud;
		pcl::PointCloud<pcl::PointXYZ> cloud_with_cdms;
		pcl::PointCloud<pcl::PointXYZ>::Ptr point_mesh (new pcl::PointCloud<pcl::PointXYZ>);
		pcl::fromPCLPointCloud2(polymesh.cloud,cloud);
		
		
		//-> mesh with point each triangle
		for (int i=0; i<polymesh.polygons.size(); i++){
			
		
			//-> Put the polygon points in another cloud
			pcl::PointCloud<pcl::PointXYZ>::Ptr polygon_points (new pcl::PointCloud<pcl::PointXYZ>);
			for (int j=0; j < polymesh.polygons[i].vertices.size(); j++)
				polygon_points->push_back(cloud.points[polymesh.polygons[i].vertices[j]]);
				
			
			
			//-> Get the CDM
			pcl::PointXYZ cdm_point;
			if (!get_CDM(polygon_points, &cdm_point)){
				if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting the CMD\033[0m" << std::endl;
				return(false);}

			
			
			//-> Store the cdm in order to use it later
			cloud_with_cdms.push_back(cdm_point);
			
			
			//-> check if the are more than three points in the polygon 
			if (polygon_points->size() < 3){
				if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed, the number of points in the polygon " << i << " is lower than 3 \033[0m" << std::endl;
				return(false);}
			
			
		
			//-> Get the plane coefficient of the points and the normal of the plane
			pcl::PointXYZ point_1(polygon_points->points[0]);
			pcl::PointXYZ point_2(polygon_points->points[1]);
			pcl::PointXYZ point_3(polygon_points->points[2]);
			std::vector <float> plane_base_coef;
			if (!get_plane_coefficients(point_1, point_2, point_3, &plane_base_coef)){
				if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting the main plane coefficients for the polygon " << i <<  "\033[0m" << std::endl;
				return(false);}
			
			
			
			if (plane_base_coef.size() != 4){
				if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed, there are " << plane_base_coef.size() <<  " coefficients for the plane " << i <<  "\033[0m" << std::endl;
				return(false);}
			pcl::PointXYZ Gen_P_normal;
			Gen_P_normal.x = plane_base_coef[0];
			Gen_P_normal.y = plane_base_coef[1]; 
			Gen_P_normal.z = plane_base_coef[2];
					
			
			//-> Make mesh-points triangles for each pair of consecutive vertices
			for (int j=0; j < polymesh.polygons[i].vertices.size(); j++){
				
				//-> get the index points and the coordinates of them
				int index_1(polymesh.polygons[i].vertices[j]);
					
				//-> This condition is just for joint the first and the last point
				int index_2;
				if (j+1 > polymesh.polygons[i].vertices.size() - 1) index_2 = polymesh.polygons[i].vertices[0];
				else index_2 = polymesh.polygons[i].vertices[j+1];
				
				pcl::PointXYZ point_1(cloud.points[index_1]);
				pcl::PointXYZ point_2(cloud.points[index_2]);			
				
				
				
				//-> Get the plane coefficient that contain the two points (index_1 and index_2)
				std::vector <float> coeff_plane_A;
				pcl::PointXYZ P_normal_1;
				pcl::PointXYZ P_normal_2; 
				P_normal_2.x = point_1.x - point_2.x;
				P_normal_2.y = point_1.y - point_2.y;
				P_normal_2.z = point_1.z - point_2.z;
				if (!vector_procuct(Gen_P_normal, P_normal_2, &P_normal_1)){
					if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting normal of the plane\033[0m" << std::endl;
					return(false);}
				if (!get_plane_coefficients(point_1, P_normal_1, &coeff_plane_A)){
					if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting the plane A with the plane normal and one point\033[0m" << std::endl;
					return(false);}
				
				
				//-> Get the plane coefficients that contain the CDM and is perpendicular to the plane A
				std::vector <float> coeff_plane_B;
				if (!get_plane_coefficients(cdm_point, P_normal_2, &coeff_plane_B)){
					if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting the plane B with the plane normal and one point\033[0m" << std::endl;
					return(false);}
				
				
				//-> Get the intersection of the three points. This point will be the hight of the triangle
				pcl::PointXYZ middle_point;
				if (!inter_with_three_planes(&coeff_plane_A, &coeff_plane_B, &plane_base_coef, &middle_point)){
					if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting the intersection of the three points\033[0m" << std::endl;
					return(false);}
				
				
				//-> Get the number of divisions between the CDM and the middle point
				pcl::PointCloud<pcl::PointXYZ>::Ptr middle_points (new pcl::PointCloud<pcl::PointXYZ>);
				float *div (new float);
				if (!mesh_line_with_gap(cdm_point, middle_point, density, div, middle_points)){
					if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting the middle points\033[0m" << std::endl;
					return(false);}				
					

		
				//-> Make the same number of divisions in the sides of the triangle
				pcl::PointCloud<pcl::PointXYZ>::Ptr side_1_points (new pcl::PointCloud<pcl::PointXYZ>);
				pcl::PointCloud<pcl::PointXYZ>::Ptr side_2_points (new pcl::PointCloud<pcl::PointXYZ>);
				if (!mesh_line_with_divisions(cdm_point, point_1, *div, side_1_points)){
					if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting side 1 points\033[0m" << std::endl;
					return(false);}					
				if (!mesh_line_with_divisions(cdm_point, point_2, *div, side_2_points)){
					if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed when getting side 2 points\033[0m" << std::endl;
					return(false);}	
							
				
				//-> identify the minimum number of points in order to avoid errors
				int min_1 (side_1_points->size());
				int min_2 (side_2_points->size());
				if (min_1 > min_2) min_1 = min_2;
				

				//-> For each par of points make a mesh-point and store them	
				for (int k=0; k < min_1; k++){
					pcl::PointCloud<pcl::PointXYZ>::Ptr  mesh_line (new pcl::PointCloud<pcl::PointXYZ>);
					
					//->turn off shell alerts
					bool tool_alerts(sh_log);
					sh_log = false;
					
					//-> If the process was ok, store the points
					point_mesh->push_back(side_2_points->points[k]);
					if (mesh_line_with_gap(side_1_points->points[k], side_2_points->points[k], density, mesh_line)){
						
							
						//-> Store them
						if (mesh_line->size() > 2)
						for (int l=1; l < mesh_line->size() - 1; l++)
							point_mesh->push_back(mesh_line->points[l]);}
					
					
					//->put the alert into the last state
					sh_log = tool_alerts;}}}
				
		
		
		//-> Complete the process adding the vertices points and all the cdms
		for (int i=0; i < cloud.size(); i++) 
			point_mesh->push_back(cloud.points[i]);		
		for (int i=0; i < cloud_with_cdms.size(); i++) 
			point_mesh->push_back(cloud_with_cdms.points[i]);
		
		
		
		//-> check if everything was ok
		if (point_mesh->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::make_point_mesh_inside_polygon] Failed making the point-mesh. The final cloud is empty\033[0m" << std::endl;
			return(false);}
		
		

				
		//-> Extract cloned points
		pcl::PointCloud<pcl::PointXYZ>::Ptr point_mesh_wcp (new pcl::PointCloud<pcl::PointXYZ>);
		for (int i = 0; i < point_mesh->size(); i++){
			bool store_point(true);
			for (int j = i+1; j < point_mesh->size(); j++)
				if (point_mesh->points[i].x == point_mesh->points[j].x && point_mesh->points[i].y == point_mesh->points[j].y && point_mesh->points[i].z == point_mesh->points[j].z)
					store_point = false;
			if (store_point)
				point_mesh_wcp->push_back(point_mesh->points[i]);}
				
		
		
		//->Return the mesh-point cloud
		*cloud_out = *point_mesh_wcp;
		
		
		return(true);}
	
	
	//**MAKE A POINT MESH WITH TWO POINTS AND THE NUMER OF DIVISIONS**//
	bool PCLtools::mesh_line_with_divisions(pcl::PointXYZ point_A, pcl::PointXYZ point_B, float div, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){
		
		//-> Check if the points are the same
		if (point_A.x == point_B.x && point_A.y == point_B.y && point_A.z == point_B.z){	
			if (sh_log) std::cout << "\033[1;31m[PCLtools::mesh_line_with_divisions] Failed. The start and the end point are the same\033[0m" << std::endl;
			return(false);}	
		
		
		pcl::PointCloud<pcl::PointXYZ> cloud;
		
		cloud.push_back(point_A);
		for (int i=1; i < div; i++){
			pcl::PointXYZ new_point;
			float inc;
			inc = (float)i / div;
			new_point.x = point_A.x - ((point_A.x - point_B.x)*inc);
			new_point.y = point_A.y - ((point_A.y - point_B.y)*inc);
			new_point.z = point_A.z - ((point_A.z - point_B.z)*inc);
			cloud.push_back(new_point);}
		cloud.push_back(point_B);
		
		
		
		//-> check if there are any errors
		if (cloud.size() <= 2 ){	
			if (sh_log) std::cout << "\033[1;31m[PCLtools::mesh_line_with_divisions] Failed. No points where calculated\033[0m" << std::endl;
			return(false);}	
		
		*cloud_out = cloud;
		
		
		return(true);}
		
	
	//**MAKE A POINT MESH WITH TWO POINTS AND THE DISTANCE BETWEEN THE POINTS**//
	bool PCLtools::mesh_line_with_gap(pcl::PointXYZ point_A, pcl::PointXYZ point_B, float gap, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){
		float *div_out (new float);
		if (!mesh_line_with_gap(point_A, point_B, gap, div_out,cloud_out))
			return(false);
		return(true);}
	bool PCLtools::mesh_line_with_gap(pcl::PointXYZ point_A, pcl::PointXYZ point_B, float gap, float *div_out, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){
		
		//-> Check if the info is correct
		if (gap < 0){			
			if (sh_log) std::cout << "\033[1;31m[PCLtools::mesh_line_with_gap] Failed. The gap is too low\033[0m" << std::endl;
			return(false);}	
		
		
		//-> check if the points are the same
		if (point_A.x == point_B.x && point_A.y == point_B.y && point_A.z == point_B.z){			
			if (sh_log) std::cout << "\033[1;31m[PCLtools::mesh_line_with_gap] Failed. The start and end points " << point_A << " and " << point_B << " are the same point\033[0m" << std::endl;
			return(false);}		
		
		
		float div;
		float x(point_A.x - point_B.x);
		float y(point_A.y - point_B.y);
		float z(point_A.z - point_B.z);
		float module(sqrt(x * x + y * y + z * z));
		
		div = (module / gap);
		*div_out = div;
		

		
		//-> Check if the info is correct
		if (div <= 1){			
			if (sh_log) std::cout << "\033[1;31m[PCLtools::mesh_line_with_gap] Failed. The gap is too hight\033[0m" << std::endl;
			return(false);}	
		
		//-> check if the info is correct
		if (!mesh_line_with_divisions(point_A, point_B, div, cloud_out)){			
			if (sh_log) std::cout << "\033[1;31m[PCLtools::mesh_line_with_gap] Failed. No points where calculated\033[0m" << std::endl;
			return(false);}	
			
		return(true);}
	
	
	//**DISTANCE BETWEEN POINT TO PLANE**//
	bool PCLtools::distance_between_point_2_plane(std::vector <float> plane_coeficcients_in, pcl::PointXYZ point_in, float *distance_out){
		double double_distance;
		if (!distance_between_point_2_plane(plane_coeficcients_in, point_in, &double_distance)){
			return(false);}
		
		*distance_out = (float)double_distance;
		return(true);}
	bool PCLtools::distance_between_point_2_plane(std::vector <float> plane_coeficcients_in, pcl::PointXYZ point_in, double *distance_out){
		
		
		//-> Check if the plane coefficients are ok
		if (plane_coeficcients_in.size() < 4){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::distance_between_point_2_plane] Failed. The number of coefficients of the plane are not ok\033[0m" << std::endl;
			return(false);}	
		
		
		//-> get line coefficients
		std::vector <float> line;
		line.push_back(point_in.x);
		line.push_back(point_in.y);
		line.push_back(point_in.z);
		line.push_back(plane_coeficcients_in[0]);
		line.push_back(plane_coeficcients_in[1]);
		line.push_back(plane_coeficcients_in[2]);
		
		
		//-> get intersection between plane and line
		pcl::PointXYZ inter_point;
		if (!inter_with_line_and_plane(plane_coeficcients_in, line, &inter_point)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::distance_between_point_2_plane] Failed. Can't get the reference point on the plane\033[0m" << std::endl;
			return(false);}		
		
		
		//-> Get vector 
		pcl::PointXYZ distance_vector;
		distance_vector.x = inter_point.x - point_in.x;
		distance_vector.y = inter_point.y - point_in.y;
		distance_vector.z = inter_point.z - point_in.z;
		
		
		//-> Get module 
		double distance;
		if (!vector_module(distance_vector, &distance)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::distance_between_point_2_plane] Failed. Can't get the distance\033[0m" << std::endl;
			return(false);}
		
		
		//-> Return value
		*distance_out = distance;
		
		return(true);}
	
	
	//** get intersection between line and plane**//
	bool PCLtools::inter_with_line_and_plane(std::vector <float> plane_in, std::vector <float> line_in, pcl::PointXYZ *point_out){
		
		//-> Check if the plane coefficients are ok
		if (plane_in.size() < 4){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_line_and_plane] Failed. The number of coefficients of the plane are not ok\033[0m" << std::endl;
			return(false);}	
			
		//-> Check if the line coefficients are ok
		if (line_in.size() < 6){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_line_and_plane] Failed. The number of coefficients of the plane are not ok\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Get line coefficients
		float X0(line_in[0]);
		float Y0(line_in[1]);
		float Z0(line_in[2]);
		float Vx(line_in[3]);
		float Vy(line_in[4]);
		float Vz(line_in[5]);
		
		
		//-> Get plane coefficients
		float A(plane_in[0]);
		float B(plane_in[1]);
		float C(plane_in[2]);
		float D(plane_in[3]);
		
		
		//-> Check if the system has no solution
		double angle;
		pcl::PointXYZ v1;
		v1.x = Vx;
		v1.y = Vy;
		v1.z = Vz;
		pcl::PointXYZ v2;
		v2.x = A;
		v2.y = B;
		v2.z = C;
		if (!angle_between_two_vetors(v1, v2, &angle)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_line_and_plane] Failed. Can't get the angle between the vectors\033[0m" << std::endl;
			return(false);}
		angle =  angle - double_PI/2;
		if (sqrt((angle)*(angle)) <= allowed_error){ 
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_line_and_plane] Failed. The plane and the line are perpendicular\033[0m" << std::endl;
			return(false);}
		
		
		//-> Get lambda numerator 
		double num_lambda;
		num_lambda = (A*X0) + (B*Y0) + (C*Z0) + D;
		num_lambda = -num_lambda;
	
		
		//-> Get lambda denominator
		double den_lambda;
		den_lambda = (A*Vx) + (B*Vy) + (C*Vz);
		
		
		//-> Get lambda
		double lambda;
		lambda = num_lambda / den_lambda;
		
		
		//-> Get point out coordinates
		double X,Y,Z;
		X = X0 + (lambda*Vx);		
		Y = Y0 + (lambda*Vy);		
		Z = Z0 + (lambda*Vz);
		
		//-> Return point
		pcl::PointXYZ inter_point;
		inter_point.x = (float)X;
		inter_point.y = (float)Y;
		inter_point.z = (float)Z;
		
		
		//-> Return point
		*point_out = inter_point;
		
		return(true);}
	
	
	//**GET THE POINT FOR AN INTERCEPTION OF THREE PLANES**//
	bool PCLtools::inter_with_three_planes (std::vector <float> plane_A, std::vector <float> plane_B, std::vector <float> plane_C, pcl::PointXYZ *intersection){	
		return(inter_with_three_planes(&plane_A, &plane_B, &plane_C, intersection));}
	bool PCLtools::inter_with_three_planes (std::vector <float> *plane_A, std::vector <float> *plane_B, std::vector <float> *plane_C, pcl::PointXYZ *intersection){	
	
		//-> Check if the planes coefficients are OK
		if (plane_A->size() != 4){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_three_planes] Failed, the number of coefficients for the plane A is not correct\033[0m" << std::endl;
			return(false);}		
		if (plane_B->size() != 4){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_three_planes] Failed, the number of coefficients for the plane B is not correct\033[0m" << std::endl;
			return(false);}		
		if (plane_C->size() != 4){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_three_planes] Failed, the number of coefficients for the plane C is not correct\033[0m" << std::endl;
			return(false);}
		
		
		//-> Configure system
		std::vector <float> aux_vector;
		Eigen::Matrix3f system_matrix; 
		Eigen::Vector3f system_vector; 
		
		aux_vector = *plane_A;
		system_matrix (0,0) = aux_vector[0]; //Coefficient A
		system_matrix (0,1) = aux_vector[1]; //Coefficient B
		system_matrix (0,2) = aux_vector[2]; //Coefficient C
		system_vector (0) =  -aux_vector[3]; //Coefficient D
		
		aux_vector = *plane_B;
		system_matrix (1,0) = aux_vector[0]; //Coefficient A
		system_matrix (1,1) = aux_vector[1]; //Coefficient B
		system_matrix (1,2) = aux_vector[2]; //Coefficient C
		system_vector (1) =  -aux_vector[3]; //Coefficient D
		
		aux_vector = *plane_C;
		system_matrix (2,0) = aux_vector[0];  //Coefficient A
		system_matrix (2,1) = aux_vector[1];  //Coefficient B
		system_matrix (2,2) = aux_vector[2];  //Coefficient C
		system_vector (2) =  -aux_vector[3];  //Coefficient D
		
	 	
		//-> Solve the system	
		Eigen::LDLT<Eigen::Matrix3f> solver;
		Eigen::Vector3f system_solution;		
		system_solution = system_matrix.inverse() * system_vector;
	
		
		//Store the solution
		pcl::PointXYZ inter;
		inter.x = system_solution(0);
		inter.y = system_solution(1);
		inter.z = system_solution(2);		
	
		
		//-> Return the solution
		*intersection = inter;
		
		
		return(true);}
	

	//**GET THE LINE COEFICIENTS FORN AN INTERSECPTION OF TWO PLANES**//
	bool PCLtools::inter_with_two_planes (std::vector <float> plane_A_in, std::vector <float> plane_B_in, std::vector <float> *line_out){
		return(inter_with_two_planes (&plane_A_in, &plane_B_in, line_out));}
	bool PCLtools::inter_with_two_planes (std::vector <float> *plane_A_in, std::vector <float> *plane_B_in, std::vector <float> *line_out){
		
	
		//-> Check plane coefficients
		if (plane_A_in->size() < 3 || plane_B_in->size() < 3){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_two_planes] There are not enough coefficients in the plane array\033[0m" << std::endl;
			return(false);}
		
	
		//-> Get planes
		std::vector <float> plane_A(*plane_A_in);
		std::vector <float> plane_B(*plane_B_in);
		
		//-> Get line direction, vectorial product and normalize
		pcl::PointXYZ v1(plane_A[0], plane_A[1], plane_A[2]);
		pcl::PointXYZ v2(plane_B[0], plane_B[1], plane_B[2]);
		pcl::PointXYZ Vec_product;
		if (!vector_procuct(v1, v2, &Vec_product)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_two_planes] Can't get the vectorial product\033[0m" << std::endl;
			return(false);}	
		if (!normalize_vector(Vec_product, &Vec_product)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_two_planes] Can't normalize the vectorial product\033[0m" << std::endl;
			return(false);}			
		

		//-> Get point that belong to the line
		std::vector <float> plane_C;
		plane_C.push_back(Vec_product.x);
		plane_C.push_back(Vec_product.y);
		plane_C.push_back(Vec_product.z);
		plane_C.push_back(0);
		pcl::PointXYZ line_point;
		if (!inter_with_three_planes(&plane_A, &plane_B, &plane_C , &line_point)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::inter_with_two_planes] Can't get the line point\033[0m" << std::endl;
			return(false);}			
		
		
		
		//-> Store values
		std::vector <float> line;
		line.push_back(line_point.x);
		line.push_back(line_point.y);
		line.push_back(line_point.z);
		line.push_back(Vec_product.x);
		line.push_back(Vec_product.y);
		line.push_back(Vec_product.z);
		
		
		//-> Return value
		*line_out = line;
		
		return(true);}
	
	
	//**GET THE PLANE COEFFICIONES **//
	bool PCLtools::get_plane_coefficients (pcl::PointXYZ point_A, pcl::PointXYZ point_B, pcl::PointXYZ point_C, std::vector <float> *plane_coeficcients){
		
		//-> get vectors
		pcl::PointXYZ vector_1;
		vector_1.x = point_A.x - point_C.x;
		vector_1.y = point_A.y - point_C.y;
		vector_1.z = point_A.z - point_C.z;
		
		pcl::PointXYZ vector_2;
		vector_2.x = point_B.x - point_C.x;
		vector_2.y = point_B.y - point_C.y;
		vector_2.z = point_B.z - point_C.z;
		
		//-> Get product of the vector 
		pcl::PointXYZ plane_normal;
		if (!vector_procuct(vector_1, vector_2, &plane_normal)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::get_plane_coefficients] Failed when getting the normal vector\033[0m" << std::endl;
			return(false);}
		
		return(get_plane_coefficients (point_A, plane_normal, plane_coeficcients));}
	bool PCLtools::get_plane_coefficients (pcl::PointXYZ point_a, pcl::PointXYZ normal_vector, std::vector <float> *plane_coeficcients_out){
		
		std::vector <float> plane_coeficcients;
		
		
		//-> Get plane coefficients
		plane_coeficcients.push_back(normal_vector.x);
		plane_coeficcients.push_back(normal_vector.y);
		plane_coeficcients.push_back(normal_vector.z);
		
		float d;
		d=-(point_a.x * normal_vector.x) - (point_a.y * normal_vector.y) - (point_a.z * normal_vector.z);

		plane_coeficcients.push_back(d);
		
		*plane_coeficcients_out = plane_coeficcients;
		
		return(true);}

	
	//**EXTRACT A POINTS FROM A POINT CLOUD**//
	bool PCLtools::extract_point_from_the_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, int index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){

		
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
		*cloud = *cloud_in;
		
		
		//-> Check if the cloud is empty
		if (cloud_in->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_point_from_the_cloud] Failed, the cloud is empty\033[0m" << std::endl;
			return(false);}
		
		
		//-> check if the index to extract is correct
		if (index < 0 || index >= cloud_in->size()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_point_from_the_cloud] Failed, index out of range\033[0m" << std::endl;
			return(false);}
		
		//->Extract index
		for (int i=0; i < cloud_in->size(); i++)
			if (i != index) 
				cloud->push_back(cloud_in->points[i]);
		
		*cloud_out = *cloud;
		
		return(true);}
	
	
	//**EXTRACT INDEX FROM CLOUD**//
	bool PCLtools::extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointIndices::Ptr index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, bool invert_index){
		
		
		//-> Convert index
		std::vector<int> int_index;
		if (!convert_pointindices_2_int_vector(index, &int_index)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_index_from_cloud] Failed, can't convert index format\033[0m" << std::endl;
			return(false);}
			
		
		return(extract_index_from_cloud(cloud_in, &int_index, cloud_out, invert_index));}
	bool PCLtools::extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, pcl::PointIndices::Ptr index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){
		
		//-> Convert index
		std::vector<int> int_index;
		if (!convert_pointindices_2_int_vector(index, &int_index)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_index_from_cloud] Failed, can't convert index format\033[0m" << std::endl;
			return(false);}
			

		return(extract_index_from_cloud(cloud_in, &int_index, cloud_out));}
	bool PCLtools::extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<int> *index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out, bool invert_index){
		
		//-> Declare array
		std::vector<int> out_index;

		
		//-> Invert index
		if (invert_index){
			
			if (index->size() < 1){
				*cloud_out = *cloud_in;
				return(true);}
			
			
			//-> Organize index array
			std::vector<int> organized_index(*index);
			if (!organize_vector_ascending(organized_index, &organized_index)){
				if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_index_from_cloud] Failed, can't organize the invert index array\033[0m" << std::endl;
				return(false);}	
		
		
			//-> Generate the negative index array
			int last_value(-1);
			for (int i=0; i < organized_index.size(); i++){
				for (int j=	last_value+1; j < organized_index[i]; j++){
					out_index.push_back(j);}
			
				last_value	= organized_index[i];}
			
			for (int i=last_value +1; i < cloud_in->size(); i++){
				out_index.push_back(i);}}
				
		
		//-> Do not invert index			
		else {out_index = *index;}
		
		
		return (extract_index_from_cloud(cloud_in, &out_index, cloud_out));}
	bool PCLtools::extract_index_from_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in, std::vector<int> *index, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out){
		
		
		//-> Check if the cloud is empty
		if (cloud_in->size() < 1){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_index_from_cloud] Failed, the cloud is empty\033[0m" << std::endl;
			return(false);}
		
		
		//-> Check if the index array is empty
		if (index->size() < 1){
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
			*cloud_out = *cloud;
			return(true);}
		
		
		//-> Check if the number of index is hight that the number of point
		if (cloud_in->size() < index->size()){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_index_from_cloud] Failed, the number of index is hight that the number of points\033[0m" << std::endl;
			return(false);}	


		//-> Organize index array
		std::vector<int> organized_index(*index);
		if (!organize_vector_ascending(organized_index, &organized_index)){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_index_from_cloud] Failed, can't organize the index array\033[0m" << std::endl;
			return(false);}	
		
		
		//-> Check if the highest index point is out of range
		if (organized_index[organized_index.size()-1] >= cloud_in->size() || organized_index[0] < 0){
			if (sh_log) std::cout << "\033[1;31m[PCLtools::extract_index_from_cloud] Failed, one of the index is out of range\033[0m" << std::endl;
			return(false);}	
		
		
		
		//-> Save the index in a cloud
		pcl::PointCloud<pcl::PointXYZ> cloud;
		int last_index(-1);
		for (int i = 0; i < organized_index.size(); i++){
			if (organized_index[i] != last_index){
				last_index = organized_index[i];
				cloud.push_back(cloud_in->points[last_index]);}}
				
	
		
		//-> Return the value
		*cloud_out = cloud;
		
		return (true);}
		
		
		
	#endif
	
			
			
