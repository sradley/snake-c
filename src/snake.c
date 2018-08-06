/*
snake.c
*/

/* TODO: implement draw_screen function */
/* TODO: implement render_snake function */
/* TODO: finish run function */
/* TODO: write function comments */

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


/* create_food ... */
food_t* create_food(snake_node_t *snake_head, int max_x, int max_y) {
    int locs_len, xy, i, j, c;

    food_t *food = malloc(sizeof(food_t));  /* allocate memory */
    assert(food);

    /* set values */
    food->eaten = 0;

    /* create array of possible location options */
    locs_len = max_x*max_y - snake_len(snake_head);
    location_t locs[locs_len];

    c = 0;
    for (i = 1; i < max_x-1; i++) {
        for (j = 1; j < max_y-1; j++) {
            if (!snake_contains_loc(snake_head, i, j)) {
                /* add valid location to loc in array */
                locs[c].x = i;
                locs[c].y = j;
                c++;
            }
        }
    }

    /* assign a valid value to food->loc */
    xy = rand() % locs_len;
    food->loc = locs[xy];

    return food;
}


/* render_snake ... */
void render_snake(snake_node_t *snake_head) {
}


/* snake_len ... */
int snake_len(snake_node_t *snake_head) {
    assert(snake_head);

    int len = 0;
    snake_node_t *cur = snake_head;

    while (cur->next != NULL) {
        len++;
    }

    return len;
}


/* snake_contains_loc */
int snake_contains_loc(snake_node_t *snake_head, int x, int y) {
    snake_node_t *cur = snake_head;

    while (cur->next != NULL) {
        if (cur->loc.x != x) continue;
        if (cur->loc.y != y) continue;
        return 1;
    }

    return 0;
}


/* render_food ... */
void render_food(food_t *food) {
}


/* move_snake ... */
void move_snake(snake_node_t *snake_head, int direction) {
    assert(snake_head);

    /* move head in direction */
    snake_node_t *prev = snake_head;
    switch(direction) {
        case LEFT:
            prev->loc.x--;  /* move left */
            break;
        case UP:
            prev->loc.y--;  /* move up */
            break;
        case RIGHT:
            prev->loc.x++;  /* move right */
            break;
        case DOWN:
            prev->loc.y++;  /* move down */
            break;
        default:
            exit(EXIT_FAILURE);  /* invalid direction */
    }

    /* return if cur->next doesn't exist */
    if (prev->next == NULL) return;
    snake_node_t *cur = prev->next;

    while (cur->next != NULL) {
        cur->loc.x = prev->loc.x;
        cur->loc.y = prev->loc.y;

        prev = cur;
        cur = cur->next;
    }
}


/* grow_snake appends a new snake_node_t to the end of snake */
void grow_snake(snake_node_t *snake_head) {
    snake_node_t *cur = snake_head;

    /* go to end of snake */
    while (cur->next != NULL) {
        cur = cur->next;
    }

    /* create node at cur->next */
    cur->next = malloc(sizeof(snake_node_t));
    assert(cur->next);

    cur->next->next = NULL;
}


/* free_snake ... */
void free_snake(snake_node_t *snake_head) {
    /* free each node in snake */
    snake_node_t *cur = snake_head;

    while (cur != NULL) {
        free(cur);
        cur = cur->next;
    }
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


/* collides_with_self ... */
int collides_with_self(snake_node_t *snake_head) {
    snake_node_t *cur = snake_head->next;

    while (cur->next != NULL) {
        if (cur->loc.x != snake_head->loc.x) continue;
        if (cur->loc.y != snake_head->loc.y) continue;
        return 1;
    }

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