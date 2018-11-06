#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <sstream>

class Screen
{
  public:


    void setStatus (bool);
	bool getStatus ();
    pid_t getPid();
    void setPid(pid_t);
    std::string getFilename();
    void createScreenFilename();
	Screen (bool);

	private:
		pid_t pid;
	  	bool active;
	  	std::string filename;
	  	static unsigned nextId;
	  	unsigned screenId;
};
