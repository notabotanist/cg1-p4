//
// File: scene.h
//
// Classes for organizing and drawing a scene
// ///////////////////////////////////////////////////////////////////// 

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
using namespace std;

/// @author mrm4677
/// Abstract base class for objects renderable in Scenes
class Geometry {
protected:
	/// if true, the Geometry should render solid instead of wireframe
	bool solid;

	/// factor by which this geometry will be uniformly scaled
	float scale;

	/// radius of bounding sphere of UNSCALED geometry
	float bRadius;

public:
	/// Location of local coordinate system
	float x, y, z;
	/// Rotation of local coordinate system
	float roll, pitch, yaw;

protected:
	Geometry();	// protected to make class abstract
	Geometry(float _x, float _y, float _z);

	/// Implement to create actual geometry with respect to local
	/// coordinate system set up by render()
	/// The current modelview matrix should be identical before and after.
	virtual void doRender() = 0;

public:
	virtual ~Geometry() {}

	/// Set up local coordinate system, in which the implementor's
	/// definition of doRender will place the geometry.
	void render();

	/// Call at invervals to perform animation based on implementor
	/// Default implementation: do nothing
	virtual void animate() {}

	/// Supplies specifications of current bounding sphere
	void getBoundingSphere(float& cx, float& cy, float& cz, float& r);

	/// setters
	/// sets solid render state
	inline void setSolid(bool s) {
		solid = s;
	}
	/// sets homogenous scale factor
	inline void setScale(float s) {
		scale = s;
	}
	/// sets radius of unscaled bounding sphere
	inline void setBound(float r) {
		bRadius = r;
	}
};

/// @author mrm4677
/// Container for Geometries.
class Scene {
private:
	/// can't instantiate Geometry objects.  Keep pointers for polymorphism
	std::vector<Geometry*> children;

public:
	Scene();
	virtual ~Scene();

	/// Iterates over all child Geometries and renders them in turn
	virtual void render();

	/// Iterates over all child Geometries and animates them in turn
	virtual void animate();

	/// Add geometry to scene.  This object takes ownership of the geometry.
	void addGeometry(Geometry& geom);

	/// Sets solid flag for all children
	void setAllSolid(bool s);

	/// Cast a pick ray through the scene
	/// Returns a pointer to the Geometry with the closest intersecting
	/// bounding sphere to the origin of the pick ray.
	Geometry* pickRay(float cx, float cy, float cz,
			  float nx, float ny, float nz);
};

#endif
