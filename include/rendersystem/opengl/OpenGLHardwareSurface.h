#ifndef _OPENGL_HARDWARE_SURFACE_H_
#define _OPENGL_HARDWARE_SURFACE_H_ 

#include "rendersystem/opengl/OpenGLRenderSystem.h"

namespace raytracer {


	class OpenGLHardwareSurface
	{
	public:
		OpenGLHardwareSurface(GLuint id, GLenum target, GLint level);
		void upload(Image *img);
	private:
		GLuint mGLTextureID;
		GLenum mTarget;
		GLint mLevel, mWidth, mHeight;
	};

} /* raytracer */

#endif /* _OPENGL_HARDWARE_SURFACE_H_ */
