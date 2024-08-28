#include "chat.h"

extern WINDOW *stdscr;
WINDOW *chatWindow;
WINDOW *usersWindow;
WINDOW *messageWindow;

extern char *serverPointer, *clientPointer;
extern int temp;
extern sem_t *semid1, *semid2, *semid3, *semid4;

int nickCounter, chatCounter, clientCounter = 0;
struct winsize ws;

void *threadChat(void *args)
{
    while (temp != 113)
    {
        sem_wait(semid2);

        for (int i = 0; serverPointer[i] != '\n' && i <= 500; i++)
        {
            clientPointer[i] = serverPointer[i];
        }
        
        if (serverPointer[0] == 'C' && serverPointer[1] == 'C')
        {
            clientCounter++;
            nickCounter++;
            wmove(usersWindow, nickCounter, 1);
            wprintw(usersWindow, "%s", &serverPointer[14]);
        }

        if (serverPointer[0] == 'C' && serverPointer[1] == 'D' && clientCounter != 0)
            clientCounter--;
        
        wmove(chatWindow, chatCounter, 1);
        wprintw(chatWindow, "%s", clientPointer);
        chatCounter++;
        sem_post(semid1);
        
        for (int i = 0; i < clientCounter; i++)
        {
            sem_post(semid4);
            sem_wait(semid3);
        }

        serverPointer[0] = '\000';
        clientPointer[0] = '\000';

        wrefresh(chatWindow);
        wrefresh(usersWindow);
    }

    return 0;
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
    curs_set(0);
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
    nickCounter = 1;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    chatWindow = newwin(ws.ws_row - 5, ws.ws_col - 22, 0, 0);
    usersWindow = newwin(ws.ws_row - 5, 22, 0, ws.ws_col - 22);
    messageWindow = newwin(5, ws.ws_col, ws.ws_row - 5, 0);
    wbkgd(chatWindow, COLOR_PAIR(1));
    wbkgd(usersWindow, COLOR_PAIR(1));
    wbkgd(messageWindow, COLOR_PAIR(2));

    wmove(chatWindow, chatCounter, 1);
    
    wmove(messageWindow, 1, 1);
    wprintw(messageWindow, "q - quit \n c - clean");

    box(chatWindow, 0, 0);
    box(usersWindow, 0, 0);
    box(messageWindow, 0, 0);

    wrefresh(chatWindow);
    wrefresh(usersWindow);
    wrefresh(messageWindow);
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