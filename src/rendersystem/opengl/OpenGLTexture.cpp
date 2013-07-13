#include "rendersystem/opengl/OpenGLTexture.h"

namespace raytracer {

	OpenGLTexture::~OpenGLTexture()
	{
		if(mAllocated)
		{
			GLSurfaceList::iterator i = mSurfaces.begin();
			for(; i < mSurfaces.end(); i++)
			{
				delete (*i);
			}
			mSurfaces.clear();
			glDeleteTextures(1, &mGLTextureID);
		}
	}
	
	bool OpenGLTexture::setupHardwareBuffers()
	{
		initNumMips();

		if(!mAllocated)
		{
			glGenTextures(1, &mGLTextureID);

			GLenum binding = GL_TEXTURE_1D;
			switch(mType)
			{
				case TEX_TYPE_1D:
					binding = GL_TEXTURE_1D;
					break;
				case TEX_TYPE_2D:
					binding = GL_TEXTURE_2D;
					break;
				case TEX_TYPE_CUBE:
					binding = GL_TEXTURE_CUBE_MAP;
					break;
			}
			glBindTexture(binding, mGLTextureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			// preallocate
			int width = mWidth;
			int height = mHeight;
			for(int i  = 0; i < mNumMips; i++)
			//for(int i  = 0; i < 1; i++)
			{
				switch(mType)
				{
					case TEX_TYPE_1D:
						glTexImage1D(GL_TEXTURE_1D, i, GL_RGB, width, 0, GL_RGB, GL_FLOAT, NULL);
						break;
					case TEX_TYPE_2D:
						glTexImage2D(GL_TEXTURE_2D, i, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, NULL);
						break;
					case TEX_TYPE_CUBE:
						std::cout << "CUBEMAPS NOT YET SUPPORTED" << std::endl; 
						break;
				}

				mSurfaces.push_back(new OpenGLHardwareSurface(mGLTextureID, binding, i));

				if(width > 1) width = width / 2;
				if(height > 1) height = height / 2;
			}

			mAllocated = true;
		}

		return mAllocated;
	}

	bool OpenGLTexture::upload()
	{
		for(int i  = 0; i < mNumMips; i++)
		{
			mSurfaces[i]->upload(mImage);
		}

		mUploaded = true;
		return mUploaded;
	}

	void OpenGLTexture::bind()
	{
		if(!mAllocated)
		{
			std::cout << "OpenGLTexture error, attempted bind of unallocated texture " << mFilePath << std::endl;
			return; 
		}

		GLenum binding = getTarget();
		glBindTexture(binding, mGLTextureID);
	}

	void OpenGLTexture::unbind()
	{
		GLenum binding = getTarget();
		glBindTexture(binding, 0);
	}

	GLenum OpenGLTexture::getTarget()
	{
		switch(mType)
		{
			case TEX_TYPE_1D:
				return GL_TEXTURE_1D;
			case TEX_TYPE_2D:
				return GL_TEXTURE_2D;
			case TEX_TYPE_CUBE:
				return GL_TEXTURE_CUBE_MAP;
		}
	}

} /* namespace raytracer */
