/*
snake.c
*/

#include <snake.h>

/* typedefs and structs */
typedef struct snake_node {
    int          x;
    int          y;
    int          alive;
    snake_node_t *next;
} snake_node_t;

typedef struct food {
    int x;
    int y;
    int eaten;
} food_t;


int main() {
    /* init random number generator */
    srand(time(NULL));

    /* start game */
    run();
    return 0;
}

/* run ... */
void run() {
    int max_x, max_y;

    /* init screen */
    initscr();
    noecho();
    curs_set(FALSE);

    /* init snake */
    snake_node_t *snake_head = malloc(sizeof(snake_node_t));
    assert(snake_head);
    snake_head->alive = 1;  /* make alive */

    /* set snake head location to centre of screen */
    snake_head->x = max_x / 2;
    snake_head->y = max_y / 2;

    /* init food */
    food_t *food = create_food(snake_head, max_x, max_y);

    /* set food location */
    food->x = rand() % max_x;
    food->y = rand() % max_y;

    /* begin program execution */
    while (1) {
        /* render objects */
        render_snake(snake_head);
        render_food(food);

        /* did food get eaten */
        eat_food(snake_head, food);
        if (food->eaten) {
            snake_grow(snake_head);                        /* grow snake */
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
void draw_screen() {
}


/* create_food ... */
food_t* create_food(snake_node_t *snake_head, int max_x, int max_y) {
    food_t *food = malloc(sizeof(food_t));  /* allocate memory */
    assert(food);

    /* set values */
    food->eaten = 0;
    food->x = rand() % max_x;
    food->y = rand() % max_y;

    return food;
}


/* render_snake ... */
void render_snake(snake_node_t *snake_head) {
}


/* render_food ... */
void render_food(food_t *food) {
}


/* grow_snake ... */
void grow_snake(snake_node_t *snake_head) {
}


/* free_snake ... */
void free_snake(snake_node_t *snake_head) {
}


/* check_for_collision ... */
void check_for_collision(snake_node_t *snake_head, int max_x, int max_y) {
}


/* eat_food ... */
void eat_food(snake_node_t *snake_head, food_t *food) {
    if (snake_head->x != food->x) {
        return;
    }

    if (snake_head->y != food->y) {
        return;
    }

    /* now we know there is a collision */
    food->eaten = 1;  /* change food status to eaten */
}