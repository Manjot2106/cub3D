/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:57:23 by msingh            #+#    #+#             */
/*   Updated: 2026/06/18 13:39:09 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_W 1200
# define WIN_H 900
# define FOV_RAD 1.0471975511965976
# define MINIMAP_SIZE 220
# define MINIMAP_MARGIN 20
# define RAY_COUNT 84
# define HIT_X 0
# define HIT_Y 1
# define RGB_ERROR "RGB must be positive integers between 0 and 255"
# define BARREL_ANIM_SPEED 1.25
# define BARREL_FRAME_COUNT 8
# define DOOR_FRAME_COUNT 8
# define DOOR_HIT_MARGIN 0.0
# define BAD_MAP_FILE_ERROR "Unable to read file: empty/not found/permissions"
# define MAP_ERROR_MEMOIRE "Memory allocation failed while parsing map"
# define MOUSE_SENSITIVITY 0.001

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef int				(*t_mlx_cb)(void);
typedef struct s_player	t_player;

typedef struct s_door
{
	int					x;
	int					y;
	double				progress;
	int					target_open;
}						t_door;

typedef struct s_sprite
{
	double				x;
	double				y;
	double				dist;
	double				anim;
	int					map_x;
	int					map_y;
	int					state;
}						t_sprite;

typedef struct s_sprite_draw
{
	double				transform_x;
	double				transform_y;
	int					screen_x;
	int					height;
	int					width;
	int					start_y;
	int					end_y;
	int					start_x;
	int					end_x;
}						t_sprite_draw;
typedef struct s_reader
{
	int					count;
	char				*line;
	char				**tmp;
}						t_reader;

typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
}						t_mlx;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
	int					hex;
}						t_color;

typedef struct s_config
{
	char				*north;
	char				*south;
	char				*east;
	char				*west;
	t_color				floor;
	t_color				ceiling;
}						t_config;

typedef struct s_check
{
	int					no;
	int					so;
	int					we;
	int					ea;
	int					f;
	int					c;
}						t_check;

typedef struct s_texture
{
	void				*img_ptr;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_len;
	int					endian;
}						t_texture;

typedef struct s_game
{
	char				**map;
	char				**file_lines;
	int					map_height;
	int					map_width;
	int					player_count;
	int					map_x;
	int					map_y;
	int					map_row;
	int					map_cols;
	int					map_max_x;
	int					map_max_y;
	int					map_pos;
	t_mlx				*mlx;
	t_player			*player;
	t_texture			wall_tex;
	t_texture			wall_no_tex;
	t_texture			wall_so_tex;
	t_texture			wall_we_tex;
	t_texture			wall_ea_tex;
	t_texture			ground_tex;
	t_texture			frame_tex;
	t_texture			door_frames[DOOR_FRAME_COUNT];
	t_texture			barrel_frames[BARREL_FRAME_COUNT];
	t_door				*doors;
	t_sprite			*sprites;
	double				zbuffer[WIN_W];
	int					door_count;
	int					sprite_count;
	t_config			config;
	char				*error_msg;
}						t_game;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				new_pos_x;
	double				new_pos_y;
	double				dir_x;
	double				dir_y;
	double				angle;
	bool				key_up;
	bool				key_down;
	bool				key_left;
	bool				key_right;
	bool				key_turn_left;
	bool				key_turn_right;
	double				last_frame_time;
	int					mouse_prev_x;
	bool				mouse_init;
}						t_player;

typedef struct s_raycast
{
	double				ray_x;
	double				ray_y;
	double				delta_x;
	double				delta_y;
	double				side_x;
	double				side_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
}						t_raycast;

typedef struct s_ray_hit
{
	double				dist;
	double				wall_x;
	double				ray_x;
	double				ray_y;
	int					side;
	int					map_x;
	int					map_y;
	int					is_door;
}						t_ray_hit;

typedef struct s_minimap
{
	int					origin_x;
	int					origin_y;
	int					cell_size;
	int					width;
	int					height;
}						t_minimap;

typedef struct s_floor_cast
{
	double				ray_x0;
	double				ray_y0;
	double				ray_x1;
	double				ray_y1;
	double				row_dist;
	double				step_x;
	double				step_y;
	double				floor_x;
	double				floor_y;
}						t_floor_cast;

typedef struct s_wall_draw
{
	int					x;
	int					y;
	int					line_h;
	int					start;
	int					end;
	int					tex_x;
	int					tex_y;
	int					color;
	double				step;
	double				tex_pos;
	t_texture			*tex;
}						t_wall_draw;

typedef struct s_rect
{
	int					x;
	int					y;
	int					w;
	int					h;
	int					color;
}						t_rect;

typedef struct s_line
{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					e2;
}						t_line;

/* init */
void					init_game(t_game *game);
void					ft_mlx(t_mlx *mlx);
void					init_mlx(t_game *game);

/* parsing */
t_game					*ft_parsing(char *map_path);
char					**read_file(char *path);
char					**append_line(char **lines, int count, char *line);
int						parse_color(char *line, t_game *game, t_check *check);
int						parse_texture(char *line, t_game *game, t_check *check);
int						check_texture_file(char *path);
int						validate_textures(t_game *game);
int						parse_elements(t_game *game);
int						is_texture_identifier(char *line);
int						find_map_start(char **file);
int						check_map_is_last(char **file, int start);
int						is_map_char(char c);
int						extract_map(t_game *game);
int						validate_closed_map(t_game *game);
int						validate_map(t_game *game);
int						is_color_identifier(char *line);

/* free */
void					free_map_lines(char **lines);
void					free_game(t_game *game);
void					free_exit(t_game *game, int exit_code);

/* player */
int						init_player_data(t_game *game);
int						set_spawn_from_map(t_game *game);
void					update_player(t_game *game, double dt);

/* render / textures */
void					put_pixel_to_frame(t_game *game, int x, int y,
							int color);
int						get_texture_pixel(t_texture *tex, int x, int y);
int						is_wall_cell(t_game *game, int map_x, int map_y);
void					cast_ray(t_game *game, double angle, t_ray_hit *hit);
void					cast_ray_skip_hit(t_game *game, double angle,
							t_ray_hit *hit, t_ray_hit *skip);
void					cast_ray_with_skip(t_game *game, double angle,
							t_ray_hit *hit, t_ray_hit *skip);
int						try_hit_door(t_game *game, t_raycast *ray,
							t_ray_hit *hit);
void					init_ray(t_game *game, double angle, t_raycast *ray);
void					draw_floor_perspective(t_game *game);
void					draw_wall_column(t_game *game, int x, t_ray_hit *hit,
							double dist);
int						darken_color(int color);
t_texture				*select_wall_texture(t_game *game, t_ray_hit *hit);
int						create_image_buffer(t_game *game);
int						load_textures(t_game *game);
int						render_first_frame(t_game *game);
void					draw_background(t_game *game);
void					draw_3d_view(t_game *game);
void					draw_behind_door(t_game *game, int x, double ray_angle,
							t_ray_hit *door_hit);
double					get_corrected_dist(t_game *game, double ray_angle,
							double dist);
/* events */
double					get_time_seconds(void);
int						key_press(int key, void *param);
int						release(int key, void *param);
int						mouse_move(int x, int y, void *param);
int						game_loop(void *param);
int						setup_hooks(t_game *game);

/* utils */
char					*skip_space(char *line);
void					trim_end(char *str);
int						is_number(char *str);
char					*get_value(char *line, int n);
int						err_msg(char *path, char *message);

/* texture helpers */
int						load_game_texture(t_game *game, t_texture *tex,
							char *path);
void					destroy_game_texture(t_game *game, t_texture *tex);

/* extension hooks */
int						bonus_is_map_start(char *line);
int						bonus_is_map_char(char c);
int						bonus_is_walkable(char c);
int						bonus_key_press(t_game *game, int key);
int						setup_bonus_features(t_game *game);
void					setup_bonus_hooks(t_game *game);
int						load_bonus_textures(t_game *game);
void					free_bonus_data(t_game *game);
int						bonus_is_blocking_cell(t_game *game, int map_x,
							int map_y);
t_texture				*bonus_select_texture(t_game *game, t_ray_hit *hit);
t_texture				*select_door_frame(t_game *game, t_ray_hit *hit);
void					draw_bonus_overlay(t_game *game);
int						bonus_is_map_char(char c);

/* Bonus features */
int						is_transparent(int color);
int						setup_doors(t_game *game);
int						setup_sprites(t_game *game);
t_door					*get_door(t_game *game, int map_x, int map_y);
int						is_door_blocking(t_game *game, int map_x, int map_y);
void					toggle_door(t_game *game);
void					update_doors(t_game *game, double dt);
void					update_barrels(t_game *game, double dt);
int						bonus_is_barrel_blocking(t_game *game, int map_x,
							int map_y);
void					bonus_touch_barrel(t_game *game, int map_x, int map_y);
double					door_ease(double t);
int						is_door_vertical(t_game *game, int x, int y);
void					clamp_sprite_screen(t_sprite_draw *d);
double					get_sprite_scale(t_sprite *sprite);
int						get_sprite_pixel(t_game *game, t_sprite_draw *d,
							t_sprite *sprite, int pos[2]);
void					draw_sprites(t_game *game);
void					sort_sprites(t_game *game);
void					draw_box(t_game *game, t_rect *box);
void					draw_line(t_game *game, int p[4], int color);
void					draw_map_layer(t_game *game, t_minimap *m);
void					draw_player_dir(t_game *game, int px, int py, int size);
void					draw_rays(t_game *game, int size, int off_x, int off_y);
void					draw_player_marker(t_game *game, int size, int off_x,
							int off_y);
void					draw_minimap(t_game *game);
void					center_mouse(t_game *game);
char					*get_barrel_frame_path(int index);
char					*get_door_frame_path(int index);
#endif
