#ifndef SNAKE_GAME_H_
#define SNAKE_GAME_H_

#define _DEFAULT_SOURCE
#define NCURSES_NO_UTF8_ACS

#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>


/* constants */
#define TICK_SPEED      70000  /* 0.1 sec in microsec */
#define LEFT            0
#define UP              1
#define RIGHT           2
#define DOWN            3


/* typedefs */
typedef struct location location_t;
typedef struct snake_node snake_node_t;
typedef struct food food_t;


/* structs */
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


/* function declarations */
/* game logic */
void    run();
WINDOW* draw_screen(int max_x, int max_y);
void    render_food(food_t *food, WINDOW *win);
void    render_snake(snake_node_t *snake_head, WINDOW *win);

/* snake functions */
int  snake_len(snake_node_t *snake_head);
int  snake_contains_loc(snake_node_t *snake_head, int x, int y);
void move_snake(snake_node_t *snake_head, int direction);
void grow_snake(snake_node_t *snake_head);
void check_for_collision(snake_node_t *snake_head, int max_x, int max_y);
int  collides_with_self(snake_node_t *snake_head);
void free_snake(snake_node_t *snake_head);

/* food functions */
food_t* create_food(snake_node_t *snake_head, int max_x, int max_y);
void    eat_food(snake_node_t *snake_head, food_t *food);


#endif  /* SNAKE_GAME_H_ */