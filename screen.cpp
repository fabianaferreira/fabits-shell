#include "screen.h"
#include "consts.h"
#include <iostream>
#include <signal.h>

unsigned Screen::nextId = 0;
Screen* Screen::activeScreen = NULL;
std::vector <Screen*> Screen::activeScreens;

Screen::Screen (bool status)
{
	active = status;
	screenId = nextId;
	nextId++;
	filename = std::string(FIFO_PATH) + "screen_" + std::to_string(screenId);
	screenName = "Screen_" + std::to_string(screenId);
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

std::string Screen::getScreenName()
{
	return screenName;
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
    std::cout << "Name: " << (*iter)->getScreenName()
							<< " | PID: " << (*iter)->getPid()
							<< " | Active: " << (*iter)->getStatus()
							<< std::endl;
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

bool Screen::activateScreen (std::string screenName)
{
  for (std::vector<Screen*>::iterator iter = Screen::activeScreens.begin();
       iter != Screen::activeScreens.end();
       iter++)
  {
    if ((*iter)->getScreenName().compare(screenName) == 0)
    {
			/*
				Desativa todas as screens, ativa a com o nome desejado
			  e altera o activeScreen para receber o ponteiro para a
				screen ativa atual
			*/
      Screen::deactivateAllScreens();
      (*iter)->setStatus(true);
			Screen::activeScreen = (*iter);
      return true;
    }

  }
  return false;
}

bool Screen::removeScreen (std::string screenName)
{
	for (unsigned i = 0; i < Screen::activeScreens.size(); i++)
	{
		std::cout << Screen::activeScreens[i]->getScreenName() << std::endl;
		if (Screen::activeScreens[i]->getScreenName().compare(screenName) == 0)
		{
			/*
				Se estou tentando remover a ativa, entao a tela mais recente criada
				sera a tela nova
			*/
			if (Screen::activeScreens[i]->getStatus())
			{
				unsigned tamanho = Screen::activeScreens.size();
				Screen::activateScreen(Screen::activeScreens[tamanho - 2]->getScreenName());
				Screen::activeScreen = Screen::activeScreens[tamanho - 2];
			}

			/*Feito isso, posso remover*/
			Screen::activeScreens.erase(Screen::activeScreens.begin() + i);
			return true;
		}
	}
	return false;
}
