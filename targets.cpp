// File: targets.cpp
//
// Author: Matthew MacEwan
//
// //////////////////////////////////////////////////////////////////////

#include <cmath>
#include <GL/glut.h>
#include "targets.h"
#include "texture.h"

static const int TIME_TO_IMPACT = 100; // frames
static const int EXPLOSION_TIME = 25; // frames

Target::Target() : Geometry(), ttl(0), state(T_IDLE) {}
Target::Target(float _x, float _y, float _z) : Geometry(_x, _y, _z), ttl(0), state(T_IDLE) {
}

void Target::renderExplosion() {
	glPushMatrix();

	float scale = sqrt((EXPLOSION_TIME + 1 - ttl) / (float)EXPLOSION_TIME);
	glScalef(scale, scale, scale);
	GlobalMaterials::setExplosionMaterial();
	glColor3ub(0xFF, 0x8C, 0);
	if (solid) {
		glutSolidSphere(2.0, 10, 5);
	} else {
		glutWireSphere(2.0, 10, 5);
	}

	glPopMatrix();
}

void Target::renderMissile() {
	if (ttl <= 2) {
		glPushMatrix();
		glScalef(0.1, 50, 0.1);
		glTranslatef(0, 0.5, 0);
		glColor3f(1, 0, 1);
		GlobalMaterials::setLaserMaterial();
		if (solid) {
			glutSolidCube(1.0);
		} else {
			glutWireCube(1.0);
		}
		glPopMatrix();
	}
}

void Target::doRender() {
	switch (state) {
	case T_TARGETED:
		renderMissile();
		renderReticle();
	case T_IDLE:
		renderIdle();
		break;
	case T_EXPLODING:
		renderExplosion();
		break;
	case T_DEAD:
	default:
		// do nothing
		break;
	}
}

void Target::lockOn() {
	if (state == T_IDLE) {
		state = T_TARGETED;
		ttl = TIME_TO_IMPACT;
	}
}

void Target::respawn() {
	state = T_IDLE;
	ttl = 0;
}

void Target::animate() {
	if (state == T_IDLE || state == T_DEAD) return;

	ttl--;
	if (ttl < 0) {
		switch (state) {
		case T_TARGETED:
			state = T_EXPLODING;
			ttl = EXPLOSION_TIME;
			break;
		case T_EXPLODING:
			state = T_DEAD;
			ttl = 0;
			break;
		}
	}
}


Radar::Radar() : rotation(0), dR(5) {
	setBound(1.420);
	setScale(0.5);	// defaults to 0.5 scale factor
}

Radar::Radar(float _x, float _y, float _z) : Target(_x, _y, _z), rotation(0), dR(5) {
	setBound(1.420);
	setScale(0.5);	// defaults to 0.5 scale factor
}

void Radar::renderIdle() {
	glEnable(GL_NORMALIZE);
	glPushMatrix();
	// Blender helped with the modeling

	// green for 'shoot me!'
	glColor3f(0, 1, 0);
	GlobalMaterials::setBuildingMaterial();
	// draw base
	glPushMatrix();
	glTranslatef(0, 0.371, 0);
	glScalef(1, 0.371, 1);
	if(solid) {
		//glutSolidCube(2.0);
		glScalef(2, 2, 2);
		renderTexCube(TextureLoader::getGeneratorTex(), 0, 1);
	} else {
		glutWireCube(2.0);
	}
	glPopMatrix();

	// rotate LCS for dish
	glRotatef(rotation, 0, 1, 0);

	// draw arm
	GlobalMaterials::setDishMaterial();
	glPushMatrix();
	glTranslatef(0, 0.742, 0.393);
	glScalef(0.557, 1.023, 0.557);
	glRotatef(-90, 1, 0, 0);
	if (solid) {
		glutSolidCone(1.0, 1.0, 4, 1);
	} else {
		glutWireCone(1.0, 1.0, 4, 1);
	}
	glPopMatrix();

	// draw dish
	glPushMatrix();
	glTranslatef(0, 2.038, -0.127);
	glRotatef(-118.9, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(1.019, 1.019, 0.590);
	if (solid) {
		glutSolidCone(1.0, 1.0, 8, 2);
	} else {
		glutWireCone(1.0, 1.0, 8, 2);
	}
	glPopMatrix();

	glPopMatrix();
	glEnable(GL_NORMALIZE);
}

void Radar::renderReticle() {
	float minx = -1.05;
	float miny = -0.05;
	float minz = -1.05;
	float maxx = 1.05;
	float maxy = 2.9;
	float maxz = 1.05;
	float ticklen = 0.5;

	// red for ROCK ON
	glColor3f(0.9, 0, 0);
	GlobalMaterials::setInterfaceMaterial(0.9, 0, 0);
	// draw all corner caps
	glBegin(GL_LINES);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx+ticklen, miny, minz);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx, miny+ticklen, minz);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx, miny, minz+ticklen);

		glVertex3f(minx, miny, maxz);
		glVertex3f(minx+ticklen, miny, maxz);
		glVertex3f(minx, miny, maxz);
		glVertex3f(minx, miny+ticklen, maxz);
		glVertex3f(minx, miny, maxz);
		glVertex3f(minx, miny, maxz-ticklen);

		glVertex3f(minx, maxy, minz);
		glVertex3f(minx+ticklen, maxy, minz);
		glVertex3f(minx, maxy, minz);
		glVertex3f(minx, maxy-ticklen, minz);
		glVertex3f(minx, maxy, minz);
		glVertex3f(minx, maxy, minz+ticklen);

		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx+ticklen, maxy, maxz);
		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx, maxy-ticklen, maxz);
		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx, maxy, maxz-ticklen);

		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx-ticklen, miny, minz);
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny+ticklen, minz);
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny, minz+ticklen);

		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx-ticklen, miny, maxz);
		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx, miny+ticklen, maxz);
		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx, miny, maxz-ticklen);

		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx-ticklen, maxy, minz);
		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx, maxy-ticklen, minz);
		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx, maxy, minz+ticklen);

		glVertex3f(maxx, maxy, maxz);
		glVertex3f(maxx-ticklen, maxy, maxz);
		glVertex3f(maxx, maxy, maxz);
		glVertex3f(maxx, maxy-ticklen, maxz);
		glVertex3f(maxx, maxy, maxz);
		glVertex3f(maxx, maxy, maxz-ticklen);
	glEnd();
}

void Radar::animate() {
	Target::animate();

	rotation = (rotation + dR) % 360;
}

Generator::Generator(Target& ward, float x, float y, float z)
		: Radar(x, y, z), _ward(ward) {
}

void Generator::animate() {
	Target::animate();

	rotation = atan2(z - _ward.z, _ward.x - x) * 57.2957; // 180 / PI
}


Zeppelin::Zeppelin(float _x, float _y, float _z) : Target(_x, _y, _z),
		radius(5), radVel(0.001), radPos(0), searchlight(0,-1,0.6) {
	setBound(2);
	setScale(0.5);
	searchlight.assignColor3f(1, 1, 0);
	searchlight.halfAngle = 60;
	searchlight.exponent = 5;
	searchlight.pitch = -120;
	initNurb();
}

void Zeppelin::addGuardian(Target& guard) {
	guardians.push_back(&guard);
}

void Zeppelin::animate() {
	Target::animate();

	// Sheild remains up while guardians alive
	if (state == T_EXPLODING) {
		// check all guardians
		for (vector<Target*>::iterator iter(guardians.begin());
				iter != guardians.end(); iter++) {
			// if any one is not dead, the sheild caught the laser
			if ((*iter)->state != T_DEAD) {
				state = T_IDLE;
				break;
			}
		}
	}

	// Animate holding pattern
	radPos += radVel;
	if (radPos > 6.28318) {
		radPos = 0;
	}
	// update position
	x = radius * cos(radPos);
	z = -radius * sin(radPos);
	// rotate up
	yaw = (radPos + 3.14159) * 57.29583;
}

void Zeppelin::renderIdle() {
	glEnable(GL_NORMALIZE);
	glPushMatrix();

	// draw envelope
	glColor3f(0, 0.8, 0);
	GlobalMaterials::setDishMaterial();
	glPushMatrix();
	glScalef(1, 1, 2);
	if (solid) {
		glutSolidSphere(1.0, 32, 16);
	} else {
		glutWireSphere(1.0, 32, 16);
	}

	// draw gondola
	glTranslatef(0, -1, -0.07);
	glScalef(0.274, 0.247, 0.344);
	glColor3f(0.7, 0.7, 0.7);
	GlobalMaterials::setBuildingMaterial();
	if (solid) {
		glutSolidCube(2.0);
	} else {
		glutWireCube(2.0);
	}
	glPopMatrix();

	// searchlight goes here
	searchlight.setSolid(solid);
	searchlight.render();
	searchlight.renderBulb();

	// The shield
	renderNurb();

	glPopMatrix();
	glDisable(GL_NORMALIZE);
}

void Zeppelin::renderReticle() {
	// render that
	glColor3f(0.9, 0, 0);
	GlobalMaterials::setInterfaceMaterial(0.9, 0, 0);

	float reticleRadius(2);

	glBegin(GL_LINE_LOOP);
		glVertex3f(0, reticleRadius, 0);
		glVertex3f(reticleRadius, 0, 0);
		glVertex3f(0, -reticleRadius, 0);
		glVertex3f(-reticleRadius, 0, 0);
	glEnd();
}

void Zeppelin::respawn() {
	Target::respawn();
	radPos = 0;
}

void Zeppelin::initNurb() {
    shield = gluNewNurbsRenderer();
    float ys[] = {0.8,0.8,0.8,0.8,0.8,2,2,0.8,0.8,2,2,0.8,0.8,0.8,0.8,0.8};
    int index(0);
    for (int x(0); x < 4; x += 1) {
        for (int z(0); z < 4; z += 1) {
			cPoints[x][z][0] = -1.5 + x;
			cPoints[x][z][2] = -1.5 + z;
			cPoints[x][z][1] = ys[x + 4 * z];
        }
    }
}

void Zeppelin::renderNurb() {
	if (solid) {
		gluNurbsProperty(shield, GLU_DISPLAY_MODE, GLU_FILL);
	} else {
		gluNurbsProperty(shield, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
	}
	GlobalMaterials::setShieldMaterial();

	glEnable(GL_AUTO_NORMAL);
	GLfloat knots[] = {0, 0, 0, 0.1, 0.9, 1, 1, 1};
	gluBeginSurface(shield);
	gluNurbsSurface(shield,
					8, knots,
					8, knots,
					4 * 3,
					3,
					&cPoints[0][0][0],
					4, 4,
					GL_MAP2_VERTEX_3);
	gluEndSurface(shield);
	glDisable(GL_AUTO_NORMAL);
}
