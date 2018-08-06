/*
game.c
*/

/* TODO: implement draw_screen function */
/* TODO: implement render_snake function */
/* TODO: finish run function */
/* TODO: write function comments */

#include <snake.h>


int main() {
    /* init random number generator */
    srand(time(NULL));

    /* start game */
    run();
    return 0;
}

/* run ... */
void run() {
    int max_x = 0;
    int max_y = 0;
    int direction = LEFT;

    /* init screen */
    initscr();
    noecho();
    curs_set(FALSE);

    /* init snake */
    snake_node_t *snake_head = malloc(sizeof(snake_node_t));
    assert(snake_head);
    snake_head->alive = 1;  /* make alive */

    /* set snake head location to centre of screen */
    snake_head->loc.x = max_x / 2;
    snake_head->loc.y = max_y / 2;

    /* init food */
    food_t *food = create_food(snake_head, max_x, max_y);

    /* begin program execution */
    while (1) {
        /* render objects */
        draw_screen(max_x, max_y);
        render_snake(snake_head);
        render_food(food);

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

        /* tick */
        usleep(TICK_SPEED);
    }

    /* free memory */
    free_snake(snake_head);
    free(food);
}


/* draw_screen ... */
void draw_screen(int max_x, int max_y) {
}


/* render_snake ... */
void render_snake(snake_node_t *snake_head) {
}


/* render_food ... */
void render_food(food_t *food) {
}