#include "rendersystem/HardwareTexture.h"

namespace raytracer {
	
	bool HardwareTexture::load()
	{

		if(!mLoaded)
		{
			if(!Texture::load())
			{
				return false;
				std::cout << "error loading image for texture" << std::endl; 
			}
		}

		if(!mUploaded)
		{
			setupHardwareBuffers();
			return upload();
		}

		return true;
	}

	void HardwareTexture::initNumMips()
	{
		mNumMips = 0;

		if(mWidth > 0 && mHeight > 0)
		{
			int width = mWidth;
			int height = mHeight;

			do {
				if(width > 1)
				{
					width = width / 2;
				}
				if(height > 1)
				{
					height = height / 2;
				}
				mNumMips++;
			} while (!(width == 1 && height == 1));
		}
	}

} /* namespace raytracer */
