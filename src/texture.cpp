#include "texture.h"

namespace raytracer {

	
	Texture::Texture(const std::string filepath) 
		: mFilePath(filepath), mImage(NULL), mLoaded(false)
		, mHeight(0), mWidth(0)
	{
	}

	bool Texture::isLoaded() const
	{
		return mLoaded;
	}

	bool Texture::load()
	{
		if(mLoaded)
			return true;

		mImage = new Image();

		if(mImage->loadFromSource(mFilePath))
		{
			mHeight = mImage->height;
			mWidth = mImage->width;
			mLoaded = true;
		}
		else
		{
			delete mImage;
		}


		if(!mLoaded)
			std::cout << "Error: could not load Texture from file '" << mFilePath  << "'" << std::endl; 
		
		return mLoaded;
	}

	void Texture::unload()
	{
		mHeight = 0;
		mWidth = 0;

		if(mLoaded)
			delete mImage;
	}

	glm::vec3 Texture::lookUp(const TexCoord &uv) const
	{
		CGUTILS_ASSERT(mImage);
		unsigned int pixelX = uv.x * mWidth;
		unsigned int pixelY = uv.y * mHeight;
		return *mImage->getRGBForPixel(pixelX, pixelY);
	}

} /* namespace raytracer */
