/*
game.c
*/

/* TODO: write function comments */

#include <snake.h>


int main(void) {
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
    int score = 0;
    int i = 1;
    clock_t begin;
    int direction = rand() % 4;

    /* init screen */
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    getmaxyx(stdscr, max_y, max_x);

    /* add screen text */
    mvwprintw(stdscr, 0, 1, "snake-c 0.0.1");
    mvwprintw(stdscr, max_y-1, max_x-21, "press ctrl-C to quit");
    mvwprintw(stdscr, max_y-1, 1, "score: %d", score);
    refresh();

    /* init window */
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

        move_snake(snake_head, direction);

        /* render objects */
        wclear(win);
        win = draw_screen(max_x, max_y);
        render_snake(snake_head, win, max_x, max_y);
        render_food(food, win);
        wrefresh(win);

        /* did food get eaten */
        eat_food(snake_head, food);
        if (food->eaten) {
            grow_snake(snake_head);                        /* grow snake */
            free(food);                                    /* free old food */
            food = create_food(snake_head, max_x, max_y);  /* create food */

            score++;
            mvwprintw(stdscr, max_y-1, 1, "score: %d", score);
            refresh();
        }

        /* keep growing until size of SNAKE_START_LEN */
        if (i < SNAKE_START_LEN) {
            grow_snake(snake_head);
            i++;
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
    wtimeout(win, 1);

    /* draw box */
    box(win, 0, 0);
    touchwin(win);

    return win;
}


/* render_snake ... */
void render_snake(snake_node_t *snake_head, WINDOW *win, int max_x, int max_y) {
    char ch[1] = {(char)219};

    wattron(win, COLOR_PAIR(2));

    snake_node_t *cur = snake_head;
    while (cur != NULL) {
        if (cur->loc.y && cur->loc.x && cur->loc.y < max_y-3 && cur->loc.x < max_x-3) {
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