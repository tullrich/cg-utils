#ifndef _OPENGL_SHADER_PROGRAM_H_
#define _OPENGL_SHADER_PROGRAM_H_ 

#include <map>
#include "common.h"
#include "rendersystem/opengl/OpenGLRenderSystem.h"

namespace raytracer {

	class OpenGLLowLevelShader; // forward declaration

	struct GLAttributeDefinition
	{
		std::string mName;
		int mLocation;

		GLAttributeDefinition(const std::string &name, int location) : mName(name), mLocation(location) {};
	};

	struct GLTextureDefinition
	{
		std::string mName;
		FixedTexture mTextureUnit;
		GLenum mType;

		GLTextureDefinition(const std::string &name, FixedTexture texUnit, GLenum type) : mName(name), mTextureUnit(texUnit), mType(type) {};
	};

	struct GLFixedUniformDefinition
	{
		std::string mName;
		FixedUniform mKey;
		GLenum mType;
		
		GLFixedUniformDefinition(const std::string &name, FixedUniform key, GLenum type) : mName(name), mKey(key), mType(type) {};
	};

	struct GLUniformBinding
	{
		std::string mName;
		GLenum mType;
		GLuint mIndex;
		GLint mLocation;
		GLint mSize; 

		GLUniformBinding() : mType(0), mIndex(-1), mLocation(-1), mSize(0) {};
		GLUniformBinding(const std::string &name, GLenum type, GLuint index, GLint location, GLint size) 
			: mName(name), mType(type), mIndex(index), mLocation(location), mSize(size) {};
	};

	class OpenGLShaderProgram
	{
	public:
		OpenGLShaderProgram();
		virtual ~OpenGLShaderProgram();
	
		void attach(OpenGLLowLevelShader &s);
		void link();
		void activate();

		int getUniformCount();
		bool getUniformName(int index, std::string &name);
		int getUniformLocation(const std::string &name);
		bool queryUniformInfo(int index, GLUniformBinding &binding);

		int getAttributeCount();
		bool getAttributeName(int index, std::string &name);
		int getAttributeLocation(const std::string &name);
		
		void bindAttributeLocation(int index, const std::string &name);

		void binddd();
		
		void setUniformMatrix3(FixedUniform key, const Matrix3 &data);
		void setUniformMatrix3(const std::string &name, const Matrix3 &data);
		void setUniformMatrix4(FixedUniform key, const Matrix4 &data);
		void setUniformMatrix4(const std::string &name, const Matrix4 &data);
		void setUniformVector4(FixedUniform key, const Vector4 &data);
		void setUniformVector4(const std::string &name, const Vector4 &data);
		void setUniformVector3(FixedUniform key, const Vector3 &data);
		void setUniformVector3(const std::string &name, const Vector3 &data);
		void setUniformFloat(FixedUniform key, float data);
		void setUniformFloat(const std::string &name, float data);

		bool isBad() { return mIsBad; }
	protected:
		void logProgramInfo();
		void bindFixedAttributes();
		void buildUniformBindings();
		void bindTextureDefinition(GLTextureDefinition t,  GLUniformBinding &b);

		GLFixedUniformDefinition* getFixedDefinition(std::string &name);
		GLTextureDefinition* getTextureDefinition(std::string &name);
		
	private:
		static GLAttributeDefinition sFixedAttributes[];
		static GLFixedUniformDefinition sFixedUniforms[];
		static GLTextureDefinition sFixedTextures[];

		typedef std::map<std::string, GLUniformBinding> NameUniformBindingMap;
		typedef std::map<FixedUniform, GLUniformBinding> KeyUniformBindingMap;
		typedef std::map<FixedTexture, GLUniformBinding> KeyTextureBindingMap;

		NameUniformBindingMap mActiveUniformsByName;
		KeyUniformBindingMap mFixedActiveUniforms;
		KeyTextureBindingMap mActiveTextures;

		OpenGLLowLevelShader *mVertexProgram, *mGeometryProgram, *mFragmentProgram;
		GLuint mProgramID, mVertexArrayObject;
		bool mIsLinked, mIsBad;
	};

} /* raytracer */

#endif /* _OPENGL_SHADER_PROGRAM_H_ */
