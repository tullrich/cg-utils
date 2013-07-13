#include "rendersystem/opengl/OpenGLShaderProgram.h"
#include <cstring>

namespace raytracer {
	
	GLAttributeDefinition OpenGLShaderProgram::sFixedAttributes[] = 
	{
		GLAttributeDefinition("vertex", FA_VERTICES),
		GLAttributeDefinition("normal", FA_NORMALS),
		GLAttributeDefinition("diffuse", FA_DIFFUSE_COLORS),
		GLAttributeDefinition("specular", FA_SPECULAR_COLORS),
		GLAttributeDefinition("uv0", FA_TEX_COORDS_0),
		GLAttributeDefinition("uv1", FA_TEX_COORDS_1),
		GLAttributeDefinition("uv2", FA_TEX_COORDS_2),
		GLAttributeDefinition("uv3", FA_TEX_COORDS_3),
		GLAttributeDefinition("uv4", FA_TEX_COORDS_4),
		GLAttributeDefinition("uv5", FA_TEX_COORDS_5),
		GLAttributeDefinition("uv6", FA_TEX_COORDS_6),
	};

	GLTextureDefinition OpenGLShaderProgram::sFixedTextures[] =
	{
		GLTextureDefinition("MapDiffuse", FT_DIFFUSE, GL_SAMPLER_2D),
		GLTextureDefinition("MapNormal", FT_NORMAL, GL_SAMPLER_2D),
		GLTextureDefinition("MapSpecular", FT_SPECULAR, GL_SAMPLER_2D),
		GLTextureDefinition("MapEmissive", FT_EMISSIVE, GL_SAMPLER_2D),
	};

	GLFixedUniformDefinition OpenGLShaderProgram::sFixedUniforms[] =
	{
		GLFixedUniformDefinition("ModelViewProjection", FU_ModelViewProjection, GL_FLOAT_MAT4),
		GLFixedUniformDefinition("ModelView", FU_ModelView, GL_FLOAT_MAT4),
		GLFixedUniformDefinition("InverseViewProjection", FU_InverseViewProjection, GL_FLOAT_MAT4),
		GLFixedUniformDefinition("diffuseColor", FU_DiffuseColor, GL_FLOAT_VEC4),
		GLFixedUniformDefinition("NormalMatrix", FU_NormalMatrix, GL_FLOAT_MAT3),
		GLFixedUniformDefinition("Shininess", FU_Shininess, GL_FLOAT),
		GLFixedUniformDefinition("FogParameters", FU_FogParameters, GL_FLOAT_VEC3),
		GLFixedUniformDefinition("FogColor", FU_FogColor, GL_FLOAT_VEC3),
	};

	OpenGLShaderProgram::OpenGLShaderProgram() 
		: mVertexProgram(NULL), mGeometryProgram(NULL), mFragmentProgram(NULL), mProgramID(0)
		, mVertexArrayObject(0), mIsLinked(false), mIsBad(false)
	{
		mProgramID = glCreateProgram();

		if(mProgramID == 0)
		{
			std::cout << "Error in OpenGLShaderProgram() with glCreateProgram" << std::endl; 
		}
	}

	OpenGLShaderProgram::~OpenGLShaderProgram()
	{
		glDeleteProgram(mProgramID);
	}

	void OpenGLShaderProgram::attach(OpenGLLowLevelShader &s)
	{
		if(mProgramID == 0)
		{
			std::cout << "error in OpenGLShaderProgram::attach, no program handle" << std::endl; 
			return;
		}

		OpenGLLowLevelShader **pipelineSlot;
		switch(s.getShaderType())
		{
			case OpenGLLowLevelShader::GPU_VERTEX_SHADER: pipelineSlot = &mVertexProgram; break;
			case OpenGLLowLevelShader::GPU_GEOMETRY_SHADER: pipelineSlot = &mGeometryProgram; break;
			case OpenGLLowLevelShader::GPU_FRAGMENT_SHADER: pipelineSlot = &mFragmentProgram; break;
		}
		if(*pipelineSlot != NULL)
		{
			std::cout << "error in OpenGLShaderProgram::attach replacing existing shader!" << std::endl;
			return;
		}
		*pipelineSlot = &s;

		if(!s.isCompiled())
		{
			s.loadSource();

			if(s.isBad())
				return;
		}

		glAttachShader(mProgramID, s.getShaderID());
	}

	void OpenGLShaderProgram::link()
	{
		if(mIsLinked)
			return;

		if (!mVertexProgram && !mGeometryProgram && !mFragmentProgram)
		{
			std::cout << "Error in OpenGLShaderProgram::link() no shaders attached" << std::endl; 
			return;
		}

		if(mProgramID == 0)
		{
			std::cout << "error in OpenGLShaderProgram::link, no program handle" << std::endl; 
			return;
		}

		bindFixedAttributes();

		glGenVertexArrays(1, &mVertexArrayObject);
		glLinkProgram(mProgramID);

		GLint errorstatus = GL_FALSE;
		glGetProgramiv(mProgramID, GL_LINK_STATUS, &errorstatus);
		if(errorstatus == GL_TRUE)
		{
			mIsLinked = true;
			buildUniformBindings();
		}
		else
		{
			std::cout << "error in OpenGLLowLevelShader::loadSource could not compile shader" << std::endl;
			logProgramInfo();
			mIsBad = true;
		}

	}

	void OpenGLShaderProgram::bindFixedAttributes()
	{
		int fixedAttributeCount = sizeof(sFixedAttributes) / sizeof(GLAttributeDefinition);

		for (int i = 0; i < fixedAttributeCount; ++i)
		{
			bindAttributeLocation(sFixedAttributes[i].mLocation, sFixedAttributes[i].mName);
		}
	}

	void OpenGLShaderProgram::buildUniformBindings()
	{
		int numActiveUniforms = getUniformCount();
		std::cout << "buildUniformBindings  " << numActiveUniforms << std::endl; 

		for (int i = 0; i < numActiveUniforms; ++i)
		{
			GLUniformBinding b;
			if(queryUniformInfo(i, b))
			{

				GLTextureDefinition *tex = getTextureDefinition(b.mName);
				if(tex)
				{
					bindTextureDefinition(*tex, b);
					continue;
				}

				mActiveUniformsByName[b.mName] = b;
				GLFixedUniformDefinition *fixed = getFixedDefinition(b.mName);
				if(fixed)
				{
					if(fixed->mType == b.mType)
					{
						mFixedActiveUniforms[fixed->mKey] = b;
						std::cout << "Got fixed uniform: '"<< b.mName  
							<< "' index: " << b.mIndex  
							<< " location: " << b.mLocation << std::endl; 
					}
					else
					{
						std::cout << "Warning: found matching fixed binding " << b.mName << " with mismatching type" << std::endl;
					}
				}
				else
				{
					std::cout << "Got custom uniform: '"<< b.mName  
						<< "' index: " << b.mIndex  
						<< " location: " << b.mLocation << std::endl; 
				}
				
			}	
			else
			{
				std::cout << "buildUniformBindings Error querying bindings when linking shader!" << std::endl;
				mIsBad = true;
				break;
			}
		}
	}

	void OpenGLShaderProgram::bindTextureDefinition(GLTextureDefinition t,  GLUniformBinding &b)
	{
		std::cout << "bindTextureDefinition "<< b.mName << " " << t.mTextureUnit << std::endl; 
		glUseProgram(mProgramID);
		glUniform1i(b.mLocation, t.mTextureUnit);

		mActiveTextures[t.mTextureUnit] = b;
	}

	GLFixedUniformDefinition* OpenGLShaderProgram::getFixedDefinition(std::string &name)
	{
		int numDefinitions = sizeof(sFixedUniforms) / sizeof(GLFixedUniformDefinition);
		for (int i = 0; i < numDefinitions; ++i)
		{
			if(sFixedUniforms[i].mName == name)
			{
				return &sFixedUniforms[i];
			}
		}
		return NULL;
	}

	GLTextureDefinition* OpenGLShaderProgram::getTextureDefinition(std::string &name)
	{
		int numDefinitions = sizeof(sFixedTextures) / sizeof(GLTextureDefinition);
		for (int i = 0; i < numDefinitions; ++i)
		{
			if(sFixedTextures[i].mName == name)
			{
				return &sFixedTextures[i];
			}
		}
		return NULL;
	}

	void OpenGLShaderProgram::logProgramInfo()
	{
		GLint logSize = 0;
		glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &logSize);

		if(logSize != 0)
		{
			GLsizei sizei = logSize;
			GLchar msg[logSize];
			glGetProgramInfoLog(mProgramID, sizei, NULL, msg);

			std::cout << "Shader program link " << msg << std::endl; 
		}
	}

	void OpenGLShaderProgram::activate()
	{
		if(!mIsLinked && !mIsBad)
			link();

		if(mIsLinked)
		{
            GLenum glErr = glGetError();
            if(glErr != GL_NO_ERROR)
            {
			    //reportGLSLError( glErr, "GLSLLinkProgram::Activate",
				//    "Error prior to using GLSL Program Object : ", mGLHandle, false, false);
            }

			glUseProgram(mProgramID);

            glErr = glGetError();
            if(glErr != GL_NO_ERROR)
            {
			    //reportGLSLError( glErr, "GLSLLinkProgram::Activate",
			}
		}
	}

	bool OpenGLShaderProgram::getAttributeName(int index, std::string &name)
	{
		if(!mIsLinked)
			return false;


		GLint maxNameSize = 0;
		glGetProgramiv(mProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameSize);
		if(maxNameSize != 0)
		{
			GLchar attrName[maxNameSize];
			GLint size;
			GLenum type;
			glGetActiveAttrib(mProgramID, index, maxNameSize, NULL, &size, &type, attrName);

			name = std::string(attrName);
			return true;
		}
		
		return false;
	}

	void OpenGLShaderProgram::binddd()
	{
		glBindVertexArray(mVertexArrayObject);
	}

	int OpenGLShaderProgram::getAttributeCount()
	{
		if(!mIsLinked)
			return 0;

		GLint numAttributes = 0;
		glGetProgramiv(mProgramID, GL_ACTIVE_ATTRIBUTES, &numAttributes);

		return numAttributes;
	}

	int OpenGLShaderProgram::getUniformCount()
	{
		if(!mIsLinked)
			return 0;

		GLint numAttributes = 0;
		glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORMS, &numAttributes);

		return numAttributes;
	}

	bool OpenGLShaderProgram::getUniformName(int index, std::string &name)
	{
		if(!mIsLinked)
			return false;


		GLint maxNameSize = 0;
		glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameSize);

		if(maxNameSize != 0)
		{
			GLchar attrName[maxNameSize];
			GLint size;
			GLenum type;
			glGetActiveUniform(mProgramID, index, maxNameSize, NULL, &size, &type, attrName);
			name = std::string(attrName);
			return true;
		}
		
		return false;
	}

	bool OpenGLShaderProgram::queryUniformInfo(int index, GLUniformBinding &binding)
	{
		if(mIsLinked)
		{
			GLint maxNameSize = 0;
			glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameSize);
			if(maxNameSize != 0)
			{
				GLchar attrName[maxNameSize];
				GLenum type;
				GLint size;
				GLsizei written;

				GLUniformBinding temp;
				glGetActiveUniform(mProgramID, index, maxNameSize, &written, &size, &type, attrName);

				if(written != 0 && strlen(attrName) != 0)
				{
					GLint location = glGetUniformLocation(mProgramID, attrName);
					if(location != -1)
					{
						binding = GLUniformBinding(attrName, type, index, location, size);
						return true;
					}
				}

			}
		}
		return false;
	}

	int OpenGLShaderProgram::getUniformLocation(const std::string &name)
	{
		return glGetUniformLocation(mProgramID, name.c_str());
	}

	int OpenGLShaderProgram::getAttributeLocation(const std::string &name)
	{
		return glGetAttribLocation(mProgramID, name.c_str());
	}

	void OpenGLShaderProgram::bindAttributeLocation(int index, const std::string &name)
	{
		glBindAttribLocation(mProgramID, index, name.c_str());
	}

	void OpenGLShaderProgram::setUniformMatrix3(FixedUniform key, const Matrix3 &data)
	{
		glUseProgram(mProgramID);

		if(sFixedUniforms[key].mType == GL_FLOAT_MAT3)
		{
			KeyUniformBindingMap::iterator i = mFixedActiveUniforms.find(key);
			if(i != mFixedActiveUniforms.end())
			{
				glUniformMatrix3fv((*i).second.mLocation, 1, false, glm::value_ptr(data));
			}
		}
	}

	void OpenGLShaderProgram::setUniformMatrix3(const std::string &name, const Matrix3 &data)
	{
		glUseProgram(mProgramID);

		NameUniformBindingMap::iterator i = mActiveUniformsByName.find(name);
		if(i != mActiveUniformsByName.end() && (*i).second.mType == GL_FLOAT_MAT3)
		{
			glUniformMatrix3fv((*i).second.mLocation, 1, false, glm::value_ptr(data));
		}
	}

	void OpenGLShaderProgram::setUniformMatrix4(FixedUniform key, const Matrix4 &data)
	{
		glUseProgram(mProgramID);

		if(sFixedUniforms[key].mType == GL_FLOAT_MAT4)
		{
			KeyUniformBindingMap::iterator i = mFixedActiveUniforms.find(key);
			if(i != mFixedActiveUniforms.end())
			{
				glUniformMatrix4fv((*i).second.mLocation, 1, false, glm::value_ptr(data));
			}
		}
	}

	void OpenGLShaderProgram::setUniformMatrix4(const std::string &name, const Matrix4 &data)
	{
		glUseProgram(mProgramID);

		NameUniformBindingMap::iterator i = mActiveUniformsByName.find(name);
		if(i != mActiveUniformsByName.end() && (*i).second.mType == GL_FLOAT_MAT4)
		{
			glUniformMatrix4fv((*i).second.mLocation, 1, false, glm::value_ptr(data));
		}
	}

	void OpenGLShaderProgram::setUniformVector4(FixedUniform key, const Vector4 &data)
	{
		glUseProgram(mProgramID);

		if(sFixedUniforms[key].mType == GL_FLOAT_VEC4)
		{
			KeyUniformBindingMap::iterator i = mFixedActiveUniforms.find(key);
			if(i != mFixedActiveUniforms.end())
			{
				glUniform4fv((*i).second.mLocation, 1, glm::value_ptr(data));
			}
		}
	}

	void OpenGLShaderProgram::setUniformVector4(const std::string &name, const Vector4 &data)
	{
		glUseProgram(mProgramID);

		NameUniformBindingMap::iterator i = mActiveUniformsByName.find(name);
		if(i != mActiveUniformsByName.end() && (*i).second.mType == GL_FLOAT_VEC4)
		{
			glUniform4fv((*i).second.mLocation, 1, glm::value_ptr(data));
		}
	}

	void OpenGLShaderProgram::setUniformVector3(FixedUniform key, const Vector3 &data)
	{
		glUseProgram(mProgramID);

		if(sFixedUniforms[key].mType == GL_FLOAT_VEC3)
		{
			KeyUniformBindingMap::iterator i = mFixedActiveUniforms.find(key);
			if(i != mFixedActiveUniforms.end())
			{
				glUniform3fv((*i).second.mLocation, 1, glm::value_ptr(data));
			}
		}
	}

	void OpenGLShaderProgram::setUniformVector3(const std::string &name, const Vector3 &data)
	{
		glUseProgram(mProgramID);

		NameUniformBindingMap::iterator i = mActiveUniformsByName.find(name);
		if(i != mActiveUniformsByName.end() && (*i).second.mType == GL_FLOAT_VEC3)
		{
			glUniform3fv((*i).second.mLocation, 1, glm::value_ptr(data));
		}
	}

	void OpenGLShaderProgram::setUniformFloat(FixedUniform key, float data)
	{
		glUseProgram(mProgramID);

		if(sFixedUniforms[key].mType == GL_FLOAT)
		{
			KeyUniformBindingMap::iterator i = mFixedActiveUniforms.find(key);
			if(i != mFixedActiveUniforms.end())
			{
				glUniform1f((*i).second.mLocation, data);
			}
		}
	}

	void OpenGLShaderProgram::setUniformFloat(const std::string &name, float data)
	{
		glUseProgram(mProgramID);

		NameUniformBindingMap::iterator i = mActiveUniformsByName.find(name);
		if(i != mActiveUniformsByName.end() && (*i).second.mType == GL_FLOAT)
		{
			glUniform1f((*i).second.mLocation, data);
		}
	}

} /* namespace raytracer */
