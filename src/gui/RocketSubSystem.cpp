#include "gui/RocketSubSystem.h"

namespace raytracer
{
	RocketSubSystem::RocketSubSystem()
	{
		Rocket::Core::SetSystemInterface(this); 
		Rocket::Core::SetRenderInterface(this);
	}

	float RocketSubSystem::GetElapsedTime()
	{

		std::cout << "GetElapsedTime" << std::endl; 
		return 1.0f;
	}

	void RocketSubSystem::RenderGeometry(Rocket::Core::Vertex* vertices
		, int num_vertices
		, int* indices
		, int num_indices
		, Rocket::Core::TextureHandle texture
		, const Rocket::Core::Vector2f& translation)
	{
		std::cout << "RenderGeometry" << std::endl; 
	}
	
}