#include <curses.h>

int main(int argc, char** argv)
{
  initscr();

  printw("Main window");

  WINDOW* subwindow = newwin(10,20,5,5);



  box(subwindow,0,0);
  mvwprintw(subwindow, 1, 1, "subwindow");

  WINDOW* subwindow2 = newwin(10,20,15,15);



  box(subwindow2,0,0);
  mvwprintw(subwindow2, 1, 1, "subwindow2");


  refresh();
  wrefresh(subwindow2);
  wrefresh(subwindow);

  getch();
  delwin(subwindow);

  endwin();
  return 0;
}