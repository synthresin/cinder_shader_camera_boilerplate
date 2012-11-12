#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicEarthApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    CameraPersp     mCam;
    gl::GlslProg    mShader;
    gl::Texture     mTex;
    Vec3f           mLightPosition;
    
    Vec3f mBrickColor, mMortarColor;
    Vec2f mBrickPct, mBrickSize;
};

void BasicEarthApp::setup()
{
    mCam.setPerspective(75.0f, getWindowAspectRatio(), 50.0f, 5000.0f);
    
    try {
        mShader = gl::GlslProg(loadResource("vert.glsl"),loadResource("frag.glsl"));
    } catch (gl::GlslNullProgramExc &exc) {
        std::cout << exc.what() << std::endl;
    } catch (...) {
        std::cout << "unknown error" << std::endl;
    }
    
    gl::Texture::Format format = gl::Texture::Format();
    format.setTarget(GL_TEXTURE_2D);
    format.setWrapS(GL_REPEAT);
    format.setWrapT(GL_REPEAT);
    format.setMagFilter(GL_LINEAR);
    format.setMinFilter(GL_LINEAR);
    mTex = gl::Texture( loadImage( loadResource("earth_tex.jpg") ), format );
    
    
    mLightPosition = Vec3f(0.0, 0.0,300.0f);
    
    // 벽돌 색깔 설정
    mBrickColor = Vec3f(0.6, 0.2, 0.3);
    mMortarColor = Vec3f(0.7, 0.7, 0.7);
    
    // 벽돌 사이즈 설정
    mBrickSize = Vec2f(10.0, 4.0);
    mBrickPct = Vec2f(0.9, 0.8);
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
    gl::setMatrices(mCam);
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mShader.bind();
    mShader.uniform("LightPosition", mLightPosition);
    mShader.uniform("BrickColor", mBrickColor);
    mShader.uniform("BrickPct", mBrickPct);
    mShader.uniform("BrickSize", mBrickSize);
    mShader.uniform("MortarColor", mMortarColor);
    gl::drawSphere(Vec3f::zero(), 100.0f);
    mShader.unbind();
    

    
    
}

CINDER_APP_BASIC( BasicEarthApp, RendererGl )
