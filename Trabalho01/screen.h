#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <vector>

class Screen
{
  public:
    Screen (bool);

    void setStatus (bool);
    bool getStatus ();
    pid_t getPid();
    void setPid(pid_t);
    std::string getFilename();
    void createScreenFilename();

    static std::vector <Screen*> activeScreens;

    static Screen getActiveScreen();
    static void listScreens();
    static void deactivateAllScreens();
    static void killAllScreens();

  private:
    pid_t pid;
    bool active;
    std::string filename;
    static unsigned nextId;
    unsigned screenId;

    static Screen* activeScreen;
};
