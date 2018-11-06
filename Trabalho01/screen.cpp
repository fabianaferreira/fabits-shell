#include "screen.h"
#include "consts.h"
#include <iostream>
// #include <string>


/*Como fazer o nome ser opcional?*/
// Screen::Screen (pid_t currentPid, bool status, std::string screenFilename)
// {
// 	pid = currentPid;
// 	active = status;
// 	filename = screenFilename;
// 	screenId = nextId;
// 	nextId++;
// }

unsigned Screen::nextId = 0;

Screen::Screen (bool status)
{
	active = status;	
	screenId = nextId;
	nextId++;
	filename = std::string(FIFO_PATH) + "screen_" + std::to_string(screenId);
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

void Screen::setPid(pid_t currentPid)
{
	pid = currentPid;
}

std::string Screen::getFilename()
{
	return filename;
}

void Screen::createScreenFilename() 
{
	std::string screenFilename;
	std::stringstream stringStream;
	stringStream << (int) pid;
	screenFilename = stringStream.str();
	filename = "./files/" + screenFilename + ".txt";
}