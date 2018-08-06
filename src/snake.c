/*
snake.c
*/

#include <snake.h>

/* typedefs and structs */
typedef struct location {
    int x;
    int y;
} location_t;

typedef struct snake_node {
    location_t   loc;
    int          alive;
    snake_node_t *next;
} snake_node_t;

typedef struct food {
    location_t loc;
    int        eaten;
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
    int direction = 0;  /* 0 = left, 1 = up, 2 = right, 3 = down */

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
        render_snake(snake_head);
        render_food(food);

        /* move snake */
        move_snake(snake_head);

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
    int x, y;

    food_t *food = malloc(sizeof(food_t));  /* allocate memory */
    assert(food);

    /* set values */
    food->eaten = 0;

    /* create array or list of possible location options */

    x = rand() % max_x;  /* change max_x to array length */
    y = rand() % max_y;  /* change max_y to array lenght */

    /* set food->x to array_of_locations[x].x */
    food->loc.x = x;
    /* set food->y to array_of_locations[y].y */
    food->loc.y = y;

    return food;
}


/* render_snake ... */
void render_snake(snake_node_t *snake_head) {
}


/* render_food ... */
void render_food(food_t *food) {
}


/* move_snake ... */
void move_snake(snake_node_t *snake_head) {
}


/* grow_snake ... */
void grow_snake(snake_node_t *snake_head) {
}


/* free_snake ... */
void free_snake(snake_node_t *snake_head) {
}


/* check_for_collision ... */
void check_for_collision(snake_node_t *snake_head, int max_x, int max_y) {
    /* if !collides with left or right wall */
    if (snake_head->loc.x > 0 && snake_head->loc.x < max_x) return;
    /* if !collides with top or bottom wall */
    if (snake_head->loc.y > 0 && snake_head->loc.y < max_y) return;

    /* if !collides with self */
    if (!collides_with_self(snake_head)) return;

    snake_head->alive = 0;  /* snake is dead */
}


int collides_with_self(snake_node_t *snake_head) {
    return 0;
}


/* eat_food ... */
void eat_food(snake_node_t *snake_head, food_t *food) {
    if (snake_head->loc.x != food->loc.x) {
        return;
    }

    if (snake_head->loc.y != food->loc.y) {
        return;
    }

    /* now we know there is a collision */
    food->eaten = 1;  /* change food status to eaten */
}