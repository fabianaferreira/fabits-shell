#include "screen.h"
#include "consts.h"
#include <iostream>
#include <signal.h>
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
Screen* Screen::activeScreen = NULL;
std::vector <Screen*> Screen::activeScreens;

Screen::Screen (bool status)
{
	active = status;
	screenId = nextId;
	nextId++;
	filename = std::string(FIFO_PATH) + "screen_" + std::to_string(screenId);
  if (active)
  {
    /*Se nao for a primeira, vai desativar tudo*/
    if (activeScreens.size() != 0)
    {
      deactivateAllScreens();
    }

    /*Adiciona screen atual ao array de screens*/
    Screen::activeScreens.push_back(this);
    Screen::activeScreen = this;
  }
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

Screen Screen::getActiveScreen ()
{
	return (*(Screen::activeScreen));
}

void Screen::listScreens()
{
  for (std::vector<Screen*>::iterator iter = Screen::activeScreens.begin();
       iter != Screen::activeScreens.end();
       iter++)
  {
       std::cout << "Screen: " << (*iter)->getPid() << std::endl;
  }
}

void Screen::killAllScreens ()
{
	for (std::vector<Screen*>::iterator iter = Screen::activeScreens.begin();
       iter != Screen::activeScreens.end();
       iter++)
    {
    		kill((*iter)->getPid(), SIGTERM);
    }
}

void Screen::deactivateAllScreens ()
{
  for (std::vector<Screen*>::iterator iter = Screen::activeScreens.begin();
       iter != Screen::activeScreens.end();
       iter++)
  {
          (*iter)->setStatus(false);
  }
}
