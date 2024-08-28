#include "chat.h"

extern WINDOW *stdscr;
WINDOW *chatWindow;
WINDOW *usersWindow;
WINDOW *messageWindow;
extern char *serverPointer, *clientPointer;
extern sem_t *semid1, *semid2, *semid3, *semid4;
extern int exits;
extern char messageBuffer[100];

int nickCounter, chatCounter, clientCounter = 0;
struct winsize ws;

void *threadChat(void *args)
{
    while (exits != 1)
    {
        sem_wait(semid4);

        wmove(chatWindow, chatCounter, 1);
        chatCounter++;
        wprintw(chatWindow, "%s", clientPointer);
        
        if (clientPointer[0] == 'C' && clientPointer[1] == 'C')
        {
            wmove(usersWindow, nickCounter, 1);
            nickCounter++;
            wprintw(usersWindow, "%s", &clientPointer[14]);
        }

        if (clientPointer[8] == 'E' && clientPointer[9] == 'N' && clientPointer[10] == 'D')
            exits = 1;

        sem_post(semid3);

        wrefresh(chatWindow);
        wrefresh(usersWindow);
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