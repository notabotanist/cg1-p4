// File: hud.cpp
//
// Author: Matthew MacEwan
// ////////////////////////////////////////////////////////////////////// 

#include "hud.h"
#include "camera.h"
#include "light.h"
#include<GL/glut.h>
#include<cmath>

#define PI_180 0.017453

Hud::Hud(Camera& cam, float retlen, float retoff) : Geometry(), head(cam),
		reticleLength(retlen), reticleOffset(retoff), warn(false), ttl(0) {
}

void Hud::startWarning() {
	warn = true;
	ttl = 32;	// 32 frames of warning
}

/// move LCS in front of camera
void Hud::fixLCS() {
	float near = 2.5; // nastily assumes the near plane is 1.0 in front of cam
	float xoff, yoff, zoff;
	head.calcView(xoff, yoff, zoff);

	// translate LCS
	x = head.x + xoff * near;
	y = head.y + yoff * near;
	z = head.z + zoff * near;

	// rotate LCS
	pitch = -head.pitch * cos(head.yaw * PI_180);
	roll = -head.pitch * sin(head.yaw * PI_180);
	yaw = -head.yaw;
}

void Hud::drawWarn() {
	// warn X is red
	glColor3f(1, 0, 0);
	GlobalMaterials::setInterfaceMaterial(1, 0, 0);
	float retExtent = reticleOffset + reticleLength;

	glBegin(GL_LINES);
		glVertex3f(-retExtent, retExtent, 0);
		glVertex3f(retExtent, -retExtent, 0);
		glVertex3f(-retExtent, -retExtent, 0);
		glVertex3f(retExtent, retExtent, 0);
	glEnd();
}

void Hud::doRender() {
	// crosshairs are white
	glColor3f(1, 1, 1);
	GlobalMaterials::setInterfaceMaterial(1, 1, 1);
	float retExtent = reticleOffset + reticleLength;
	glBegin(GL_LINES);
		glVertex3f(reticleOffset, 0, 0);
		glVertex3f(retExtent, 0, 0);
		glVertex3f(-reticleOffset, 0, 0);
		glVertex3f(-retExtent, 0, 0);
		glVertex3f(0, reticleOffset, 0);
		glVertex3f(0, retExtent, 0);
		glVertex3f(0, -reticleOffset, 0);
		glVertex3f(0, -retExtent, 0);
	glEnd();

	// draw warning if necessary
	if (warn && ttl % 16 < 8) { 
		// mod term enables flashing
		drawWarn();
	}
}

void Hud::animate() {
	fixLCS();

	if (warn) {
		ttl--;
		if (ttl < 0) {
			warn = false;
			ttl = 0;
		}
	}
}
