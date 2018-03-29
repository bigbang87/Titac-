#pragma once

class Actor
{
public:
	Actor();
	virtual void onBegin() {};
	virtual void onTick() {};
};