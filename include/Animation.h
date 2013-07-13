#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "common.h"

namespace raytracer {

	class KeyFrame
	{

	};

	class Track
	{
		
	};
	
	class Animation
	{
		double ticksPerSecond;
		std::string mName;
		public:
			Animation(std::string name) : mName(name) {};

			void addTrack();
	};

} /* namespace raytracer */

#endif	/* _ANIMATION_H_ */