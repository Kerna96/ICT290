//  camera.h
//  Header file for the camera class
//	Allows the camera to be navigated around the world. 
//	Also sets Plains, Bounding Boxes and view Maps
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.1415962654

#include "cameraMap.h"
#include "EasySound.h"

//--------------------------------------------------------------------------------------

class Camera
{
public:

	Camera();
	virtual ~Camera() {es->Unload(stepSound);}

	//----------------------------------------------------------------------------------
	
	//----------------------------------------------------------------------------------
	//  Set Methods
	//----------------------------------------------------------------------------------
	// set step and rotation size
	void SetRotateSpeed (const GLdouble &tempSpeed) {m_rotateSpeed = tempSpeed;}
	void SetMoveSpeed (const GLdouble &tempSpeed) {m_moveSpeed = tempSpeed;}
	void SetFOV (int FOV, float ratio);

	//----------------------------------------------------------------------------------
	//  Get Methods
	//----------------------------------------------------------------------------------
	//GLdouble GetLR () {return m_x;}
	//GLdouble GetUD () {return m_y;}
	//GLdouble GetFB () {return m_z;}	
	
	// position the camera, may need changing
	void Position (GLdouble const & tempX,
				   GLdouble const & tempY,
				   GLdouble const & tempZ,
				   GLdouble const & tempAngle);

	// check whether ok to move
	void CheckCamera();

	// Used to pass direction to move or rotate  (i.e. 1, -1 or 0)
	void DirectionFB(int const & tempMove);
	void DirectionLR(int const & tempMove);
	void DirectionUD(int const & tempMove);
	void DirectionRotateLR(GLdouble const & tempMove);
	void DirectionLookUD(int const & tempMove);

	// display map
	void DisplayMap(const int & screenWidth, const int & screenHeight, 
		            const GLuint & tempImage);
	// display welcome screen
	void DisplayWelcomeScreen (const int & screenWidth, const int & screenHeight,
							   const int & tempExit, const GLuint & tempImage);
	// display no exit
	void DisplayNoExit (const int & screenWidth, const int & screenHeight, 
						const GLuint & tempImage);
	
private:

	//steep incline increments
	GLdouble m_incrementX;
	GLdouble m_incrementZ;
	int m_No_Plains;
	int m_plainNo;
	GLdouble m_plainHeight;

	// rotation variables
	GLdouble m_rotateAngleLR;
	GLdouble m_deltaAngleLR;
	GLdouble m_rotateAngleUD;	
	GLdouble m_deltaAngleUD;

	// movement variables
	GLdouble m_x, m_y, m_z, m_zLast, m_xLast;
	GLdouble m_lookX, m_lookY,m_lookZ;
	GLdouble m_lookXX, m_lookYY, m_lookZZ;
	GLdouble m_deltaMoveLR;
	GLdouble m_deltaMoveFB;
	GLdouble m_deltaMoveUD;
	GLdouble m_direction;

	// movement speed (step size)
	GLdouble m_rotateSpeed;
	GLdouble m_moveSpeed;

	// move around the world
	void MoveFB();
	void MoveLR();
	void MoveUD();
	void RotateLR();
	void LookUD();

	// resets camera
	void ResetXYZ();
	// display new view #leave in
	void callGLLookAt();

	// objects
	CameraMap m_map;

	CEasySound *es;
	CSound* stepSound;

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    Camera (const Camera &cam) {};
    Camera &operator = (const Camera &cam) {};
};

#endif
