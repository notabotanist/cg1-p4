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
