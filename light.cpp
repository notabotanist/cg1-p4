// File: light.cpp
// Author: Matthew MacEwan
// /////////////////////////////////////////////////////////////////////

#include "light.h"
#include <GL/glut.h>
#include <cmath>

/////////
// LightManager
/////////
int LightManager::curLight(GL_LIGHT0);

int LightManager::getNextLight() {
    int assignedLight(curLight);
    if (assignedLight >= GL_LIGHT0 + GL_MAX_LIGHTS) {
        assignedLight = -1;
    } else {
        curLight++;
        glEnable(assignedLight);
    }
    return assignedLight;
}

void LightManager::resetLights() {
    curLight = GL_LIGHT0;
}

//////////////
// GlobalMaterials
//////////////
void GlobalMaterials::setNoMaterial() {
    GLfloat no_mat[] = {0, 0, 0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
}

void GlobalMaterials::setBuildingMaterial() {
    GlobalMaterials::setNoMaterial();
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1};
    GLfloat diffuse[] = {0.5, 0.5, 0.5, 1}; // gray buildings
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
}

void GlobalMaterials::setGroundMaterial() {
    GlobalMaterials::setNoMaterial();
    GLfloat ambient[] = {0, 0.2, 0, 1};
    GLfloat diffuse[] = {0, 0.5, 0, 1}; // green grass
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
}

void GlobalMaterials::setDishMaterial() {
    GlobalMaterials::setNoMaterial();
    GLfloat ambient[] = {0, 0, 0, 1};
    GLfloat diffuse[] = {0.8, 0.8, 0.8, 1};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
}

void GlobalMaterials::setExplosionMaterial() {
    GlobalMaterials::setNoMaterial();
    GLfloat emissive[] = {1.0, 0.55, 0, 1};
    glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
}

void GlobalMaterials::setLaserMaterial() {
    GlobalMaterials::setNoMaterial();
    GLfloat emissive[] = {1, 0, 1, 1};
    glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
}

////////////
// Light
////////////
Light::Light(float _x, float _y, float _z) : Geometry(_x, _y, _z),
        directional(false) {
}

void Light::doRender() {
    lightHandle = LightManager::getNextLight();
    if (lightHandle < 0) {
        // Too many lights!
        return;
    }

    GLfloat* lightPos;
    // prepare light data
    if (directional) {
        GLfloat dlightPos[] = {x, y, z, 0}; // Change to use trig with yaw and pitch as you dare
        lightPos = dlightPos;
    } else {
        GLfloat plightPos[] = {x, y, z, 1};
        lightPos = plightPos;
    }

    // position and set light color
    glLightfv(lightHandle, GL_POSITION, lightPos);
    glLightfv(lightHandle, GL_DIFFUSE, color);
}

void Light::assignColor3f(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
