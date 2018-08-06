/*
snake.c
*/

/* TODO: write function comments */

#include <snake.h>


/* snake_len ... */
int snake_len(snake_node_t *snake_head) {
    assert(snake_head);

    int len = 0;
    snake_node_t *cur = snake_head;

    while (cur != NULL) {
        len++;
        cur = cur->next;
    }

    return len;
}


/* snake_contains_loc */
int snake_contains_loc(snake_node_t *snake_head, int x, int y) {
    snake_node_t *cur = snake_head;

    while (cur->next != NULL) {
        if (cur->loc.x != x) {
            cur = cur->next;
            continue;
        }

        if (cur->loc.y != y) {
            cur = cur->next;
            continue;
        }

        return 1;
    }

    return 0;
}


/* move_snake ... */
void move_snake(snake_node_t *snake_head, int direction) {
    int prev_x, prev_y, tmp_x, tmp_y;
    assert(snake_head);

    /* move head in direction */
    snake_node_t *prev = snake_head;
    prev_x = prev->loc.x;
    prev_y = prev->loc.y;

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

    while (cur != NULL) {
        tmp_x = cur->loc.x;
        tmp_y = cur->loc.y;

        cur->loc.x = prev_x;
        cur->loc.y = prev_y;

        prev_x = tmp_x;
        prev_y = tmp_y;
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


/* check_for_collision ... */
void check_for_collision(snake_node_t *snake_head, int max_x, int max_y) {
    /* if collides with left or right wall */
    if (snake_head->loc.x < 0 || snake_head->loc.x >= max_x-2) {
        snake_head->alive = 0;
    }

    /* if collides with top or bottom wall */
    if (snake_head->loc.y < 0 || snake_head->loc.y >= max_y-2) {
        snake_head->alive = 0;
    }

    /* if collides with self */
    if (collides_with_self(snake_head)) {
        snake_head->alive = 0;
    }
}


/* collides_with_self ... */
int collides_with_self(snake_node_t *snake_head) {
    snake_node_t *cur = snake_head->next;

    while (cur != NULL) {
        if (cur->loc.x != snake_head->loc.x) {
            cur = cur->next;
            continue;
        }

        if (cur->loc.y != snake_head->loc.y) {
            cur = cur->next;
            continue;
        }

        return 1;
    }

    return 0;
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