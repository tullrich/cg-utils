#include "rendersystem/opengl/OpenGLRenderSystem.h"

namespace raytracer {

	using namespace CEGUI;
	int myData = 0;


	void DebugLog (GLenum source , GLenum type , GLuint id , GLenum severity , GLsizei length , const GLchar * message , GLvoid * userParam)
	{
		printf (" Message : %s\n", message );
	}
	
	OpenGLRenderSystem::OpenGLRenderSystem()
	{

	}

	Window* OpenGLRenderSystem::initialise(const string &windowTitle)
	{
		Window *win = RenderSystem::initialise(windowTitle);
		glewInit();

		if(GLEW_ARB_debug_output)
		{
			std::cout << "GL_ARB_debug_output found" << std::endl;
			glDebugMessageCallbackARB( DebugLog , & myData );
			std::cout << "GL_ARB_debug_output found" << std::endl;
		}
		//glEnable(GL_UNIFORM_BUFFER);
		//glShadeModel( GL_SMOOTH );
	    /* Set the background black */
	    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	    /* Depth buffer setup */
	    glClearDepth( 1.0f );
	    /* Enables Depth Testing */
	    glEnable( GL_DEPTH_TEST );
	    /* Enables culling */
	    glEnable( GL_CULL_FACE );
	    glCullFace( GL_BACK );
	    /* The Type Of Depth Test To Do */

	    glEnable(GL_BLEND);
	    glDepthFunc( GL_LEQUAL );
	    glEnable(GL_DITHER);
	    glEnable(GL_MULTISAMPLE_ARB);
	    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	    glEnable(GL_LINE_SMOOTH);
	    glEnable(GL_POLYGON_SMOOTH);
	    glEnable(GL_POINT_SMOOTH);
	   //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	    //float sampleCoverageValue = -1.0f;
	    //glSampleCoverage(1.0f, GL_TRUE);
   		//glEnable(GL_SAMPLE_COVERAGE);
	    //glGetFloatv(GL_SAMPLE_COVERAGE_VALUE, &sampleCoverageValue);
	    //std::cout << "GL_SAMPLE_COVERAGE_VALUE: " << sampleCoverageValue << std::endl;
	    //int sampleBuffers = -1;
	    //glGetIntegerv(GL_SAMPLE_BUFFERS, &sampleBuffers);
	    //std::cout << "GL_SAMPLE_BUFFERS: " << sampleBuffers << std::endl;
	    //int maxSamples = -1;
	    //glGetIntegerv(GL_SAMPLES, &maxSamples);
	    //std::cout << "GL_SAMPLES: " << maxSamples << std::endl;

	    OpenGLLowLevelShader *vertexShader = new OpenGLLowLevelShader(OpenGLLowLevelShader::GPU_VERTEX_SHADER, "test_vs.vert");
		OpenGLLowLevelShader *fragShader = new  OpenGLLowLevelShader(OpenGLLowLevelShader::GPU_FRAGMENT_SHADER, "test_fs.frag");
		OpenGLLowLevelShader *geoShader = new  OpenGLLowLevelShader(OpenGLLowLevelShader::GPU_GEOMETRY_SHADER, "test_gs.geo");
		mDefaultProgram = new OpenGLShaderProgram();
		mDefaultProgram->attach(*vertexShader);
		mDefaultProgram->attach(*fragShader);
		mDefaultProgram->attach(*geoShader);
		mDefaultProgram->link();

		if(!mDefaultProgram->isBad())
		{
			mDefaultProgram->activate();
		}
		else
		{
			std::cout << "COULD NOT LINK" << std::endl; 
			delete win;
			win = NULL;
			return NULL;
		}

		initCEGUI();
	    return win;
	}

	void OpenGLRenderSystem::initCEGUI()
	{
		CEGUI::OpenGL3Renderer& myRenderer = CEGUI::OpenGL3Renderer::bootstrapSystem();

		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
    		(CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("schemes", "/home/tim/workspace/cegui-0.8.2/datafiles/schemes/");
		rp->setResourceGroupDirectory("imagesets", "/home/tim/workspace/cegui-0.8.2/datafiles/imagesets/");
		rp->setResourceGroupDirectory("fonts", "/home/tim/workspace/cegui-0.8.2/datafiles/fonts/");
		rp->setResourceGroupDirectory("layouts", "/home/tim/workspace/cegui-0.8.2/datafiles/layouts/");
		rp->setResourceGroupDirectory("looknfeels", "/home/tim/workspace/cegui-0.8.2/datafiles/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", "/home/tim/workspace/cegui-0.8.2/datafiles/lua_scripts/");

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

		CEGUI::SchemeManager::getSingleton().createFromFile( "TaharezLook.scheme" );
		WindowManager& wmgr = WindowManager::getSingleton();
		CEGUI::Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
		System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
		FrameWindow* fWnd = static_cast<FrameWindow*>(
   			wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));
		myRoot->addChild( fWnd );

		// position a quarter of the way in from the top-left of parent.
		fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );
		// set size to be half the size of the parent
		fWnd->setWidth( UDim( 0.5f, 0 ));
		fWnd->setHeight( UDim( 0.5f, 0 ) );
		fWnd->setText( "Hello World!" );

		PushButton* btnClose = static_cast<PushButton*>(wmgr.createWindow("TaharezLook/Button", "Button"));
		btnClose->setText("Exit");
		fWnd->addChild( btnClose );
	}

	HardwareBufferManager* OpenGLRenderSystem::initaliseHWBufManager()
	{
		return &OpenGLHardwareBufferManager::getInstance();
	}


	void OpenGLRenderSystem::render(const RenderOperation &op)
	{
		OpenGLHardwareBuffer *vertex_glhwb = static_cast<OpenGLHardwareBuffer*>(op.mVertexData);
		OpenGLHardwareBuffer *index_glhwb = static_cast<OpenGLHardwareBuffer*>(op.mIndexData);
		OpenGLHardwareBuffer *uv_glhwb = static_cast<OpenGLHardwareBuffer*>(op.mUVData);
		OpenGLHardwareBuffer *normal_glhwb = static_cast<OpenGLHardwareBuffer*>(op.mNormalData);
		

		// vertices
		glBindBuffer(GL_ARRAY_BUFFER, vertex_glhwb->getBufferID());
		glVertexAttribPointer(FixedAttribute::FA_VERTICES, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glEnableVertexAttribArray(FixedAttribute::FA_VERTICES);

		// tex coords 
		if(uv_glhwb)
		{
			glBindBuffer(GL_ARRAY_BUFFER, uv_glhwb->getBufferID());
			glVertexAttribPointer(FixedAttribute::FA_TEX_COORDS_0, 2, GL_FLOAT, GL_TRUE, 0, 0);
			glEnableVertexAttribArray(FixedAttribute::FA_TEX_COORDS_0);
		}		

		// normals 
		if(normal_glhwb)
		{
			glBindBuffer(GL_ARRAY_BUFFER, normal_glhwb->getBufferID());
			glVertexAttribPointer(FixedAttribute::FA_NORMALS, 3, GL_FLOAT, GL_TRUE, 0, 0);
			glEnableVertexAttribArray(FixedAttribute::FA_NORMALS);
		}

		GLenum nativePrimitiveType;
		switch(op.mType)
		{
			case RenderOperation::PT_TRIANGLE_LIST:
				nativePrimitiveType = GL_TRIANGLES;
				break;
			case RenderOperation::PT_LINE_LIST:
				nativePrimitiveType = GL_LINES;
				break;
			default:
				nativePrimitiveType = GL_POINTS;
				break;
		}

		if(index_glhwb)
		{
			/* indices */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_glhwb->getBufferID());
			glDrawElements(nativePrimitiveType, index_glhwb->getNumElements() * 3, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(nativePrimitiveType, 0, vertex_glhwb->getNumElements());
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(FixedAttribute::FA_VERTICES);
		glDisableVertexAttribArray(FixedAttribute::FA_TEX_COORDS_0);
		glDisableVertexAttribArray(FixedAttribute::FA_NORMALS);

		GLenum glErr = glGetError();
        if(glErr != GL_NO_ERROR)
        {
        	//std::cout << "some gl error" << std::endl; 
        }
	}

	void OpenGLRenderSystem::clearImpl(const RGBA &color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
    	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void OpenGLRenderSystem::uploadModelViewProj()
	{
    	mDefaultProgram->setUniformMatrix4(FU_ModelViewProjection, mModelViewProjectionMatrix);
    	mDefaultProgram->setUniformMatrix4(FU_ModelView, mModelViewMatrix);
    	mDefaultProgram->setUniformMatrix3(FU_NormalMatrix
    		, glm::transpose(glm::inverse(Matrix3(mModelViewMatrix))));
    	mDefaultProgram->setUniformMatrix4(FU_InverseViewProjection, glm::inverse(mProjectionViewMatrix));
	}

	void OpenGLRenderSystem::setTexture(int unit, bool enabled, const Texture *t)
	{
		OpenGLTexture *GLt = (OpenGLTexture*) t;

		if(enabled && t)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			mLastTexUnitBindings[unit] = GLt->getTarget();
			GLt->bind();
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(mLastTexUnitBindings[unit], 0);
		}
	}


	void OpenGLRenderSystem::setParameterVector3(FixedUniform attr, const Vector3 &value)
	{
		mDefaultProgram->setUniformVector3(attr, value);
	}

	void OpenGLRenderSystem::setParameterVector4(FixedUniform attr, const Vector4 &value)
	{
		mDefaultProgram->setUniformVector4(attr, value);
	}


	void OpenGLRenderSystem::setParameterFloat(FixedUniform attr, float value)
	{
		mDefaultProgram->setUniformFloat(attr, value);
	}


	void OpenGLRenderSystem::setLight(int unit, bool enabled, const Light *t)
	{
		if(enabled)
		{
			mDefaultProgram->setUniformVector3("uLightSources.ambient", t->getAmbient());
			mDefaultProgram->setUniformVector3("uLightSources.diffuse", t->getDiffuse());
			mDefaultProgram->setUniformVector3("uLightSources.specular", t->getSpecular());
			mDefaultProgram->setUniformVector3("uLightSources.position", Vector3(mViewMatrix * t->getPosition()));
		}
		else
		{

		}
	}

	void OpenGLRenderSystem::renderGUI()
	{
		setTexture(1, false, NULL);
		setTexture(2, false, NULL);
		setTexture(3, false, NULL);
		setTexture(4, false, NULL);
		setTexture(5, false, NULL);
		setTexture(6, false, NULL);
		setTexture(7, false, NULL);		
		setTexture(0, false, NULL);

		glUseProgram(0);
		glActiveTexture(0);
		CEGUI::System::getSingleton().renderAllGUIContexts();
		glBindVertexArray(0); // not cleaned up by CEGUI
		mDefaultProgram->activate();
	}


} /* namespace raytracer */
