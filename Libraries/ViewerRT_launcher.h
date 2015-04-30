#ifndef ViewerRT_LAUNCHER_H
#define ViewerRT_LAUNCHER_H

#include "ViewerRT.h"

	class ViewerRT_launcher
		{
		
		public:

			ViewerRT_launcher (ViewerRT *viewer_real_time);	
			~ViewerRT_launcher ();	

			//Public launchers
			void launcher_1 ();
		
		
		private:
			
			//Private Launchers
			ViewerRT *viewer;
			

		
};	
	#include "ViewerRT_launcher.hpp"
#endif

