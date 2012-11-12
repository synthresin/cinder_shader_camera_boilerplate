#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicEarthApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    CameraPersp mCam;
    gl::GlslProg mShader;
};

void BasicEarthApp::setup()
{
    mCam.setPerspective(75.0f, getWindowAspectRatio(), 50.0f, 5000.0f);
    
    try {
        mShader = gl::GlslProg("vert.glsl","frag.glsl");
    } catch (gl::GlslNullProgramExc &exc) {
        std::cout << exc.what() << std::endl;
    } catch (...) {
        std::cout << "unknown error" << std::endl;
    }
}

void BasicEarthApp::mouseDown( MouseEvent event )
{
}

void BasicEarthApp::update()
{
    mCam.lookAt(Vec3f(0.0, 0.0, 500.0f), Vec3f::zero(), Vec3f::yAxis());
    
    
}

void BasicEarthApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::setMatrices(mCam);
    
    gl::drawSphere(Vec3f::zero(), 50.0f);
    
    
}

CINDER_APP_BASIC( BasicEarthApp, RendererGl )
