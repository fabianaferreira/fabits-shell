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
    std::string getScreenName();

    // Variaveis estaticas
    static std::vector <Screen*> activeScreens;

    // Metodos estaticos
    static Screen getActiveScreen ();
    static void listScreens ();
    static void deactivateAllScreens ();
    static void killAllScreens ();
    static bool activateScreen (std::string);
    static bool removeScreen (std::string);

  private:
    pid_t pid;
    bool active;
    std::string filename;
    std::string screenName;
    static unsigned nextId;
    unsigned screenId;

    static Screen* activeScreen;
};
