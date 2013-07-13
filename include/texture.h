#ifndef _TEXTURE_H_
#define _TEXTURE_H_ 

#include "common.h"
#include "rtimage.h"

namespace raytracer {

	using namespace cgutils;

	class Texture
	{
	public:

		/**
		 * Texture representing filepath on disk
		 */
		Texture(const std::string filepath);

		/**
		 * Load the image from disk using the filepath provided during construction
		 * @return TRUE if loading was successfull, FALSE otherwise
		 */
		virtual bool load();
		
		void unload();

		/**
		 * check if this texture has been loaded from disk
		 * @return FALSE if load() has not returned successfully for this {@link Texture}
		 */
		bool isLoaded() const;


		glm::vec3 lookUp(const TexCoord &uv) const;

	protected:
		bool mLoaded;
		Image *mImage;
		unsigned int mHeight, mWidth;
		std::string mFilePath;
	};


	class  TextureManager : public ResourceManager<std::string, Texture> {};

} /* raytracer */

#endif /* _TEXTURE_H_ */
