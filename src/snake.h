#ifndef SNAKE_H_
#define SNAKE_H_

#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>


/* constants */
#define SNAKE_START_LEN 1
#define TICK_SPEED      30000


/* typedefs */
typedef struct location location_t;
typedef struct snake_node snake_node_t;
typedef struct food food_t;


/* function declarations */
void    run();
void    draw_screen();
food_t* create_food(snake_node_t *snake_head, int max_x, int max_y);
void    render_snake(snake_node_t *snake_head);
void    render_food(food_t *food);
void    move_snake(snake_node_t *snake_head);
void    grow_snake(snake_node_t *snake_head);
void    free_snake(snake_node_t *snake_head);
void    check_for_collision(snake_node_t *snake_head, int max_x, int max_y);
void    eat_food(snake_node_t *snake_head, food_t *food);


#endif  /* SNAKE_H_ */