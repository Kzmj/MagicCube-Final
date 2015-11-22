#pragma once

#include "MagicCube.h"

struct location
{
	float X;
	float Y;
	float Z;

	float XRot;
	float YRot;
};
class mob
{
public:
	location MobLocation;
	float Speed;
	mob()
	{
		MobLocation.X = 0;
		MobLocation.Y = 0;
		MobLocation.Z = 0;
		MobLocation.XRot = 0;
		MobLocation.YRot = 0;
		Speed = 1;
	}
};
class mobs
{

public:
	std::vector<mob> Mob;
	mobs()
	{
		Mob.push_back(mob());
	}
	void addMob()
	{
		Mob.push_back(mob());
	}
};

extern mobs Mobs;