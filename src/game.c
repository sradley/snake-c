/*
game.c
*/

/* TODO: add title and quit messages */
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

    /* init window */
    getmaxyx(stdscr, max_y, max_x);
    WINDOW *win = draw_screen(max_x, max_y);

    /* init color */
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);

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
                if (direction != RIGHT) direction = LEFT;
                break;
            case KEY_UP:
                if (direction != DOWN) direction = UP;
                break;
            case KEY_RIGHT:
                if (direction != LEFT) direction = RIGHT;
                break;
            case KEY_DOWN:
                if (direction != UP) direction = DOWN;
                break;
            default:
                break;
        }

        /* did snake hit itself or a wall */
        check_for_collision(snake_head, max_x, max_y);
        if (!snake_head->alive) {
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

        /* calculate time diff */
        diff = (int)(clock() - begin) / CLOCKS_PER_SEC;

        /* tick */
        usleep(TICK_SPEED - diff*1000000);
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
    char ch[1] = {(char)219};

    wattron(win, COLOR_PAIR(2));

    snake_node_t *cur = snake_head;
    while (cur != NULL) {
        if (cur->loc.y && cur->loc.x) {
            mvwprintw(win, cur->loc.y, cur->loc.x, ch);
        }
        cur = cur->next;
    }

    wattroff(win, COLOR_PAIR(2));
}


/* render_food ... */
void render_food(food_t *food, WINDOW *win) {
    char ch[1] = {(char)219};

    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, food->loc.y, food->loc.x, ch);
    wattroff(win, COLOR_PAIR(1));
}