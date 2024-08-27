#include "client.h"

extern WINDOW *stdscr;
WINDOW *chatWindow;
WINDOW *usersWindow;
WINDOW *messageWindow;
struct winsize ws;
extern char messageBuffer[100];
extern char chatBuffer[100];
extern int exits;
extern int chatCounter;
extern mqd_t mqdReadServer, mqdWriteServer;

void *threadChat(void *args)
{
    unsigned int prio;
    while(exits != 1)
    {
        if(chatCounter > ws.ws_row - 8)
        {
            refreshWindow();
            chatCounter = 1;
        }

        if(mq_receive(mqdWriteServer, chatBuffer, 150, &prio) == -1)
        {
            wmove(messageWindow, 3, 1);
            wprintw(messageWindow, "receive client error");
            sleep(2);
        }
        else
        {
            wmove(chatWindow, chatCounter, 1);
            wprintw(chatWindow, "%s", chatBuffer);
            chatBuffer[0] = '\000';
            chatCounter++;
        }

        wrefresh(chatWindow);
    }

    return 0;
}

void refreshMessage()
{
    delwin(messageWindow);

    messageWindow = newwin(5, ws.ws_col, ws.ws_row - 5, 0);
    wbkgd(messageWindow, COLOR_PAIR(2));
    box(messageWindow, 0, 0);
    wmove(messageWindow, 2, 1);
    wprintw(messageWindow, "/q - quit");
    wmove(messageWindow, 1, 1);
    wprintw(messageWindow, "%s", messageBuffer);

    wrefresh(messageWindow);
}

void sigWinchHandler(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    refreshWindow();
}

void initGraph()
{
    initscr();

    signal(SIGWINCH, sigWinchHandler);
    cbreak();
    curs_set(1);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    refresh();

    refreshWindow();
}

void refreshWindow()
{
    deleteWindows();

    chatCounter = 1;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    chatWindow = newwin(ws.ws_row - 5, ws.ws_col - 22, 0, 0);
    usersWindow = newwin(ws.ws_row - 5, 22, 0, ws.ws_col - 22);
    wbkgd(chatWindow, COLOR_PAIR(1));
    wbkgd(usersWindow, COLOR_PAIR(1));

    box(chatWindow, 0, 0);
    box(usersWindow, 0, 0);

    move(ws.ws_row - 4, 1);

    wrefresh(chatWindow);
    wrefresh(usersWindow);
    refreshMessage();
    refresh();
}

void deleteWindows()
{
    delwin(chatWindow);
    delwin(usersWindow);
    delwin(messageWindow);
}

void endGraph()
{
    deleteWindows();
    endwin();
}