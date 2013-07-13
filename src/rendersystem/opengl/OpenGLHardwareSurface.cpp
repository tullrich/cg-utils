#include "rendersystem/opengl/OpenGLHardwareSurface.h"

namespace raytracer {

	OpenGLHardwareSurface::OpenGLHardwareSurface(GLuint id, GLenum target, GLint level) 
		: mGLTextureID(id), mTarget(target), mLevel(level)
	{
		glBindTexture(mTarget, mGLTextureID);

		glGetTexLevelParameteriv(mTarget, level, GL_TEXTURE_WIDTH, &mWidth);
		glGetTexLevelParameteriv(mTarget, level, GL_TEXTURE_HEIGHT, &mHeight);
	}

	void OpenGLHardwareSurface::upload(Image *img)
	{
		glBindTexture(mTarget, mGLTextureID);
		if(img->width != mWidth || img->height != mHeight)
		{
			//std::cout << "OpenGLHardwareSurface: attempting upload of incorrectly sized mip level, using software mipmap creation" << std::endl; 
			gluBuild2DMipmapLevels(mTarget, GL_RGB, img->width, img->height, GL_RGB, GL_FLOAT, 0, mLevel, mLevel, img->getImageBuffer());
		}
		else
		{
			glTexImage2D(mTarget, mLevel, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_FLOAT, img->getImageBuffer());
		}
	
	}

} /* namespace raytracer */
