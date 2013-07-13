#ifndef _HARDWARE_TEXTURE_H_
#define _HARDWARE_TEXTURE_H_ 

#include "texture.h"

namespace raytracer {

	enum TextureType
	{
		TEX_TYPE_1D,
		TEX_TYPE_2D,
		TEX_TYPE_CUBE,
	};

	class HardwareTexture : public Texture
	{
	public:
		HardwareTexture(const std::string &filePath) : Texture(filePath), mType(TEX_TYPE_2D), mUploaded(false), mNumMips(0) {};

		TextureType getTextureType() { return mType; }
		virtual bool load();
		virtual void bind() = 0;
		virtual void unbind() = 0;
	protected:
		virtual bool setupHardwareBuffers() = 0;
		virtual bool upload() = 0;
		void initNumMips();

		TextureType mType;
		bool mUploaded;
		int mNumMips;
	};

} /* raytracer */

#endif /* _HARDWARE_TEXTURE_H_ */
