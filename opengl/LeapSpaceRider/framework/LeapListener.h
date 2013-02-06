#ifndef LEAP_LISTENER_H
#define LEAP_LISTENER_H


#include <iostream>
#include "../Leap/include/Leap.h"


class UserListener : public Leap::Listener
{
public:
	virtual void onInit(const Leap::Controller&);
	virtual void onConnect(const Leap::Controller&);
	virtual void onDisconnect(const Leap::Controller&);
	virtual void onExit(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
};


#endif