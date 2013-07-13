#include "light.h"

namespace raytracer {


	Light::Light(const std::string &name) : name(name), mAmbient(0), mDiffuse(0)
		, mSpecular(0), position(0), direction(0)
	{

	}

	void Light::genShadowRay(const glm::vec3 point, Ray &r) const
	{
		r = Ray(point, position);
	}

	void Light::setColor(const RGB &ambient, const RGB &diffuse, const RGB &specular)
	{
		mAmbient = ambient;
		mDiffuse = diffuse;
		mSpecular = specular;
	}

	void Light::setLocation(const glm::vec3 &position, const glm::vec3 &direction)
	{
		this->position = position;
		this->direction = direction;
	}

	void Light::setAttenuation(float constant, float linear, float quadratic)
	{
		this->attenuationConstant = constant;
		this->attenuationLinear = linear;
		this->attenuationQuadratic = quadratic;
	}

	void Light::visitRenderables(RenderableVisitor &r) const
	{
		// no renderables for lights
	}

	const AABB& Light::getWorldBounds()
	{
		return mWorldBounds;
	}

	void PointLight::getAttenuatedRadiance(const Ray &r, RGB &out) const
	{
		float cofactor = attenuationConstant + attenuationLinear * r.d + attenuationQuadratic * pow(r.d, 2);
		cofactor = clamp(1.0f / cofactor, 0.0, 1.0);

		//std::cout << "d " << d << " cofactor " << cofactor << " result " << diffuse * cofactor << std::endl;

		out = mDiffuse * cofactor;
	}

	AreaLight::AreaLight(const std::string &name, const glm::vec3 &side_h, const glm::vec3 &side_w) : Light(name)
	{
		this->side_h = side_h;
		this->side_w = side_w;
		this->normal = glm::normalize(glm::cross(side_h, side_w));
		this->area = glm::length(glm::cross(side_w, side_h));
	}

	void AreaLight::genShadowRay(const glm::vec3 point, Ray &r) const
	{
		float variance_h = randf();
		float variance_w = randf();

		glm::vec3 sample_point = position + (variance_h * side_h) + (variance_w * side_w);

		r = Ray(point, sample_point);
	}

	void AreaLight::getAttenuatedRadiance(const Ray &r, RGB &out) const
	{
		glm::vec3 light_exitant = glm::normalize(r.p - r.q);

		float cofactor = attenuationConstant + attenuationLinear * r.d + attenuationQuadratic * pow(r.d, 2);
		cofactor = clamp(1.0f / cofactor, 0.0, 1.0);

		out = mDiffuse * cofactor * fmaxf(glm::dot(normal, light_exitant), 0) * area;
	}

	std::ostream& operator<<(std::ostream& o, const Light& b)
	{
		return o << "Light '" << b.name << "' {\n" \
		<< "\tposition: " << b.position << "\n" \
		<< "\tattenuationConstant:" << b.attenuationConstant << "\n" \
		<< "\tattenuationLinear:" << b.attenuationLinear << "\n" \
		<< "\tattenuationQuadratic:" << b.attenuationQuadratic << "\n" \
		<< "\tdiffuse:" << b.mDiffuse << "\n" \
		<< "\tambient:" << b.mAmbient << "\n" \
		<< "\tspecular:" << b.mSpecular << "\n" \
		<< "}";
	}

} /* namespace raytracer */
