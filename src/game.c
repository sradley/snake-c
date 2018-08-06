/*
game.c
*/

/* TODO: finish run function */
/* TODO: write function comments */

#include <snake.h>
#include <stdio.h>


int main() {
    /* init random number generator */
    srand(time(NULL));

    /* start game */
    run();
    endwin();

    return 0;
}

/* run ... */
void run() {
    int max_x, max_y, ch, diff;
    clock_t begin;
    int direction = LEFT;  /* rand() % 4 */

    /* init screen */
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    getmaxyx(stdscr, max_y, max_x);
    WINDOW *win = draw_screen(max_x, max_y);

    /* init snake */
    snake_node_t *snake_head = malloc(sizeof(snake_node_t));
    assert(snake_head);
    snake_head->alive = 1;  /* make alive */
    snake_head->next= NULL;

    /* set snake head location to centre of screen */
    snake_head->loc.x = max_x / 2;
    snake_head->loc.y = max_y / 2;

    /* init food */
    food_t *food = create_food(snake_head, max_x, max_y);

    /* begin program execution */
    while (1) {
        /* start timer */
        begin = clock();

        /* check for input */
        ch = wgetch(win);
        switch(ch) {
            case KEY_LEFT:
                direction = LEFT;
                break;
            case KEY_UP:
                direction = UP;
                break;
            case KEY_RIGHT:
                direction = RIGHT;
                break;
            case KEY_DOWN:
                direction = DOWN;
                break;
            default:
                break;
        }

        /* render objects */
        wclear(win);
        win = draw_screen(max_x, max_y);
        render_snake(snake_head, win);
        render_food(food, win);
        wrefresh(win);

        /* move snake */
        move_snake(snake_head, direction);

        /* did food get eaten */
        eat_food(snake_head, food);
        if (food->eaten) {
            grow_snake(snake_head);                        /* grow snake */
            free(food);                                    /* free old food */
            food = create_food(snake_head, max_x, max_y);  /* create food */
        }

        /* did snake hit itself or a wall */
        check_for_collision(snake_head, max_x, max_y);
        if (!snake_head->alive) {
            break;
        }

        /* calculate time diff */
        diff = (int)(clock() - begin);

        /* tick */
        usleep(TICK_SPEED - diff*10);
    }

    /* free memory */
    free_snake(snake_head);
    free(food);
}


/* draw_screen .. */
WINDOW* draw_screen(int max_x, int max_y) {
    /* init window */
    WINDOW *win = newwin(max_y-2, max_x-2, 1, 1);
    keypad(win, TRUE);
    wtimeout(win, 5);

    /* draw box */
    box(win, 0, 0);
    touchwin(win);

    return win;
}


/* render_snake ... */
void render_snake(snake_node_t *snake_head, WINDOW *win) {
    snake_node_t *cur = snake_head;
    while (cur != NULL) {
        mvwaddch(win, cur->loc.y, cur->loc.x, 'S');
        cur = cur->next;
    }
}


/* render_food ... */
void render_food(food_t *food, WINDOW *win) {
    mvwaddch(win, food->loc.y, food->loc.x, 'F');
}