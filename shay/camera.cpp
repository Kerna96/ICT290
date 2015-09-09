//  camera.cpp
//
//  Implementation file for Camera Class
//  Defines all the methods declared, but not defined, in camera.h
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#include "Camera.h"
#include <math.h>
#include <gl/glut.h>

//--------------------------------------------------------------------------------------
// Set initial values
//--------------------------------------------------------------------------------------
Camera::Camera(){
	m_rotateSpeed = 0.0f;
	m_moveSpeed = 0.0f;

	ResetXYZ();

	m_deltaMoveFB = 0;
	m_deltaMoveLR = 0;
	m_deltaMoveUD = 0;

	m_rotateAngleLR = 0.0;
	m_rotateAngleUD = 0.0;
	m_deltaAngleLR = 0.0;
	m_deltaAngleUD = 0.0;

	// sound objects
	es = CEasySound::Instance();
	stepSound = es->GetSound(es->Load("sounds/step.wav"));
}

//--------------------------------------------------------------------------------------
// Reset camera values
//--------------------------------------------------------------------------------------
void Camera::ResetXYZ(){
	m_x = 0.0f;
	m_y = 1.75f;
	m_z = 0.0f;
	
	m_lookX = 0.0f;
	m_lookY = 0.0f;
	m_lookZ = -1.0f;
	
	m_lookXX = 1.0f;
	m_lookYY = 1.0f;
	m_lookZZ = 0.0f;
}

//--------------------------------------------------------------------------------------
//  Determine direction
//--------------------------------------------------------------------------------------
void Camera::DirectionFB(int const & tempMove){
	m_deltaMoveFB = tempMove;
}
//--------------------------------------------------------------------------------------
void Camera::DirectionLR(int const & tempMove){
	m_deltaMoveLR = tempMove;
}
//--------------------------------------------------------------------------------------
// Not used but allows up and down movement
void Camera::DirectionUD(int const & tempMove){
	m_deltaMoveUD = tempMove;
}

//--------------------------------------------------------------------------------------
void Camera::DirectionRotateLR(GLdouble const & tempMove){
	m_deltaAngleLR = tempMove * m_rotateSpeed;
}

//--------------------------------------------------------------------------------------
void Camera::DirectionLookUD(int const & tempMove){
	m_deltaAngleUD = tempMove * m_rotateSpeed;
}

void SetFOV(int FOV, float ratio){
	gluPerspective(FOV,ratio,0.000001,250000);
}

//--------------------------------------------------------------------------------------
// Move camera backwards and forwards
//--------------------------------------------------------------------------------------
void Camera::MoveFB(){
	// record previous co-ordinates
	m_xLast = m_x;
	m_zLast = m_z;

	// increment position
	m_z += (m_deltaMoveFB * (m_lookZ) * m_moveSpeed);
	m_x += (m_deltaMoveFB * (m_lookX) * m_moveSpeed);

	// redisplay
	callGLLookAt();
}

//--------------------------------------------------------------------------------------
// Move camera left and right (sideways)
//--------------------------------------------------------------------------------------
void Camera::MoveLR(){
	// record previous co-ordinates
	m_zLast = m_z;
	m_xLast = m_x;

	// increment position
	m_z += (m_deltaMoveLR * (m_lookZZ) * m_moveSpeed);
	m_x += (m_deltaMoveLR * (m_lookXX) * m_moveSpeed);

	// redisplay
	callGLLookAt();
}

//----------------------------------------------------------------------------------------
// Moves camera up and down (NOT USED)
//----------------------------------------------------------------------------------------
/*void Camera::MoveUD(){
	m_y += m_deltaMoveUD * (m_lookYY) * m_moveSpeed;
	callGLLookAt();
}*/

//----------------------------------------------------------------------------------------
// Rotates camera left and right
//----------------------------------------------------------------------------------------
void Camera::RotateLR(){
	m_rotateAngleLR += m_deltaAngleLR;
	m_lookX = sin(m_rotateAngleLR);
	m_lookZ = -cos(m_rotateAngleLR);
	m_lookXX = sin(m_rotateAngleLR + (float) PI/2.0);
	m_lookZZ = -cos(m_rotateAngleLR + (float) PI/2.0);
	callGLLookAt();
}

//----------------------------------------------------------------------------------------
//  Rotates camera up and down
//----------------------------------------------------------------------------------------
void Camera::LookUD(){
	m_rotateAngleUD += m_deltaAngleUD;
	
	m_lookY = sin(m_rotateAngleUD);
	if(m_lookY > 1.0){
		m_lookY = 1.0;
	}else if(m_lookY < 0.0){
		m_lookY = 0.0;
	}
	
	callGLLookAt();
}

//----------------------------------------------------------------------------------------
// Positions camera at co-ordinates of parameters
//----------------------------------------------------------------------------------------
void Camera::Position (GLdouble const & tempX, GLdouble const & tempY,
			           GLdouble const & tempZ, GLdouble const & tempAngle){
	ResetXYZ();
	
	m_x = tempX;
	m_y = tempY;
	m_z = tempZ;

	// rotate to correct angle
	m_rotateAngleLR = tempAngle * (PI / 180);
	m_lookX = sin(m_rotateAngleLR);
	m_lookZ = -cos(m_rotateAngleLR);
	m_lookXX = sin(m_rotateAngleLR + (float) PI/2.0);
	m_lookZZ = -cos(m_rotateAngleLR + (float) PI/2.0);
	m_rotateAngleUD = 0.0;
	m_deltaAngleUD = 0.0;
}

//----------------------------------------------------------------------------------------
//  Redisplay new camera view #LEAVE IN
//----------------------------------------------------------------------------------------
void Camera::callGLLookAt(){
	glLoadIdentity();
	gluLookAt(m_x, m_y, m_z, 
		      m_x + m_lookX, m_y + m_lookY, m_z + m_lookZ,
			  0.0f, 1.0f, 0.0f);
}

//--------------------------------------------------------------------------------------
// Display map of world
//----------------------------------------------------------------------------------------

/*void Camera::DisplayMap(const int & screenWidth, const int & screenHeight, 
		                const GLuint & tempImage){
	m_map.DisplayMap(screenWidth, screenHeight, GetLR (), GetFB (), tempImage);
}*/

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

/*void Camera::DisplayWelcomeScreen(const int & screenWidth, const int & screenHeight, 
		                const int & tempExit, const GLuint & tempImage){
	 m_map.DisplayWelcomeScreen(screenWidth, screenHeight, tempExit, tempImage);
}*/

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

/*void Camera::DisplayNoExit(const int & screenWidth, const int & screenHeight, 
		                   const GLuint & tempImage){
	 m_map.DisplayNoExit(screenWidth, screenHeight, tempImage);
}*/

//----------------------------------------------------------------------------------------

/*void Camera::SetWorldCoordinates (const GLdouble &tempX, const GLdouble &tempZ){
	m_colDetect.SetWorldX(tempX);
	m_colDetect.SetWorldZ(tempZ);
}*/
