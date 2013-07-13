#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "common.h"
#include "texture.h"

namespace raytracer {

	/**
	 * material definition referenced by each {@link Mesh}
	 */
	class Material
	{
		friend std::ostream& operator<<(std::ostream& o, const Material& b);

	public:
		Material() : name(""), mDiffuse(0), mSpecular(0), mAmbient(0), mEmissive(0)
			, mDiffuseMap(NULL), mSpecularMap(NULL), mEmissiveMap(NULL), mNormalMap(NULL)
			, mShininess(0), mLoaded(false) { };
		Material(const std::string name) : name(name), mDiffuse(0), mSpecular(0), mAmbient(0), mEmissive(0)
			, mDiffuseMap(NULL), mSpecularMap(NULL), mEmissiveMap(NULL), mNormalMap(NULL)
			, mShininess(0), mLoaded(false) { };

		virtual glm::vec3 BRDF(const TexCoord *uv) const;
		virtual glm::vec3 Le(const TexCoord *uv) const;

		void setDiffuse(RGB diffuse) { mDiffuse = diffuse; }
		void setSpecular(RGB specular) { mSpecular = specular; }
		void setShininess(float shininess) { mShininess = shininess; }
		void setAmbient(RGB ambient) { mAmbient = ambient; }
		void setEmissive(RGB emissive) { mEmissive = emissive; }
		void setDiffuseTexture(Texture *t) { mDiffuseMap = t; };
		void setSpecularTexture(Texture *t) { mSpecularMap = t; };
		void setEmissiveTexture(Texture *t) { mEmissiveMap = t; };
		void setNormalTexture(Texture *t) { mNormalMap = t; }

		const RGB& getDiffuse() const { return mDiffuse; }
		const RGB& getSpecular() const { return mSpecular; }
		float getShininess() const { return mShininess; }
		const RGB& getAmbient() const { return mAmbient; }
		const RGB& getEmissive() const { return mEmissive; }
		Texture* getDiffuseTexture() const { return mDiffuseMap; }
		Texture* getSpecularTexture() const { return mSpecularMap; }
		Texture* getEmissiveTexture() const { return mEmissiveMap; }
		Texture* getNormalTexture() const { return mNormalMap; }

		bool hasDiffuseTexture() const { return mDiffuseMap != NULL; }
		bool hasSpecularTexture() const { return mSpecularMap != NULL; }
		bool hasEmissiveTexture() const { return mEmissiveMap != NULL; }
		bool hasNormalTexture() const { return mNormalMap != NULL; }

		void ensureLoaded();

	private:
		/**
		 * material name
		 */
		std::string name;

		/**
		 * diffuse, specular, & ambient coefficents for each RGB
		 */
		RGB mDiffuse, mSpecular, mAmbient;

		/**
		 * emmisive component of this light
		 */
		RGB mEmissive;

		/**
		 *  specular shineness exponent 
		 */
		float mShininess;


		Texture *mDiffuseMap, *mSpecularMap, *mEmissiveMap, *mNormalMap;

		bool mLoaded;
	};

	/**
	 * Insert stream operator for Material
	 */
	std::ostream& operator<<(std::ostream& o, const Material& b);

	/**
	 * Singleton managing a global material cache
	 */
	class  MaterialManager : public ResourceManager<std::string, Material>
	{
	public:
		MaterialManager();
		virtual Material* getDefaultObject();

	private:
		Material *mDefaultMaterial;
	};

}; /* namespace raytracer */

#endif /* _MATERIAL_H */
