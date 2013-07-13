#ifndef _OPENGL_TEXTURE_H_
#define _OPENGL_TEXTURE_H_ 

#include "common.h"
#include "rendersystem/HardwareTexture.h"
#include "rendersystem/opengl/OpenGLHardwareSurface.h"
#include "rendersystem/opengl/OpenGLRenderSystem.h"
#include <vector>

namespace raytracer {

	class OpenGLHardwareSurface; // forward declaration

	class OpenGLTexture : public HardwareTexture
	{
	public:
		OpenGLTexture(const std::string &filePath) : HardwareTexture(filePath), mAllocated(false), mGLTextureID(-1) {};
		virtual ~OpenGLTexture();

		bool setupHardwareBuffers();
		virtual void bind();
		virtual void unbind();

		GLenum getTarget();
	protected:
		virtual bool upload();
	private:
		bool mAllocated;
		GLuint mGLTextureID;

		typedef std::vector<OpenGLHardwareSurface*> GLSurfaceList;
		GLSurfaceList mSurfaces;
	};

} /* raytracter */

#endif /* _OPENGL_TEXTURE_H_ */
