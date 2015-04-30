#ifndef POINT_CLOUD_XYZ_CONECTED_HPP
#define POINT_CLOUD_XYZ_CONECTED_HPP

	PointCloudXYZConected::PointCloudXYZConected(){}
	PointCloudXYZConected::~PointCloudXYZConected(){}
	
	
	//**SIZE IF THE CLOUD, NUMBER OF POINTS**//
	int PointCloudXYZConected::size(){
		return (Points.size());}
		
	void PointCloudXYZConected::clear(){
		Points.clear();
		plane.clear();
		line.clear();}
	
	
	bool PointCloudXYZConected::CheckPointPlaneIndexStatus(){
		//-> Check if the connected cloud planes, lines, segments, points status
		int last_plane_index(-1);
		for (int i=0; i < Points.size(); i++){
			//-> Max plane index
			for (int j=0; j < Points[i].plane_index.size(); j++){
				if (Points[i].plane_index[j] > last_plane_index)
					last_plane_index = Points[i].plane_index[j];}}
	
	
		//-> Check if the relations are correct
		if (last_plane_index >= plane.size() && last_plane_index != -1) return(false);
		else  return(true);
	
		
		return(false);}
	bool PointCloudXYZConected::CheckPointLineIndexStatus(){
		//-> Check if the connected cloud planes, lines, segments, points status
		int last_line_index(-1);
		for (int i=0; i < Points.size(); i++){
			//-> Max plane index
			for (int j=0; j < Points[i].line_index.size(); j++){
				if (Points[i].line_index[j] > last_line_index)
					last_line_index = Points[i].line_index[j];}}
	
	
		//-> Check if the relations are correct
		if (last_line_index >= line.size() && last_line_index != -1) return(false);
		else  return(true);
		
		return(false);}
	bool PointCloudXYZConected::CheckPointSegmentIndexStatus(){
		//-> Check if the connected cloud planes, lines, segments, points status
		int last_segment_index(-1);
		for (int i=0; i < Points.size(); i++){
			//-> Max plane index
			for (int j=0; j < Points[i].segment_index.size(); j++){
				if (Points[i].segment_index[j] > last_segment_index)
					last_segment_index = Points[i].segment_index[j];}}
	
	
		//-> Check if the relations are correct
		if (last_segment_index >= segment.size() && last_segment_index != -1) return(false);
		else  return(true);
		
		return(false);}
	bool PointCloudXYZConected::CheckPointConexionsStatus(){
		//-> Check if the connected cloud planes, lines, segments, points status
		int last_point_index(-1);
		for (int i=0; i < Points.size(); i++){
			//-> Max plane index
			for (int j=0; j < Points[i].linear_conexion_index.size(); j++){
				if (Points[i].linear_conexion_index[j] > last_point_index)
					last_point_index = Points[i].linear_conexion_index[j];}}
	
	
		//-> Check if the relations are correct
		if (last_point_index >= Points.size() && last_point_index != -1){
			return(false);}
		else  return(true);}
	bool PointCloudXYZConected::CheckLinePlaneIndexStatus(){
		//-> Check if the connected cloud planes, lines, segments, points status
		int last_plane_index(-1);
		for (int i=0; i < line.size(); i++){
			//-> Max plane index
			for (int j=0; j < line[i].plane_index.size(); j++){
				if (line[i].plane_index[j] > last_plane_index)
					last_plane_index = line[i].plane_index[j];}}
	
	
		//-> Check if the relations are correct
		if (last_plane_index >= plane.size() && last_plane_index != -1) return(false);
		else  return(true);
	
		
		return(false);}
	bool PointCloudXYZConected::CheckSegmentPlaneIndexStatus(){
		//-> Check if the connected cloud planes, lines, segments, points status
		int last_plane_index(-1);
		for (int i=0; i < segment.size(); i++){
			//-> Max plane index
			for (int j=0; j < segment[i].plane_index.size(); j++){
				if (segment[i].plane_index[j] > last_plane_index)
					last_plane_index = segment[i].plane_index[j];}}
	
	
		//-> Check if the relations are correct
		if (last_plane_index >= plane.size() && last_plane_index != -1) return(false);
		else  return(true);
	
		
		return(false);}
	bool PointCloudXYZConected::CheckSegmentLineIndexStatus(){
		//-> Check if the connected cloud planes, lines, segments, points status
		int last_line_index(-1);
		for (int i=0; i < segment.size(); i++){
			//-> Max plane index
			for (int j=0; j < segment[i].line_index.size(); j++){
				if (segment[i].line_index[j] > last_line_index)
					last_line_index = segment[i].line_index[j];}}
	
	
		//-> Check if the relations are correct
		if (last_line_index >= line.size() && last_line_index != -1) return(false);
		else  return(true);
	
		
		return(false);}
	bool PointCloudXYZConected::CheckConnecctedPointStatus(){
		bool plane_status;
		bool line_status;
		bool segment_status; 
		bool points_status;
		return(CheckConnecctedPointStatus(&plane_status, &line_status, &segment_status, &points_status));}
	bool PointCloudXYZConected::CheckConnecctedPointStatus(bool *PointPlaneIndexStatus, bool *PointLineIndexStatus, bool *PointSegmentIndexStatus, bool *PointConexionsStatus){
		*PointPlaneIndexStatus = CheckPointLineIndexStatus();
		*PointLineIndexStatus = CheckPointPlaneIndexStatus();
		*PointSegmentIndexStatus = CheckPointSegmentIndexStatus();
		*PointConexionsStatus = CheckPointConexionsStatus();
		
		if (*PointPlaneIndexStatus && *PointLineIndexStatus && *PointSegmentIndexStatus && *PointConexionsStatus) 
			return(true);
		else 
			return(false);}
	bool PointCloudXYZConected::CheckAllStatus(){
		bool plane_status;
		bool line_status;
		bool segment_status; 
		bool points_status;
		bool LinePlaneIndexStatus;
		bool SegmentPlaneIndexStatus;
		bool SegmentLineIndexStatus;
		return(CheckAllStatus(&plane_status, &line_status, &segment_status, &points_status, &LinePlaneIndexStatus, &SegmentPlaneIndexStatus, &SegmentLineIndexStatus));}
	bool PointCloudXYZConected::CheckAllStatus(bool *PointPlaneIndexStatus, bool *PointLineIndexStatus, bool *PointSegmentIndexStatus, bool *PointConexionsStatus, bool *LinePlaneIndexStatus, bool *SegmentPlaneIndexStatus, bool *SegmentLineIndexStatus){
		*PointPlaneIndexStatus = CheckPointLineIndexStatus();
		*PointLineIndexStatus = CheckPointPlaneIndexStatus();
		*PointSegmentIndexStatus = CheckPointSegmentIndexStatus();
		*PointConexionsStatus = CheckPointConexionsStatus();
		*LinePlaneIndexStatus = CheckLinePlaneIndexStatus();
		*SegmentPlaneIndexStatus = CheckSegmentPlaneIndexStatus();
		*SegmentLineIndexStatus = CheckSegmentLineIndexStatus();
		
		
		if (*PointPlaneIndexStatus && *PointLineIndexStatus && *PointSegmentIndexStatus && *PointConexionsStatus && *LinePlaneIndexStatus && *SegmentPlaneIndexStatus && *SegmentLineIndexStatus) 
			return(true);
		else 
			return(false);}
	
	
	#endif
	
			
			
			
			
			
			
			
