#include <iostream>
using namespace std;

#include "texture.h"
#include <SOIL/SOIL.h>
#include <GL/glut.h>

GLuint TextureLoader::buildingTex(0);
GLuint TextureLoader::roofTex(0);

int TextureLoader::loadTextures() {
    cout << "Loading..." << endl;

    buildingTex = SOIL_load_OGL_texture(
            "building.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
    if (buildingTex == 0) {
        cout << "Building - Soil error " << SOIL_last_result() << endl;
        return -1;
    }

    roofTex = SOIL_load_OGL_texture(
            "roof.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
    if (roofTex == 0) {
        cout << "Roof - Soil error " << SOIL_last_result() << endl;
        return -1;
    }

    return 0;
}

void resetTexParameters() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

int renderTexCube(unsigned int sideTex, unsigned int topTex,
                  float sideYinvScale) {

    glBindTexture(GL_TEXTURE_2D, sideTex);
    resetTexParameters();
    glBegin(GL_QUADS);
        // draw side1
        glNormal3f(0,0,1); glTexCoord2f(0,0); glVertex3f(-0.5, -0.5, 0.5);
        glNormal3f(0,0,1); glTexCoord2f(1,0); glVertex3f(0.5, -0.5, 0.5);
        glNormal3f(0,0,1); glTexCoord2f(1,sideYinvScale); glVertex3f(0.5, 0.5, 0.5);
        glNormal3f(0,0,1); glTexCoord2f(0,sideYinvScale); glVertex3f(-0.5, 0.5, 0.5);
        // draw side2
        glNormal3f(1,0,0); glTexCoord2f(0,0); glVertex3f(0.5, -0.5, 0.5);
        glNormal3f(1,0,0); glTexCoord2f(1,0); glVertex3f(0.5, -0.5, -0.5);
        glNormal3f(1,0,0); glTexCoord2f(1,sideYinvScale); glVertex3f(0.5, 0.5, -0.5);
        glNormal3f(1,0,0); glTexCoord2f(0,sideYinvScale); glVertex3f(0.5, 0.5, 0.5);
        // draw side3
        glNormal3f(0,0,-1); glTexCoord2f(0,0); glVertex3f(0.5, -0.5, -0.5);
        glNormal3f(0,0,-1); glTexCoord2f(1,0); glVertex3f(-0.5, -0.5, -0.5);
        glNormal3f(0,0,-1); glTexCoord2f(1,sideYinvScale); glVertex3f(-0.5, 0.5, -0.5);
        glNormal3f(0,0,-1); glTexCoord2f(0,sideYinvScale); glVertex3f(0.5, 0.5, -0.5);
        // draw side4
        glNormal3f(-1,0,0); glTexCoord2f(0,0); glVertex3f(-0.5, -0.5, -0.5);
        glNormal3f(-1,0,0); glTexCoord2f(1,0); glVertex3f(-0.5, -0.5, 0.5);
        glNormal3f(-1,0,0); glTexCoord2f(1,sideYinvScale); glVertex3f(-0.5, 0.5, 0.5);
        glNormal3f(-1,0,0); glTexCoord2f(0,sideYinvScale); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, topTex);
    resetTexParameters();
    glBegin(GL_QUADS);
        // draw top
        glNormal3f(0,1,0); glTexCoord2f(0,0); glVertex3f(-0.5, 0.5, 0.5);
        glNormal3f(0,1,0); glTexCoord2f(1,0); glVertex3f(0.5, 0.5, 0.5);
        glNormal3f(0,1,0); glTexCoord2f(1,1); glVertex3f(0.5, 0.5, -0.5);
        glNormal3f(0,1,0); glTexCoord2f(0,1); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
}
