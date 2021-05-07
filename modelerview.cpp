#if defined(__APPLE__)
#  include <OpenGL/gl3.h> // defines OpenGL 3.0+ functions
#else
#  if defined(WIN32)
#    define GLEW_STATIC 1
#  endif
#  include <GL/glew.h>
#endif

#include "modelerview.h"
#include "camera.h"
#include "bitmap.h"
#include "modelerapp.h"
#include "particleSystem.h"

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.h>
#include <FL/gl.h>
#include <GL/glu.h>
#include <cstdio>

static const int	kMouseRotationButton			= FL_LEFT_MOUSE;
static const int	kMouseTranslationButton			= FL_MIDDLE_MOUSE;
static const int	kMouseZoomButton				= FL_RIGHT_MOUSE;

static const char *bmp_name = NULL;

const std::string fragmentShader = R"(
void main()
{
	gl_FragColor = gl_Color;
}
)";
// https://blog.csdn.net/boksic/article/details/43834111 


const std::string vertexShader = R"(
void main()
{
vec3 normal, lightDir;
vec4 diffuse, ambient,globalAmbient,specular;
float NdotL;float NdotHV;

normal = normalize(gl_NormalMatrix * gl_Normal);
lightDir = normalize(vec3(gl_LightSource[0].position));
NdotL = max(dot(normal, lightDir), 0.0);
diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
/* Compute the ambient and globalAmbient terms */

ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

/* compute the specular term if NdotL is  larger than zero */
if (NdotL > 0.0) {
// normalize the half-vector, and then compute the
// cosine (dot product) with the normal
NdotHV = max(dot(normal, gl_LightSource[0].halfVector.xyz),0.0);
specular = gl_FrontMaterial.specular * gl_LightSource[0].specular *
pow(NdotHV,gl_FrontMaterial.shininess);}
gl_FrontColor = NdotL * diffuse + 0 + ambient +specular;
gl_Position = ftransform();
}
)";//https://blog.csdn.net/boksic/article/details/43834111


void printShaderLog(GLuint shader)
{
	GLint shaderState;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderState);
	if (shaderState == GL_TRUE)
	{
		return;
	}
	GLsizei bufferSize = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufferSize);
	if (bufferSize > 0)
	{
		GLchar* buffer = new char[bufferSize];
		glGetShaderInfoLog(shader, bufferSize, NULL, buffer);
		printf("%s", buffer);
		delete[] buffer;
	}
}
//https ://blog.csdn.net/u010223072/article/details/80641050

ModelerView::ModelerView(int x, int y, int w, int h, char *label)
: Fl_Gl_Window(x,y,w,h,label), t(0), save_bmp(false) 
{
	m_ctrl_camera = new Camera();
	m_curve_camera = new Camera();
	camera(CURVE_MODE);



}

ModelerView::~ModelerView()
{
	delete m_ctrl_camera;
	delete m_curve_camera;
}
int ModelerView::handle(int event)
{
    unsigned eventCoordX = Fl::event_x();
	unsigned eventCoordY = Fl::event_y();
	unsigned eventButton = Fl::event_button();
	unsigned eventState  = Fl::event_state();

	switch(event)	 
	{
	case FL_PUSH:
		{
			switch(eventButton)
			{
			case kMouseRotationButton:
				if (!Fl::event_state(FL_ALT)) {
					m_camera->clickMouse(kActionRotate, eventCoordX, eventCoordY );
					break;
				} // ALT + LEFT = MIDDLE
			case kMouseTranslationButton:
				m_camera->clickMouse(kActionTranslate, eventCoordX, eventCoordY );
				break;
			case kMouseZoomButton:
				m_camera->clickMouse(kActionZoom, eventCoordX, eventCoordY );
				break;
			}
           // printf("push %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	case FL_DRAG:
		{
			m_camera->dragMouse(eventCoordX, eventCoordY);
            //printf("drag %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	case FL_RELEASE:
		{
			switch(eventButton)
			{
			case kMouseRotationButton:
			case kMouseTranslationButton:
			case kMouseZoomButton:
				m_camera->releaseMouse(eventCoordX, eventCoordY );
				break;
			}
          //  printf("release %d %d\n", eventCoordX, eventCoordY);
		}
		break;
	default:
		return Fl_Gl_Window::handle(event);
	}
	
	redraw();

	return 1;
}

static GLfloat lightPosition0[] = { 4, 2, -4, 0 };
static GLfloat lightDiffuse0[]  = { 1,1,1,1 };
static GLfloat lightPosition1[] = { -2, 1, 5, 0 };
static GLfloat lightDiffuse1[]  = { 1, 1, 1, 1 };

GLuint FshaderID;
GLuint VshaderID;
GLuint programID;

void ModelerView::draw()
{

    if (!valid())
    {
        glShadeModel( GL_SMOOTH );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
        glEnable( GL_LIGHT1 );
		glEnable( GL_NORMALIZE );

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;

		}
		std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
		
		const char* Fshaders = fragmentShader.c_str();
		const char* Vshaders = vertexShader.c_str();

		FshaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FshaderID, 1, &Fshaders, NULL);
		glCompileShader(FshaderID);
		cout<<"frag info"<<endl;
		printShaderLog(FshaderID);

		VshaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VshaderID, 1, &Vshaders, NULL);
		glCompileShader(VshaderID);
		cout << "Vert info" << endl;

		printShaderLog(VshaderID);


		 programID = glCreateProgram();
		glAttachShader(programID, FshaderID);
		glAttachShader(programID, VshaderID);
		glLinkProgram(programID);
		glUseProgram(programID);
    }

  	glViewport( 0, 0, w(), h() );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,float(w())/float(h()),1.0,100.0);
				
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_camera->applyViewingTransform();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse0 );
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse1 );
	glUniform1fv(glGetAttribLocation(programID, "lightPos"),3, lightPosition0);


	// If particle system exists, draw it
	ParticleSystem *ps = ModelerApplication::Instance()->GetParticleSystem();
	if (ps != NULL) {
		ps->computeForcesAndUpdateParticles(t);
		ps->drawParticles(t);
	}
}


/** Set the active camera **/
void ModelerView::camera(cam_mode_t mode)
{
	switch (mode) {
	case CTRL_MODE:
		m_camera = m_ctrl_camera;
		break;
	case CURVE_MODE:
		m_camera = m_curve_camera;
		break;
	}
}


/** Cleanup fxn for saving bitmaps **/
void ModelerView::endDraw()
{
	if ((bmp_name == NULL) || (!save_bmp)) return;
	glFinish();
	saveBMP(bmp_name);
	save_bmp = false;
}


void ModelerView::setBMP(const char *fname)
{
	save_bmp = true;
	bmp_name = fname;
}

void ModelerView::saveBMP(const char* szFileName)
{
	int xx = x();
	int yy = y();
	int ww = w();
	int hh = h();
	
	make_current();
	
	unsigned char *imageBuffer = new unsigned char[3 * ww * hh];
	
	glReadBuffer(GL_BACK);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, ww);
    
    glReadPixels( 0, 0, ww, hh, 
		GL_RGB, GL_UNSIGNED_BYTE, 
		imageBuffer );
	
	writeBMP(szFileName, ww, hh, imageBuffer);
	
	delete [] imageBuffer;
}

