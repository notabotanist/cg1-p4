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
	LightManager();

public:
	static int getNextLight();
	static void resetLights();
}

/// Class for positional & directional lights
/// but not ambient light.
class Light : public Geometry {
private:
	/// OpenGL light constant assigned to this light
	const int lightHandle;

public:
	/// RGBA light color
	float color[4];

protected:
	virtual void doRender();
}

#endif
