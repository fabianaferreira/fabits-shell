#include <sys/types.h>
#include <unistd.h>

class Screen
{
  public:
    void setStatus (bool);
		bool getStatus ();
    pid_t getPid();
		Screen (pid_t, bool);

	private:
		pid_t pid;
	  bool active;
};
