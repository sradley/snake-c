#ifndef SNAKE_H_
#define SNAKE_H_

#define _DEFAULT_SOURCE

#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>


/* constants */
#define SNAKE_START_LEN 1
#define TICK_SPEED      200000  /* 0.2 sec in microsec */
#define LEFT            0
#define UP              1
#define RIGHT           2
#define DOWN            3


/* typedefs */
typedef struct location location_t;
typedef struct snake_node snake_node_t;
typedef struct food food_t;


/* function declarations */
void    run();
void    draw_screen(int max_x, int max_y);
food_t* create_food(snake_node_t *snake_head, int max_x, int max_y);
void    render_snake(snake_node_t *snake_head);
int     snake_len(snake_node_t *snake_head);
void    render_food(food_t *food);
void    move_snake(snake_node_t *snake_head, int direction);
void    grow_snake(snake_node_t *snake_head);
void    free_snake(snake_node_t *snake_head);
void    check_for_collision(snake_node_t *snake_head, int max_x, int max_y);
int     collides_with_self(snake_node_t *snake_head);
void    eat_food(snake_node_t *snake_head, food_t *food);


#endif  /* SNAKE_H_ */