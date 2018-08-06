/*
food.c
*/

/* TODO: write function comments */

#include <snake.h>


/* create_food ... */
food_t* create_food(snake_node_t *snake_head, int max_x, int max_y) {
    int locs_len, xy, i, j, c;

    food_t *food = malloc(sizeof(food_t));  /* allocate memory */
    assert(food);

    /* set values */
    food->eaten = 0;

    /* create array of possible location options */
    locs_len = (max_x-4)*(max_y-4) - snake_len(snake_head);
    location_t locs[locs_len];

    c = 0;
    for (i = 1; i < max_x-3; i++) {
        for (j = 1; j < max_y-3; j++) {
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