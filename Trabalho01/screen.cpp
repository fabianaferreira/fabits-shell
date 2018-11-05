#include "screen.h"
#include <iostream>

Screen::Screen (pid_t currentPid, bool status)
{
	pid = currentPid;
	active = status;
}

void Screen::setStatus(bool status)
{
	active = status;
}

bool Screen::getStatus()
{
	return active;
}

pid_t Screen::getPid()
{
	return pid;
}
