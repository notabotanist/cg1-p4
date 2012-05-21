// File: targets.h
//
// //////////////////////////////////////////////////////////////////////

#ifndef TARGETS_H_
#define TARGETS_H_

#include "scene.h"
#include "light.h"

/// @author mrm4677
/// Base class for geometry objects which can be targeted
class Target : public Geometry {
private:
	int ttl;

public:
	enum TState { T_IDLE, T_TARGETED, T_EXPLODING, T_DEAD };
	TState state;

private:
	void renderExplosion();
	void renderMissile();

protected:
	void doRender();

	virtual void renderIdle() = 0;
	virtual void renderReticle() = 0;

public:
	Target();
	Target(float _x, float _y, float _z);

	virtual void animate();

	// Put Target into targetted state and begin countdown to impact
	void lockOn();

	// Reset target to idle state
	virtual void respawn();
};

/// @author mrm4677
/// Stationary enemy emplacements with rotating dish
class Radar : public Target {
protected:
	/// current rotation of dish in degrees
	int rotation;
	/// dish rotation rate in degrees/frame
	int dR;

protected:
	// render implementation
	virtual void renderIdle();
	virtual void renderReticle();

public:
	Radar();
	Radar(float _x, float _y, float _z);

	// Implementations over abstract
	/// Incrementally rotate dish
	virtual void animate();
};

/// Shield generator.  Will rotate to point toward shielded target
class Generator : public Radar {
private:
	/// Reference to warded target
	Target& _ward;

public:
	Generator(Target& ward, float x = 0, float y = 0, float z = 0);

	/// supersede rotation over time to point at target
	virtual void animate();
};

/// Mobile enemy command fortress, protected by a number of shield generators
/// Flies circular holding pattern around the city
class Zeppelin : public Target {
private:
	/// as long as any guardian is alive, the Zeppelin cannot be destroyed
	/// Zeppelin does not take ownership of these guardians
	vector<Target*> guardians;

	/// Mobile light source.  TODO: upgrade to spotlight
	Light searchlight;

protected:
	/// animation information
	float radius;
	float radVel;
	float radPos;

protected:
	virtual void renderIdle();
	virtual void renderReticle();

public:
	Zeppelin(float _x = 0, float _y = 0, float _z = 0);

	virtual void animate();

	/// Add a guardian
	void addGuardian(Target& guard);

	/// Reset the position too
	virtual void respawn();
};

#endif
