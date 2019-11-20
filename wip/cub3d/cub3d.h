/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:37:35 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 14:37:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>

# include "minilibx_mms_beta/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

# include "maths.h"
# include "keys.h"

# define WINDOW_NAME				"Hello World"

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_MOUSE_PRESS		4
# define X_EVENT_MOUSE_RELEASE		5
# define X_EVENT_MOUSE_MOVE			6
# define X_EVENT_EXIT				17

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define P_RESOLUTION "R"
# define P_TEX_NORTH "NO"
# define P_TEX_SOUTH "SO"
# define P_TEX_WEST "WE"
# define P_TEX_EAST "EA"
# define P_SPRITE "S"
# define P_FLOOR_COLOR "F"
# define P_ROOF_COLOR "C"

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define OBJ_EMPTY 0
# define OBJ_WALL 1
# define OBJ_OBJ 2
# define OBJ_PLAYER 3

# define E(error) ft_strdup(error)

# define PLAYER_ORIENTATION "NSEW"

# define MAX_WINDOW_WIDTH 640
# define MAX_WINDOW_HEIGHT 480

# define RENDER_SHOW_STATS 0

typedef struct		s_image
{
	void			*ptr;
	int				*pic;
	int				bpp;
	int				stride;
	int				endian;
	int				width;
	int				height;
	int				line_unit;
}					t_image;

typedef struct		s_game_object
{
	int				type;
	void			*data;
}					t_game_object;

typedef struct		s_map
{
	char			*file;
	t_vec2i			resolution;
	t_game_object	**objs;
	t_image			*wall_texs[4];
	t_image			*sprite;
	int				roof_color;
	int				floor_color;
	t_dim2i			size;
}					t_map;

typedef struct		s_mlx_context
{
	void			*mlx;
	void			*win;
	t_dim2i			w_dim;
	int				width;
	int				height;
}					t_mlx_context;

typedef struct		s_player_speed
{
	double			base;
	double			value;
}					t_player_speed;

typedef struct		s_player
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
	t_player_speed	move_speed;
	t_player_speed	rot_speed;
}					t_player;

typedef struct		s_engine
{
	t_mlx_context	ctx;
	char			*str;
	t_map			*map;
	t_player		player;
	t_image			*canvas;
	int				dirty;
	int				was_dirty;
}					t_engine;

typedef struct		s_ray_result
{
	int				line_height;
	int				start;
	int				end;
	int				obj_type;
}					t_ray_result;

typedef struct		s_ray
{
	int				x;
	t_engine		*engine;
	t_player		*player;
	t_vec2d			pos;
	int				width;
	int				height;
	t_vec2d			dir;
	t_vec2i			map;
	t_vec2d			step;
	t_vec2d			delta;
	double			perp_wall_dist;
	double			camera_x;
	t_vec2d			side_dist;
	int				side;
	int				hit;
	t_ray_result	out;
}					t_ray;

typedef struct		s_g_obj_data_player
{
	char			dir;
}					t_g_obj_data_player;

typedef	struct		s_drawer_line_args
{
	t_image			*image;
	int				color;
}					t_drawer_line_args;

int					engine_initialize(char *path, int save_arg);
void				*engine_hooks(t_engine *engine);
int					engine_loop(t_engine *engine);

int					engine_on_key_pressed(int keycode, t_engine *engine);
int					engine_on_key_released(int keycode, t_engine *engine);

int					engine_on_mouse_released(int button, int x, int y,
												t_engine *engine);
int					engine_on_mouse_pressed(int button, int x, int y,
												t_engine *engine);
int					engine_on_mouse_move(int x, int y, t_engine *engine);
int					engine_on_exit(t_engine *engine);

void				*engine_handle_error(char *error);

void				*mlx_context_initialize(t_mlx_context *context);
void				*mlx_window_initialize(t_mlx_context *context);
void				*mlx_canvas_initialize(t_engine *engine, t_map *map,
											t_image **canvas_ptr);

int					color_assemble(int red, int green, int blue);
void				color_dismentle(int color, int *red, int *green, int *blue);

t_map				*map_load(t_engine *eng, char *path);

char				*map_loader_set_color(char *key, char *colors,
											int *color_ptr);
char				*map_loader_set_resolution(char *key, char **resolutions,
											t_engine *eng);
char				*map_loader_set_sprite_texture(t_engine *eng, t_map *map,
											char *path);
char				*map_loader_set_wall_texture(t_engine *eng, t_map *map,
											char *key, char *path);

char				*map_loader_grid_bind_object(t_game_object *current,
												char *str);
char				*map_loader_grid_create_line(t_game_object **grid,
												t_map *map, char **split);
char				*map_loader_parse_grid(t_engine *eng, t_map *map,
											char **split);

int					map_is_empty_at(t_map *map, int x, int y);
int					map_get_object_type_at(t_map *map, int x, int y);
t_game_object		*map_get_object_at(t_map *map, int x, int y);

void				map_dump_object(t_game_object object);
void				map_dump(t_map *map);

t_image				*image_create(t_engine *eng, int width, int height);
t_image				*image_load(t_engine *eng, char *path);

void				image_clear(t_image *image);

void				image_get_pixel_raw(int rgb[], t_image *img, int x, int y);
void				image_set_pixel_raw(int rgb[], t_image *img, int x, int y);
int					image_get_pixel(t_image *image, int x, int y);
void				image_set_pixel(t_image *image, int x, int y, int color);
void				image_draw_vertical_line(t_drawer_line_args args, int x,
											int y_start, int y_end);

char				*player_initialize(t_engine *engine);

char				*player_init_set_position(t_map *map,
														t_player *player);
char				*player_init_set_direction(t_player *player,
													t_g_obj_data_player *data);
int					player_handle_mouvement(t_map *map, t_player *player);

void				render_scene(t_engine *engine);
void				render_scene_smart(t_engine *engine, int show_stats);
void				render_display_fps(t_engine *engine);

void				ray_render_scene(t_engine *engine);

void				ray_compute_initialize_struct(t_ray *ray_ptr,
													t_engine *engine);
void				ray_compute(t_ray *ray_ptr);
void				ray_compute_initialize(t_ray *ray);
void				ray_compute_find_side(t_ray *ray);
void				ray_compute_dda(t_ray *ray);
void				ray_compute_distance(t_ray *ray);
void				ray_compute_set_limits(t_ray *ray);

void				fps_counter_end(void);
void				fps_counter_start(void);
int					fps_counter_get(void);
double				fps_counter_get_tick(void);

int					mlx_put_image_to_window_scale(void *mlx_ptr, void *win_ptr,
													void *img_ptr,
													int sx, int sy,
													int sw, int sh,
													int dx, int dy,
													int dw, int dh,
													unsigned int color);

#endif