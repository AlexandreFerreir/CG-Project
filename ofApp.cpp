#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex(); //para utilizar coordenadas de textura normalizadas
	ofBackground(0); //define a cor do fundo da tela
	ofSetFrameRate(60);

	//habilita o teste de profundidade.
	//isto força com que o desenho final não seja feito pela em que a geometria é chamada,
	//mas sim pela sua posição no eixo z
	glEnable(GL_DEPTH_TEST);

	resX =15;
	resY = 10;
	floorWidth = gw()*2.5;
	floorHeight = gw();
	lensAngle = 120;
	alpha = 10;
	beta = 1000;
	view = 0;
	orto = 0;
	objectRotationAngle = 0.0f;
	baseWidth = floorWidth / GLfloat(resX);
	baseHeight = floorHeight / GLfloat(resY);
	elevatorPosition = 0.0;  // Altura inicial do elevador
	elevatorSpeed = 1.;    // Velocidade de movimento do elevador
	elevatorDirection = 1; // 1 para subir, -1 para descer
	elevatorPosition2 = 0.0;  // Altura inicial do elevador
	elevatorSpeed2 = 1.;    // Velocidade de movimento do elevador
	elevatorDirection2 = 1; // 1 para subir, -1 para descer
	anglerotation_rodagigante = 0;


	ambientOn = false;
	dirOn = false;
	pointOn = false;
	spotOn = false;
	autoMove = false;
	pointRoda1On = false;
	pointRoda2On = false;

	amb = false;
	dif = false;
	spec = false;

	spotExponent = 0;
	spotCutoff = 1;
	spotTheta = 0;

	img_glass.load("glass.jpg");
	img_predio1.load("manicomio.jpeg");
	img_predio2.load("predio_depressao.jpg");
	img_tijolos.load("tijolos_burro.jpg");
	img_chao.load("chao.jpg");
	img_predio_noite.load("predio_noite.jpeg");

	
	//skybox

	//para criar texturas procedurais é "desenhar" num buffer
	//e depois converter o resultado deste desenho numa imagem
	nightSky.allocate(gw(), gh(), GL_RGBA);
	nightSky.begin();//inicia o desenho no frame buffer
	ofClear(0, 0, 0, 255);//limpa
	nightSky.end();//finaliza o desenho no buffer
	//aloca uma imagem vazia com o tamanho do frame buffer para utilização como textura
	nightSkyImg.allocate(gw(), gh(), OF_IMAGE_COLOR_ALPHA);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_SMOOTH);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, true);

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));


	anglerotation_rodagigante += 0.5;
	elevatorPosition += elevatorDirection * elevatorSpeed;
	elevatorPosition2 += elevatorDirection2 * elevatorSpeed2;

	
	if (autoMove) {
		pointPos[0] = gw() * 0.5 * sin(pointXtheta * PI / 180.0);
		pointPos[1] = gh() * 0.5 * cos(pointYtheta * PI / 180.0);
		pointPos[2] =  200;

		pointXtheta += 0.75;
		pointYtheta += 0.75;

	
		//calculo da direcao da luz direcional
		float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);
		float y = -gh() * 0.5;
		float x = 0;
		dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);
		dirVecTheta += 0.5;

		//calculo da direcao do spot
		spotDir[0] = cos(spotTheta * PI / 180.);
		spotDir[1] = sin(spotTheta * PI / 180.);
		spotTheta += 0.75;


	}else {
		//luz pontual
		pointPos[0] = 0;
		pointPos[1] = 0;
		pointPos[2] = 90;
		
		//luz direcional
		dirVec3f = ofVec3f(0, -gh() * 0.5, gh() * 0.25 * 0.95) - ofVec3f(0, 0, 0);
		
		//spot
		spotDir[0] = 0;
		spotDir[1] = 0;
	}


}

//--------------------------------------------------------------
void ofApp::draw(){
	glViewport(0, 0, gw(), gh());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (orto) {
		glOrtho(-3000, 3000, -3000, 3000, -5000, 5000);
	}
	else{
		perspective(lensAngle, alpha, beta);
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	switch (view) {
	case 0:
		//vista panoramica
		lookat(0, -gh()*1.5, gw()*0.6, 0, 0, 0, 0, 1, 0);
		break;
	case 1:
		//vista de frente
		lookat(0, -gh()*2, 0, 0, 0, 0, 0, 0, 1);
		break;
	case 2:
		// Vista de topo
		lookat(0, 0, gw()*1.2, 0, 0, 0, 0, 1, 0);
		break;

	case 3:
		// Vista fora mundo
		lookat(0, 0, gw() * 7, 0, 0, 0, 0, 1, 0);
		break;

	}

	//rotacao mundo
	glRotatef(objectRotationAngle, 0, 0, 1);

	

	////glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_LIGHTING);//habilita o uso de iluminação
	glEnable(GL_NORMALIZE);//utiliza versores para normais (normais normalizadas)
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); //configuração consegue evidenciar melhor os efeitos especulares.
	//glEnable(GL_COLOR_MATERIAL);
	

	//#################################################

	lights();
	drawWorld();

	//#################################################
	//desenha representação das luzes e vetores utilizados
	//sem iluminação
	glDisable(GL_LIGHTING);//desabilita iluminação
	//representação da posição da Light1
	if (pointOn) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(pointPos[0], pointPos[1], pointPos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}
	//representação da posição da Light0
	if (dirOn) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(dirVec3f.x, dirVec3f.y, dirVec3f.z);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(dirVec3f.x, dirVec3f.y, dirVec3f.z);
		glEnd();
		glPopMatrix();
	}
	//representação da posição da luz spot
	if (spotOn) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(spotPos[0], spotPos[1], spotPos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}
	if (pointRoda1On) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(pointRoda1Pos[0], pointRoda1Pos[1], pointRoda1Pos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}
	if (pointRoda2On) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(pointRoda2Pos[0], pointRoda2Pos[1], pointRoda2Pos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}

	skybox();



}

void ofApp::drawWorld(){

	glPushMatrix();


	loadMaterial(2); //obsidian
	img_chao.bind();

	//floor
	glPushMatrix();//floor push
	glScalef(floorWidth, floorHeight, 1.);

	malha_unit_with_textures(resX, resY,8);
	glPopMatrix();//floor pop

	img_chao.unbind();



	//predio cubo
	loadMaterial(16); //bronze
	img_predio2.bind();

	glPushMatrix();
	glTranslatef(baseWidth * 6, baseHeight * 3.5, 500);
	glScalef(baseWidth, baseHeight, 1000);
	/*cube_unit_with_textures(baseWidth * 0.75, 280);*/
	cube_unit_with_textures(1, 1);
	glPopMatrix();

	img_predio2.unbind();



	//suporte elevador panoramico

	loadMaterial(11); //silver
	glPushMatrix();
	glTranslatef(baseWidth * 3.65, baseHeight * 4.5, 800);
	glScalef(baseWidth * 0.25, baseHeight * 0.25, 1600);
	cube_unit();
	glPopMatrix();

	if (elevatorPosition2 > 1500) {
		elevatorDirection2 = -1;
	}
	else if (elevatorPosition2 < 100) {
		elevatorDirection2 = 1;
	}

	//elevador panoramico

	glPushMatrix();
	glTranslatef(baseWidth * 3.65, baseHeight * 4.5, elevatorPosition2);
	glScalef(baseWidth * 0.20, baseHeight * 0.20, 200);
	cube_unit();
	glPopMatrix();


	loadMaterial(2); //obsidian
	//predio malha com elevador panoramico

	img_predio_noite.bind();

	glPushMatrix();
	glTranslatef(baseWidth, baseHeight * 4.5, 800);
	glScalef(baseWidth * 5, baseHeight, 1600);
	cube_malha_unit_with_textures(10, 10, 2);
	glPopMatrix();

	img_predio_noite.unbind();



	//predio cubo malha

	loadMaterial(8); //copper
	img_tijolos.bind();

	glPushMatrix();
	glTranslatef(baseWidth * 5, baseHeight * 0.5, 200);
	glScalef(baseWidth, baseHeight, 400);
	cube_malha_unit_with_textures(4, 4, 2);
	glPopMatrix();

	img_tijolos.unbind();



	//predio cubo malha com elevador interior
	loadMaterial(16); //whitePlastic

	img_predio1.bind();

	glPushMatrix();
	glTranslatef(-baseWidth * 6, baseHeight * 0.5, 500);
	glScalef(baseWidth, baseHeight, 1000);
	cube_malha_unit_with_textures(4, 4, 1);
	glPopMatrix();

	img_predio1.unbind();


	if (elevatorPosition > 900) {
		elevatorDirection = -1;
	}
	else if (elevatorPosition < 100) {
		elevatorDirection = 1;
	}
	//elevador

	glPushMatrix();
	glTranslatef(-baseWidth * 6, baseHeight * 0.5, elevatorPosition);
	glScalef(baseWidth * 0.25, baseHeight * 0.25, 200);
	cube_malha_unit(4, 4);
	glPopMatrix();



	//predio piramide

	loadMaterial(5); //turquoise
	img_glass.bind();

	glPushMatrix();
	glTranslatef(baseWidth * 4, -baseHeight * 3.5, 300);
	glScalef(baseWidth * 3, baseHeight * 3, 600);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	pyramid_unit_with_textures();
	glPopMatrix();

	img_glass.unbind();
	


	//roda gigante

	loadMaterial(17); //yellowPlastic

	glPushMatrix();
	glTranslatef(-baseWidth * 0.5, baseHeight * 0.5, baseWidth * 3);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(anglerotation_rodagigante, 0.0f, 0.0f, 1.0f);
	glScalef(baseWidth * 0.18, baseWidth * 0.18, baseWidth * 0.18);
	rodaGigante(0, 0, 0, baseWidth * 0.05, baseWidth * 0.005, 6);
	glPopMatrix();


	//suportes roda gigante

	loadMaterial(4); //ruby

	glPushMatrix();
	glTranslatef(-baseWidth * 0.5, baseHeight * 2, baseWidth * 1.5);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(baseWidth, baseWidth * 3, baseWidth * 0.5);
	triangular_prism_unit();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-baseWidth * 0.5, -baseHeight * 0.5, baseWidth * 1.5);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(baseWidth, baseWidth * 3, baseWidth * 0.5);
	triangular_prism_unit();
	glPopMatrix();

	//drawLine(-baseWidth * 0.5, baseHeight * 2, baseWidth * 3, -baseWidth * 0.5, -baseHeight * 0.5, baseWidth * 3);
	ofDrawCylinder(-baseWidth * 0.5, baseWidth *0.45, baseWidth * 3, 20, 900);


	glPopMatrix();//global
}


void ofApp::lights() {
	//#################################################
	//define luzes
	//#################################################
	//fonte de luz que só tem componente ambiente
	//não conta como uma fonte de luz LIGHT0 - LIGHT8
	if (ambientOn) {
		ambientLight[0] = 1;//R
		ambientLight[1] = 1;//G
		ambientLight[2] = 1;//B
		ambientLight[3] = 1;//useless
	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//#################################################


	//#################################################
	//luz direcional
	dirVec[0] = dirVec3f.x;//x
	dirVec[1] = dirVec3f.y;//y
	dirVec[2] = dirVec3f.z;//z
	dirVec[3] = 0;//vetor - direção!

	if (amb) {
		dirAmb[0] = 1;//R
		dirAmb[1] = 1;//G
		dirAmb[2] = 1;//B
		dirAmb[3] = 1.;//constante
	}
	else {
		dirAmb[0] = 0;//R
		dirAmb[1] = 0;//G
		dirAmb[2] = 0;//B
		dirAmb[3] = 1.;//constante
	}
	
	if(dif){
		dirDif[0] = 1;//R
		dirDif[1] = 1;//G
		dirDif[2] = 1;//B
		dirDif[3] = 1.;//constante
	}
	else {
		dirDif[0] = 0;//R
		dirDif[1] = 0;//G
		dirDif[2] = 0;//B
		dirDif[3] = 1.;//constante
	}

	if(spec){
		dirSpec[0] = 1.;//R
		dirSpec[1] = 1.;//G
		dirSpec[2] = 1.;//B
		dirSpec[3] = 1.;//constante
	}else {
		dirSpec[0] = 0;//R
		dirSpec[1] = 0;//G
		dirSpec[2] = 0;//B
		dirSpec[3] = 1.;//constante
	}
	

	glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);
	if (dirOn) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	//#################################################

	//#################################################
	//luz pontual
	
	pointPos[3] = 1;//ponto - posição!


	if (amb) {
		pointAmb[0] = 1.;//R
		pointAmb[1] = 1.;//G
		pointAmb[2] = 1.;//B
		pointAmb[3] = 1.;//constante
	}
	else {
		pointAmb[0] = 0;//R
		pointAmb[1] = 0;//G
		pointAmb[2] = 0;//B
		pointAmb[3] = 1.;//constante
	}

	if (dif) {
		pointDif[0] = 1.;//R
		pointDif[1] = 1.;//G
		pointDif[2] = 1.;//B
		pointDif[3] = 1.;//constante
	}
	else {
		pointDif[0] = 0;//R
		pointDif[1] = 0;//G
		pointDif[2] = 0;//B
		pointDif[3] = 1.;//constante
	}

	if (spec) {
		pointSpec[0] = 1.;//R
		pointSpec[1] = 1.;//G
		pointSpec[2] = 1.;//B
		pointSpec[3] = 1.;//constante
	}
	else {
		pointSpec[0] = 0;//R
		pointSpec[1] = 0;//G
		pointSpec[2] = 0;//B
		pointSpec[3] = 1.;//constante
	}
	
	glLightfv(GL_LIGHT1, GL_POSITION, pointPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);


	//atenuação
	
	pointAtC = 1;
	pointAtL = 0.0001;
	pointAtQ = 0.00001;
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, pointAtC);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, pointAtL);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, pointAtQ);


	if (pointOn) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}


	//#################################################
	//luz pontual Roda 1

	
	//posicao
	pointRoda1Pos[0] = -baseWidth * 0.5;
	pointRoda1Pos[1] = baseHeight * 2.55;
	pointRoda1Pos[2] = baseWidth * 3;
	pointRoda1Pos[3] = 1;//ponto - posição!


	if (amb) {
		pointRoda1Amb[0] = 1.;//R
		pointRoda1Amb[1] = 1.;//G
		pointRoda1Amb[2] = 1.;//B
		pointRoda1Amb[3] = 1.;//constante
	}
	else {
		pointRoda1Amb[0] = 0;//R
		pointRoda1Amb[1] = 0;//G
		pointRoda1Amb[2] = 0;//B
		pointRoda1Amb[3] = 1.;//constante
	}

	if (dif) {
		pointRoda1Dif[0] = 1.;//R
		pointRoda1Dif[1] = 1.;//G
		pointRoda1Dif[2] = 1.;//B
		pointRoda1Dif[3] = 1.;//constante
	}
	else {
		pointRoda1Dif[0] = 0;//R
		pointRoda1Dif[1] = 0;//G
		pointRoda1Dif[2] = 0;//B
		pointRoda1Dif[3] = 1.;//constante
	}

	if (spec) {
		pointRoda1Spec[0] = 1.;//R
		pointRoda1Spec[1] = 1.;//G
		pointRoda1Spec[2] = 1.;//B
		pointRoda1Spec[3] = 1.;//constante
	}
	else {
		pointRoda1Spec[0] = 0;//R
		pointRoda1Spec[1] = 0;//G
		pointRoda1Spec[2] = 0;//B
		pointRoda1Spec[3] = 1.;//constante
	}

	glLightfv(GL_LIGHT3, GL_POSITION, pointRoda1Pos);
	glLightfv(GL_LIGHT3, GL_AMBIENT, pointRoda1Amb);
	glLightfv(GL_LIGHT3, GL_SPECULAR, pointRoda1Spec);

	//atenuação

	pointRoda1AtC = 0.2;
	pointRoda1AtL = 0.0001;
	pointRoda1AtQ = 0.00001;

	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, pointRoda1AtC);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, pointRoda1AtL);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, pointRoda1AtQ);


	if (pointRoda1On) {
		glEnable(GL_LIGHT3);
	}
	else {
		glDisable(GL_LIGHT3);
	}



	//#################################################
	//luz pontual Roda 2

	//posicao
	pointRoda2Pos[0] = -baseWidth * 0.5;
	pointRoda2Pos[1] = -baseHeight * 1.05;
	pointRoda2Pos[2] = baseWidth * 3;
	pointRoda2Pos[3] = 1;//ponto - posição!


	if (amb) {
		pointRoda2Amb[0] = 1.;//R
		pointRoda2Amb[1] = 1.;//G
		pointRoda2Amb[2] = 1.;//B
		pointRoda2Amb[3] = 1.;//constante
	}
	else {
		pointRoda2Amb[0] = 0;//R
		pointRoda2Amb[1] = 0;//G
		pointRoda2Amb[2] = 0;//B
		pointRoda2Amb[3] = 1.;//constante
	}

	if (dif) {
		pointRoda2Dif[0] = 1.;//R
		pointRoda2Dif[1] = 1.;//G
		pointRoda2Dif[2] = 1.;//B
		pointRoda2Dif[3] = 1.;//constante
	}
	else {
		pointRoda2Dif[0] = 0;//R
		pointRoda2Dif[1] = 0;//G
		pointRoda2Dif[2] = 0;//B
		pointRoda2Dif[3] = 1.;//constante
	}

	if (spec) {
		pointRoda2Spec[0] = 1.;//R
		pointRoda2Spec[1] = 1.;//G
		pointRoda2Spec[2] = 1.;//B
		pointRoda2Spec[3] = 1.;//constante
	}
	else {
		pointRoda2Spec[0] = 0;//R
		pointRoda2Spec[1] = 0;//G
		pointRoda2Spec[2] = 0;//B
		pointRoda2Spec[3] = 1.;//constante
	}

	glLightfv(GL_LIGHT4, GL_POSITION, pointRoda2Pos);
	glLightfv(GL_LIGHT4, GL_AMBIENT, pointRoda2Amb);
	glLightfv(GL_LIGHT4, GL_SPECULAR, pointRoda2Spec);

	//atenuação

	pointRoda2AtC = 0.2;
	pointRoda2AtL = 0.0001;
	pointRoda2AtQ = 0.00001;
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, pointRoda2AtC);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, pointRoda2AtL);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, pointRoda2AtQ);


	if (pointRoda2On) {
		glEnable(GL_LIGHT4);
	}
	else {
		glDisable(GL_LIGHT4);
	}


	//#################################################
	//luz foco left

	//posicao
	spotPos[0] = 0;
	spotPos[1] = 0.;
	spotPos[2] = 3000;
	spotPos[3] = 1.;


	//direcao
	//spotDir[0] = 0.;
	//spotDir[1] = 0.;
	spotDir[2] = -1.;
	//spotDir[3] = 0.;Não tem a 4 coordenada, é sempre vetor


	if (amb) {
		//ambiente
		spotAmb[0] = 1.;//R
		spotAmb[1] = 1.;//G
		spotAmb[2] = 1.;//B
		spotAmb[3] = 0.;//constante
	}
	else {
		//ambiente
		spotAmb[0] = 0.;//R
		spotAmb[1] = 0.;//G
		spotAmb[2] = 0.;//B
		spotAmb[3] = 0.;//constante
	}
	if (dif) {
		//difusa
		spotDif[0] = 1.;//R
		spotDif[1] = 1.;//G
		spotDif[2] = 1.;//B
		spotDif[3] = 1.;//constante
	}
	else {
		//difusa
		spotDif[0] = 0.;//R
		spotDif[1] = 0.;//G
		spotDif[2] = 0.;//B
		spotDif[3] = 1.;//constante
	}
	if (spec) {
		//specular
		spotSpecular[0] = 1.;//R
		spotSpecular[1] = 1.;//G
		spotSpecular[2] = 1.;//B
		spotSpecular[3] = 1.;//constante
	}
	else {
		//specular
		spotSpecular[0] = 0.;//R
		spotSpecular[1] = 0.;//G
		spotSpecular[2] = 0.;//B
		spotSpecular[3] = 1.;//constante
	}

	glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

	glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpecular);

	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);

	//atenuação
	spotAtC = 1.;
	spotAtL = 0.;
	spotAtQ = 0.;
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, spotAtC);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, spotAtL);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, spotAtQ);
	if (spotOn) {
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT2);
	}

}


void ofApp::skybox() {

	//desenhamos normalmente para um buffer na placa gráfica
	//após o desenho pegamos na imagem resultante e utilizamos como textura


	//para cirar o efeito de fadeout, limpamos o framebuffer com um retângulo quase transparente
	//RGBA -> (0, 0, 0, 0.01)
	//no começo de cada novo frame
	//assim, o desenho do frame anterior vai persistindo e fazendo fade-out

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	nightSky.begin();//inicio do desenho em frame buffer


	//limpa o framebuffer com retângulo
	glColor4f(0, 0, 0, 0.05);
	ofDrawRectangle(0, 0, gw(), gh());

	glPushMatrix();
	glTranslatef(0, 0, 1.);
	float x = ofRandom(0, gw());
	float y = ofRandom(0, gh());

	ofSetColor(255, 255, 255, 255);
	ofDrawCircle(x, y, 1);
	ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255), ofRandom(20, 255));
	ofRect(ofRandom(0, gw() * 0.5), ofRandom(0, gh()), 2, 2);

	glPopMatrix();
	nightSky.end();//fim do desenho em frame buffer
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	ofDisableAlphaBlending();

	nightSky.readToPixels(nightSkyImg.getPixelsRef());
	nightSkyImg.update();

	glEnable(GL_TEXTURE);
	nightSkyImg.bind();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor4f(1, 1, 1, 1);
	glPushMatrix();
	glRotatef(rx, 1, 0, 0);
	glRotatef(ry, 0, 1, 0);
	glRotatef(rz, 0, 0, 1);
	glScalef(gw() * 5, gw() * 5, gw() * 5);
	sphereSkyBox(128);
	glPopMatrix();


	nightSkyImg.unbind();
	glDisable(GL_TEXTURE);

	rx += 0.01;
	ry += 0.2;
	rz += 0.015;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		amb = !amb;
		break;
	case '2':
		dif = !dif;
		break;
	case '3':
		spec = !spec;
		break;
	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'o':
		orto = !orto;
		break;

	case 'a':
		ambientOn = !ambientOn;
		break;
	case 'd':
		dirOn = !dirOn;
		break;
	case 'p':
		pointOn = !pointOn;
		break;

	case 'r':
		pointRoda1On = !pointRoda1On;
		pointRoda2On = !pointRoda2On;
		break;

	case 's':
		spotOn = !spotOn;
		break;

	case 'l':
		spotCutoff++;
		if (spotCutoff > 180) {
			spotCutoff = 180;
		}
		break;
	case 'k':
		spotCutoff--;
		if (spotCutoff < 1) {
			spotCutoff = 1;
		}
		break;

	case OF_KEY_LEFT:
		objectRotationAngle += 5.0f;
		break;
	case OF_KEY_RIGHT:
		objectRotationAngle -= 5.0f;
		break;
	case 'v':
		view++;
		if (view > 3) {
			view = 0;
		}
		break;
	case 'q':
		autoMove = !autoMove;
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	cout << endl << x << " " << y;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	setup();

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit() {
	img_glass.clear();
	img_predio1.clear();
	img_predio2.clear();
	img_tijolos.clear();
	img_chao.clear();
	img_predio_noite.clear();
}



