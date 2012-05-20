// File: light.h
// Author: Matthew MacEwan
// Classes and global values supporting various lighting scenarios
// /////////////////////////////////////////////////////////////////////

#ifndef LIGHT_H_
#define LIGHT_H_

#include "scene.h"

/// asdf
class LightManager {
private:
	static int curLight;

private:
	LightManager() {};

public:
	static int getNextLight();
	static void resetLights();
};

/// Class for positional & directional lights
/// but not ambient light.
class Light : public Geometry {
protected:
	/// OpenGL light constant assigned to this light
	int lightHandle;

public:
	/// RGBA light color
	float color[4];

	/// boolean indicating if the light is directional or positional
	bool directional;

protected:
	virtual void doRender();

public:
    Light(float _x = 0, float _y = 0, float _z = 0);
    virtual ~Light() {};

    void assignColor3f(float r, float g, float b);
};

#endif
