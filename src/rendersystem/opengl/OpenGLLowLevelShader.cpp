#include "rendersystem/opengl/OpenGLLowLevelShader.h"
#include <fstream>
#include <sstream>

namespace raytracer {
	
	OpenGLLowLevelShader::OpenGLLowLevelShader(HardwareShaderType type, const std::string &filePath) 
		: mType(type), mShaderID(0), mFilePath(filePath), mIsCompiled(false), mIsBad(false)
	{
		GLenum shadertype;
		switch(type)
		{
			case GPU_VERTEX_SHADER: shadertype = GL_VERTEX_SHADER; break;
			case GPU_FRAGMENT_SHADER: shadertype = GL_FRAGMENT_SHADER; break;
			case GPU_GEOMETRY_SHADER: shadertype = GL_GEOMETRY_SHADER; break;
		}
		mShaderID = glCreateShader(shadertype);

		if(mShaderID == 0)
		{
			std::cout << "Error in OpenGLLowLevelShader() with glCreateShader" << std::endl;
			mIsBad = true;
		}
	}

	bool OpenGLLowLevelShader::readSourceFile()
	{
		std::ifstream stream(mFilePath);

		if(stream.good())
		{
			std::stringbuf sb;
			stream.get(sb, EOF);
			mSource = sb.str();
			return true;
		}

		return false;
	}

	void OpenGLLowLevelShader::loadSource()
	{
		if(mIsBad || mIsCompiled)
			return; // already tried

		if(mShaderID == 0)
		{
			std::cout << "error in OpenGLLowLevelShader::loadSource, no shader handle" << std::endl; 
			return;
		}

		if(!readSourceFile())
		{
			std::cout << "error in OpenGLLowLevelShader::loadSource, could not read shader "<< mFilePath << std::endl; 
			return;
		}

		const char* mSource_cstr = mSource.c_str();
		glShaderSource(mShaderID, 1, &mSource_cstr, NULL); // assumed null terminated

		glCompileShader(mShaderID);

		GLint errorstatus = GL_FALSE;
		glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &errorstatus);
		if(errorstatus != GL_TRUE)
		{
			std::cout << "error in OpenGLLowLevelShader::loadSource could not compile shader" << std::endl;
			logShaderInfo();
			mIsBad = true;
			return;
		}

		mIsCompiled = true;
	}

	void OpenGLLowLevelShader::logShaderInfo()
	{
		GLint logSize = 0;
		glGetShaderiv(mShaderID, GL_INFO_LOG_LENGTH, &logSize);

		if(logSize != 0)
		{
			GLsizei sizei = logSize;
			GLchar msg[logSize];
			glGetShaderInfoLog(mShaderID, sizei, NULL, msg);

			std::cout << "'" << mFilePath << "' at " << msg << std::endl; 
		}
	}

	OpenGLLowLevelShader::~OpenGLLowLevelShader()
	{
		glDeleteShader(mShaderID); // 0 silently ignored
	}

} /* namespace raytracer */
