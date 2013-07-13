#ifndef _ROCKET_SUBSYSTEM_H_
#define _ROCKET_SUBSYSTEM_H_

#include "common.h"
#include "Rocket/Core.h"
#include "Rocket/Core/SystemInterface.h"
#include "Rocket/Core/RenderInterface.h"

namespace raytracer {
	
	class RocketSubSystem : public Rocket::Core::SystemInterface, public Rocket::Core::RenderInterface
	{
	public:
		RocketSubSystem();
		virtual ~RocketSubSystem() {};
		
		// SystemInterface
		virtual float GetElapsedTime();

		// RenderInterface
		virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices
			, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
		virtual void EnableScissorRegion(bool enable) {};
		virtual void SetScissorRegion(int x, int y, int width, int height) {};
	};

} /* namespace raytracer */

#endif