#pragma once

#include "ofMain.h"
#include "extras.h"
#include "drawing_extras.h"
#include "cam_extras.h"
#include "materials.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();


		void skybox();
		void lights();
		void drawWorld();


		//camera variables
		int view;
		int orto;
		GLfloat lensAngle;
		GLfloat alpha, beta;

		ofVec3f camPos;
		ofVec3f lookatPos;
		ofVec3f camUp;


		//floor
		GLint resX, resY;
		GLfloat floorWidth, floorHeight;

		//base
		GLfloat baseWidth, baseHeight;
		

		float objectRotationAngle ;

		GLfloat elevatorPosition = 0.0;  
		GLfloat elevatorSpeed = 0.1;    
		GLint elevatorDirection = 1;     


		GLfloat elevatorPosition2 = 0.0;
		GLfloat elevatorSpeed2 = 0.1;
		GLint elevatorDirection2 = 1;

		float anglerotation_rodagigante;


		//luz
		bool ambientOn;
		bool dirOn;
		bool pointOn;
		bool spotOn;
		bool pointRoda1On;
		bool pointRoda2On;
		
		bool amb, dif, spec;//componentes

		bool autoMove;

		GLfloat ambientLight[4];

		GLfloat dirVec[4];
		GLfloat dirAmb[4];
		GLfloat dirDif[4];
		GLfloat dirSpec[4];
		ofVec3f dirVec3f;
		GLfloat dirVecTheta;


		GLfloat pointPos[4];
		GLfloat pointAmb[4];
		GLfloat pointDif[4];
		GLfloat pointSpec[4];
		GLfloat pointZtheta;
		GLfloat pointAtC, pointAtL, pointAtQ;
		GLfloat pointXtheta, pointYtheta;


		GLfloat pointRoda1Pos[4];
		GLfloat pointRoda1Amb[4];
		GLfloat pointRoda1Dif[4];
		GLfloat pointRoda1Spec[4];
		GLfloat pointRoda1AtC, pointRoda1AtL, pointRoda1AtQ;

		GLfloat pointRoda2Pos[4];
		GLfloat pointRoda2Amb[4];
		GLfloat pointRoda2Dif[4];
		GLfloat pointRoda2Spec[4];
		GLfloat pointRoda2AtC, pointRoda2AtL, pointRoda2AtQ;
		

		GLfloat spotPos[4];
		GLfloat spotDir[3];
		GLfloat spotAmb[4];
		GLfloat spotDif[4];
		GLfloat spotSpecular[4];
		GLfloat spotExponent;
		GLfloat spotCutoff;
		GLfloat spotTheta;
		GLfloat spotAtC, spotAtL, spotAtQ;


		//texturas
		ofImage img_glass;
		ofImage img_predio1;
		ofImage img_predio2;
		ofImage img_tijolos;
		ofImage img_chao;
		ofImage img_predio_noite;

		


		//skybox
		float rx, ry, rz;
		float phaseX;
		float phaseY;

		//procedural texture
		ofImage sky;
		ofFbo nightSky;
		ofImage nightSkyImg;
		unsigned char* skyPixels = NULL;
		int px, py, numPixels;




		
};
