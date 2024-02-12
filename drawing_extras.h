#pragma once

#include "ofMain.h"
#include "extras.h"

# define M_PI           3.14159265358979323846
//desenha ponto 3D na origem
inline void drawPoint() {
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
}

inline void drawLine(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

//desenha axis 3D
inline void axis3d() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

//função que desenha quadrado unitário 
//centrado na origem e preenchido
inline void rectFill_unit() {
	glBegin(GL_QUADS);
	glVertex3d(-0.5, -0.5, 0.);
	glVertex3d(-0.5, 0.5, 0.);
	glVertex3d(0.5, 0.5, 0.);
	glVertex3d(0.5, -0.5, 0.);
	glEnd();
}

//função que desenha malha unitária com resolução mxn
inline void malha_unit(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex2d(i * x_step + x_start, j * y_step + y_start);
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();

}

inline void malha_unit_yup(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex3f(i * x_step + x_start, j * y_step + y_start, 0);
			glVertex3f((i + 1) * x_step + x_start, j * y_step + y_start, 0);
			glVertex3f((i + 1) * x_step + x_start, (j + 1) * y_step + y_start, 0);
			glVertex3f(i * x_step + x_start, (j + 1) * y_step + y_start, 0);
		}
	}
	glEnd();
}


inline void malha_unit_with_textures(GLint m, GLint n, GLint aux) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//a malha tem sua origem no ponto (0,0,0)
	//temos de definir o canto por onde queremos começar a calcular os vértices
	//no caso, escolhemos o canto esquerdo superior (-0.5, -0.5, 0)
	//a malha tem tamanho unitário
	//aqui calculamos o tamanho de cada retângulo (ou a distância x, y entre os vértices)
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);


	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {

			glNormal3f(0, 0, 1);
			glTexCoord2f(aux * i * 1 / float(m), aux * j * 1 / float(n) );
			glVertex3f(i * x_step + x_start, j * y_step + y_start, 0);

			glNormal3f(0, 0, 1);
			glTexCoord2f(aux * i * 1 / float(m), aux * (j + 1) * 1 / float(n));
			glVertex3f(i * x_step + x_start, (j + 1) * y_step + y_start, 0);

			glNormal3f(0, 0, 1);
			glTexCoord2f(aux * (i + 1) * 1 / float(m), aux * (j + 1) * 1 / float(n));
			glVertex3f((i + 1) * x_step + x_start, (j + 1) * y_step + y_start, 0);

			glNormal3f(0, 0, 1);
			glTexCoord2f(aux * (i + 1) * 1 / float(m), aux * (j) * 1 / float(n));
			glVertex3f((i + 1) * x_step + x_start, (j)*y_step + y_start, 0);
		}
	}
	glEnd();
}


inline void triangular_prism_unit() {
	GLfloat p = 0.5;


	glBegin(GL_TRIANGLES);

	//frente
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(0, p, p);
	

	//tras
	glNormal3f(0, 0, 1); glVertex3f(0, p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, -p);
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, -p);
	
	
	glEnd();


	glBegin(GL_QUADS);


	// Base do prisma (triangular)
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, p);


	glNormal3f(0, 0, 1); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(0, p, p);
	glNormal3f(0, 0, 1); glVertex3f(0, p, -p);
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, -p);


	

	glEnd();
}


inline void cube_unit() {
	GLfloat p = 0.5;
	glBegin(GL_QUADS);
	//frente

	glNormal3f(0, 0, 1); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(-p, p, p);
	glNormal3f(0, 0, 1); glVertex3f(p, p, p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, p);

	//tras
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, p, -p);
	glNormal3f(0, 0, 1); glVertex3f(-p, p, -p);

	//cima
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, -p);

	//baixo
	glNormal3f(0, 0, 1); glVertex3f(-p, p, p);
	glNormal3f(0, 0, 1); glVertex3f(-p, p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, p, p);

	//esq
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glVertex3f(-p, p, -p);
	glNormal3f(0, 0, 1); glVertex3f(-p, p, p);

	//dir
	glNormal3f(0, 0, 1); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glVertex3f(p, p, p);
	glNormal3f(0, 0, 1); glVertex3f(p, p, -p);
	glNormal3f(0, 0, 1); glVertex3f(p, -p, -p);

	glEnd();

}

inline void cube_unit_with_textures(float W, float H) {
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat p = 0.5;
	glBegin(GL_QUADS);

	// Frente
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, H); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-p, p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, 0.0); glVertex3f(p, p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, H); glVertex3f(p, -p, p);

	// Trás
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, H); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(p, -p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, 0.0); glVertex3f(p, p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, H); glVertex3f(-p, p, -p);

	// Cima
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, H ); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, 0.0); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, H); glVertex3f(p, -p, -p);

	// Baixo
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, H); glVertex3f(-p, p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-p, p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, 0.0); glVertex3f(p, p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, H); glVertex3f(p, p, p);

	// Esquerda
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, H); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, 0.0); glVertex3f(-p, p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, H); glVertex3f(-p, p, p);

	// Direita
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, H); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(p, p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, 0.0); glVertex3f(p, p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(W, H); glVertex3f(p, -p, -p);

	glEnd();
	
}


inline void pyrimd_unit() {
	GLfloat p = 0.5;
	glBegin(GL_TRIANGLES);

	// Frente
	glVertex3f(0, p, 0);
	glVertex3f(-p, -p, p);
	glVertex3f(p, -p, p);

	// Trás
	glVertex3f(0, p, 0);
	glVertex3f(p, -p, -p);
	glVertex3f(-p, -p, -p);

	// esquerdo
	glVertex3f(0, p, 0);
	glVertex3f(-p, -p, -p);
	glVertex3f(-p, -p, p);

	// direito
	glVertex3f(0, p, 0);
	glVertex3f(p, -p, p);
	glVertex3f(p, -p, -p);

	glEnd();

	// Base 
	glBegin(GL_QUADS);

	glVertex3f(-p, -p, p);
	glVertex3f(p, -p, p);
	glVertex3f(p, -p, -p);
	glVertex3f(-p, -p, -p);

	glEnd();

}


inline void pyramid_unit_with_textures() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat p = 0.5;
	glBegin(GL_TRIANGLES);

	// Frente
	glNormal3f(0, 0, 1); glTexCoord2f(0.5, 1.0); glVertex3f(0, p, 0);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(p, -p, p);

	// Trás
	glNormal3f(0, 0, 1); glTexCoord2f(0.5, 1.0); glVertex3f(0, p, 0);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(p, -p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(-p, -p, -p);

	// Esquerda
	glNormal3f(0, 0, 1); glTexCoord2f(0.5, 1.0); glVertex3f(0, p, 0);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(-p, -p, p);

	// Direita
	glNormal3f(0, 0, 1); glTexCoord2f(0.5, 1.0); glVertex3f(0, p, 0);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(p, -p, -p);

	glEnd();

	// Base 
	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(p, -p, p);
	glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(p, -p, -p);
	glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(-p, -p, -p);

	glEnd();
}


//funcao que desenha cubo unit�rio com malha_unit()
inline void cube_malha_unit(GLint m, GLint n) {

	//tras
	
	glPushMatrix();
	glTranslated(0., 0., -0.5);
	glRotated(180, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//cima

	glPushMatrix();
	glTranslated(0., -0.5, 0.);
	glRotated(90, 1, 0, 0);
	malha_unit(m, n);
	glPopMatrix();

	//baixo

	glPushMatrix();
	glTranslated(0., 0.5, 0.);
	glRotated(-90, 1, 0, 0);
	malha_unit(m, n);
	glPopMatrix();

	//esquerda
	glPushMatrix();
	glTranslated(-0.5, 0., 0.);
	glRotated(-90, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//direita
	
	glPushMatrix();
	glTranslated(0.5, 0., 0.);
	glRotated(90, 0, 1, 0);
	malha_unit(m, n);
	glPopMatrix();

	//frente
	glPushMatrix();
	glTranslated(0., 0., 0.5);
	malha_unit(m, n);
	glPopMatrix();

}

//funcao que desenha cubo unit�rio com malha_unit()
inline void cube_malha_unit_with_textures(GLint m, GLint n, GLint aux) {

	//tras

	glPushMatrix();
	glTranslated(0., 0., -0.5);
	glRotated(180, 0, 1, 0);
	malha_unit_with_textures(m, n, aux);
	glPopMatrix();

	//cima

	glPushMatrix();
	glTranslated(0., -0.5, 0.);
	glRotated(90, 1, 0, 0);
	malha_unit_with_textures(m, n, aux);
	glPopMatrix();

	//baixo

	glPushMatrix();
	glTranslated(0., 0.5, 0.);
	glRotated(-90, 1, 0, 0);
	malha_unit_with_textures(m, n, aux);
	glPopMatrix();

	//esquerda
	glPushMatrix();
	glTranslated(-0.5, 0., 0.);
	glRotated(-90, 0, 1, 0);
	malha_unit_with_textures(m, n, aux);
	glPopMatrix();

	//direita

	glPushMatrix();
	glTranslated(0.5, 0., 0.);
	glRotated(90, 0, 1, 0);
	malha_unit_with_textures(m, n, aux);
	glPopMatrix();

	//frente
	glPushMatrix();
	glTranslated(0., 0., 0.5);
	malha_unit_with_textures(m, n, aux);
	glPopMatrix();

}

inline void circleTrig2D(GLfloat x, GLfloat y, GLfloat r, GLint n) {
	GLfloat angleIncrement = 2.0 * M_PI / n; 
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1); glVertex2f(x, y);

	for (int i = 0; i <= n; i++) {
		GLfloat angle = i * angleIncrement;
		GLfloat xVertex = x + r * cos(angle);
		GLfloat yVertex = y + r * sin(angle);
		glNormal3f(0, 0, 1); glVertex2f(xVertex, yVertex);
	}

	glEnd();

}

void rodaGigante(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, GLint n) {

	// Desenha os raios do prisma
	circleTrig2D(x, y, r, n);

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= n; i++) {
		GLfloat angle = i * (2.0 * M_PI / n);
		GLfloat xVertex = x + r * cos(angle);
		GLfloat yVertex = y + r * sin(angle);

		// Vertices na base do prisma
		glNormal3f(0, 0, 1); glVertex3f(xVertex, yVertex, z);

		// Vertices no topo do prisma
		glNormal3f(0, 0, 1); glVertex3f(xVertex, yVertex, z + height);
	}
	glEnd();

}

inline void sphereSkyBox(int res) {
	float dtheta = PI / float(res);
	float dphi = 2 * PI / float(res);



	for (int i = 0; i < res; i++) {
		for (int j = 0; j < res; j++) {
			glBegin(GL_QUADS);

			float x1 = sin(i * dtheta) * cos(j * dphi);
			float y1 = sin(i * dtheta) * sin(j * dphi);
			float z1 = cos(i * dtheta);
			float tx1 = i / float(res);
			float ty1 = j / float(res);
			ofVec3f n1 = ofVec3f(-x1, -y1, -z1);
			glTexCoord2f(ty1, tx1);
			glNormal3f(n1.x, n1.y, n1.z);
			glVertex3f(x1, y1, z1);

			float x2 = sin(i * dtheta) * cos((j + 1) * dphi);
			float y2 = sin(i * dtheta) * sin((j + 1) * dphi);
			float z2 = cos(i * dtheta);
			float tx2 = i / float(res);
			float ty2 = (j + 1) / float(res);
			ofVec3f n2 = ofVec3f(-x2, -y2, -z2);
			glTexCoord2f(ty2, tx2);
			glNormal3f(n2.x, n2.y, n2.z);
			glVertex3f(x2, y2, z2);

			float x3 = sin((i + 1) * dtheta) * cos((j + 1) * dphi);
			float y3 = sin((i + 1) * dtheta) * sin((j + 1) * dphi);
			float z3 = cos((i + 1) * dtheta);
			float tx3 = (i + 1) / float(res);
			float ty3 = (j + 1) / float(res);
			ofVec3f n3 = ofVec3f(-x3, -y3, -z3);
			glTexCoord2f(ty3, tx3);
			glNormal3f(n3.x, n3.y, n3.z);
			glVertex3f(x3, y3, z3);

			float x4 = sin((i + 1) * dtheta) * cos(j * dphi);
			float y4 = sin((i + 1) * dtheta) * sin(j * dphi);
			float z4 = cos((i + 1) * dtheta);
			float tx4 = (i + 1) / float(res);
			float ty4 = j / float(res);
			ofVec3f n4 = ofVec3f(-x4, -y4, -z4);
			glTexCoord2f(ty4, tx4);
			glNormal3f(n4.x, n4.y, n4.z);
			glVertex3f(x4, y4, z4);

			glEnd();
		}
	}
}