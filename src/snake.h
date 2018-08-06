#ifndef SNAKE_H_
#define SNAKE_H_

#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


/* constants */
#define SNAKE_START_LEN 1
#define TICK_SPEED      30000


/* typedefs */
typedef struct snake_node snake_node_t;
typedef struct food food_t;


/* function declarations */
void run();
void draw_screen();
void grow_snake(snake_node_t *snake_head);
void render_snake(snake_node_t *snake_head);
void render_food(food_t *food);


#endif  /* SNAKE_H_ */