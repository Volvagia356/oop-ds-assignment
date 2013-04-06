#include "winsize.hpp"

#ifdef unix
#include <sys/ioctl.h>
int getColumns() {
    winsize ws;
    ioctl(0,TIOCGWINSZ,&ws);
    return ws.ws_col;
}
#endif

#ifdef WINNT
#include <windows.h>
int getColumns() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    return csbi.dwSize.X;
}
#endif