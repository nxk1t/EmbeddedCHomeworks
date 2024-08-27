#include "server.h"

extern WINDOW *stdscr;
WINDOW *chatWindow;
WINDOW *usersWindow;
WINDOW *messageWindow;
struct winsize ws;
extern int userCounter, chatCounter, temp;
extern char chatBuffer[100];
extern char userBuffer[50];
extern mqd_t mqdReadServer, mqdWriteServer;

void *threadChat(void *args)
{
    unsigned int prio;
    char test_array[110];

    if(mq_receive(mqdWriteServer, test_array, 150, &prio) == -1)
    {
            wmove(chatWindow, 10, 1);
            wprintw(chatWindow, "first receive server error");
    }

    while(temp != 113)
    {
        if(chatCounter > ws.ws_row - 8) refreshWindow();

        if(mq_receive(mqdReadServer, chatBuffer, 150, &prio) == -1)
        {
            wmove(messageWindow, 3, 1);
            wprintw(messageWindow, "receive server error");
            sleep(3);
        }

        if(chatBuffer[0] == '1' || chatBuffer[0] == '2')
        {
            wmove(chatWindow, 1, 10);
            wprintw(chatWindow, "%s", &chatBuffer[2]);
        }
        else if(chatBuffer[0] == '3')
        {
            wmove(chatWindow, chatCounter, 1);
            wprintw(chatWindow, "%s", &chatBuffer[2]);
            wmove(usersWindow, userCounter, 1);
            wprintw(usersWindow, "%s", &chatBuffer[12]);
            chatCounter++;
            userCounter++;
        }
        else if(chatBuffer[0] == '4')
        {
            wmove(chatWindow, chatCounter, 1);
            wprintw(chatWindow, "%s", &chatBuffer[2]);
            chatCounter++;
            userCounter--;
        }
        else
        {
            wmove(chatWindow, chatCounter, 1);
            wprintw(chatWindow, "%s", &chatBuffer[2]);
            chatCounter++;
        }
        
        for(int i = 1; i < userCounter; i++)
        {
            if(mq_send(mqdWriteServer, &chatBuffer[2], 100, 1) == -1)
            {
                printf("send server error");
            }
        }
        chatBuffer[0] = '\000';

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
    userCounter = 1;

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