class Screen {
	pid_t pid;
    bool active;
  public:
    void set_values (pid_t, bool);
    pid_t pid() {return pid;}
};

void Screen::set_values (pid_t x, bool y) {
  pid = x;
  active = y;
}