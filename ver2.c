#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node {
    int xpos;
    int ypos;
    struct node* next;
}; //A linked list describing the points of the node of the snake

void startscreen(){
    //center of the screen
    int xcen = COLS/2;
    int ycen = LINES/2;
    clear();
    refresh();
    printf("The screen is %d rows, %d columns\n", LINES, COLS);
    move(ycen, xcen-12); //move() uses column, row
    addstr("Press any key to continue\n");
    refresh();
    getchar();
    clear();

}

void drawborder(){
    //center of the screen
    int xcen = COLS/2;
    int ycen = LINES/2;
    int margin = 3;  //so we don't have to change the margins in the border variables
    //next four lines is to keep the borders dynamic
    int nborder = margin;
    int sborder = LINES - margin;
    int wborder = margin;
    int eborder = COLS - margin;
    int drawspeed = 3000;  //so we don't have to change every single draw block speed
    //drawing the top border
    for(int n = 0; n < eborder-wborder; n++){
        move(nborder, wborder+n);
        addstr("x");
        refresh();
        usleep(drawspeed);
    }
    //drawing the right border
    for(int n = 0; n < sborder-nborder; n++){
        move(nborder+n, eborder);
        addstr("x");
        refresh();
        usleep(drawspeed);
    }
    //drawing the bottom border
    for(int n = 0; n < eborder-wborder; n++){
        move(sborder, eborder-n);
        addstr("x");
        refresh();
        usleep(drawspeed);
    }
    //drawing the left border
    for(int n = 0; n < sborder-nborder; n++){
        move(sborder-n, wborder);
        addstr("x");
        refresh();
        usleep(drawspeed);
    }
    //just fun text above and below the border
    move(nborder-2, xcen-11);
    addstr("Press any key to start!\n");
    move(sborder+2, xcen-13);
    addstr("Use the arrow keys to move");
    refresh();
    getchar();
}

int keystroke(){
    int ch = getch();
        switch (ch) {
            case KEY_UP:        // user pressed up arrow key 
                move(0,0);
                addstr("You pressed the UP arrow           ");
                return 0;
                break;
            case KEY_DOWN:      // user pressed down arrow key 
                move(0,0);
                addstr("You pressed the DOWN arrow         ");
                return 0;
                break;
            case KEY_LEFT:      // user pressed left arrow key 
                move(0,0);
                addstr("You pressed the LEFT arrow         ");
                return 0;
                break;
            case KEY_RIGHT:     // user pressed right arrow key 
                move(0,0);
                addstr("You pressed the RIGHT arrow        ");
                return 0;
                break;
            case 'x':           // pressing x or X will exit the program
            case 'X': 
                endwin();       // close curses
                return 1;       // in case of gameover screen, return 1 rather than just closing the window
            default:
                move(0,0);
                char buf[100];
                sprintf(buf,"You pressed a \"%c\" key, ASCI code %d       ", (char)ch, ch);
                addstr(buf);
                return 0;
                break;
            
        } 
}

int main(int ac, char*av[]){
    int speed = 1;
    //im not actually too sure if we need these declared in the main block just quite yet, but i added them just in case
    int xcen = COLS/2;
    int ycen = LINES/2;
    int margin = 3;  //so we don't have to change the margins in the border variables
    //next four lines is to keep the borders dynamic
    int nborder = margin;
    int sborder = LINES - margin;
    int wborder = margin;
    int eborder = COLS - margin;
    int gameover = 0;
    int victory = (COLS - 6) + (LINES -8); //Half the perimeter of the snake pit
    int count = 0; //current length of the snake (will grow to match the length)
    int length = 3; 
    //snake position
    struct node *head;  //the moving head of the snake
    head = (struct node *)malloc(sizeof(struct node));
    struct node *tail;  //the tail end of the snake
    tail = (struct node *)malloc(sizeof(struct node));
    struct node *temp;  
    temp = (struct node *)malloc(sizeof(struct node));
    tail->xpos = 119;
    tail->ypos = 7;
    tail->next = NULL;
    //switches to tell us which arrow key was pressed last
    int u = 0;
    int d = 0;
    int l = 0;
    int r = 1;

    if(ac == 2){
        speed = atoi(av[1]);
    }
    initscr(); //initialize the curses library
    startscreen();
    drawborder();
    //below this comment is the code for using the arrow keys and reading the key presses that he gave us
    curs_set(0);                // hide the cursor
    noecho();                   // do not echo user input to the screen
    keypad(stdscr, TRUE);       // enables workign with the arrow keys
    move(0,0);         
    addstr("Press any key....");

    
    move(tail->ypos, tail->xpos);
    addstr(">");
    refresh();
    sleep(1);
    while(!gameover) {
        temp = tail;
        while(temp->next != NULL)
            temp = temp->next;
        head->xpos = temp->xpos +1;
        head->ypos = temp->ypos;
        head->next = NULL;
        temp->next = head;
        move(head->ypos, head->xpos);
        addstr(">");
        refresh();
            move(0,0);
            char buf[100];
            sprintf(buf,"Head's position is (%d, %d)       ", head->xpos, head->ypos);
            addstr(buf);
            refresh();
        if(count < length){
            count ++;
        }/* 
        else{
            move(tail->ypos, tail->xpos);
            addstr("1");
            refresh();
            temp = tail->next;
            tail = temp;
            //free(temp);
            
        }
        */
        if(head->xpos >= 232){
            gameover = 1;
        }
        /*
        keystroke();
        */
        sleep(1);
        //usleep (250000);              
    }
    endwin(); //turn off curses
}