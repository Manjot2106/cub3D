NAME := cub3D
BONUS_NAME := cub3D_bonus

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -lXfixes

LIBFTDIR := ./libft
MLX_DIR := ./mlx
OBJ_DIR := obj

LIBFT := $(LIBFTDIR)/libft.a
MLX := $(MLX_DIR)/libmlx.a

HEADERS := -I./includes -I$(LIBFTDIR) -I$(MLX_DIR)
MLX_FLAGS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

COMMON_SRCS = \
	src/main.c \
	src/events/key.c \
	src/init/init_game.c \
	src/init/init_mlx.c \
	src/init/init_player.c \
	src/parsing/parsing.c \
	src/parsing/read_file.c \
	src/parsing/parse_elements.c \
	src/parsing/parse_elements_utils.c \
	src/parsing/parse_color.c \
	src/parsing/parse_textures.c \
	src/parsing/extract_map.c \
	src/parsing/parse_map.c \
	src/parsing/validate_map.c \
	src/parsing/validate_closed_map.c \
	src/render/cast_ray.c \
	src/render/cast_ray2.c \
	src/render/cast_ray_doors.c \
	src/render/floor.c \
	src/render/wall.c \
	src/render/image.c \
	src/render/create_image.c \
	src/render/render_game.c \
	src/render/render_mandatory.c \
	src/texture/load_textures.c \
	src/events/setup.c \
	src/utils/free_map.c \
	src/utils/texture_free.c \
	src/utils/parsing_utils.c

MANDATORY_SRCS = \
	src/events/player_update.c \
	src/bonus_hooks_parse.c \
	src/bonus_hooks_events.c \
	src/bonus_hooks_events_utils.c \
	src/bonus_hooks_events_more.c \
	src/bonus_hooks_render.c

BONUS_ONLY_SRCS = \
	src_bonus/player_update_bonus.c \
	src_bonus/core/hooks_parse_bonus.c \
	src_bonus/core/hooks_events_bonus.c \
	src_bonus/core/hooks_render_bonus.c \
	src_bonus/core/hooks_rendrer_bonus2.c \
	src_bonus/render/minimap_utils_bonus.c \
	src_bonus/render/minimap_draw_bonus.c \
	src_bonus/render/minimap_bonus.c \
	src_bonus/raycasting/doors_bonus.c \
	src_bonus/raycasting/doors_update_bonus.c \
	src_bonus/raycasting/doors_setup_bonus.c \
	src_bonus/sprites/sprites_setup_bonus.c \
	src_bonus/sprites/sprites_sort_bonus.c \
	src_bonus/sprites/sprites_barrels_bonus.c \
	src_bonus/sprites/sprites_render_bonus.c \
	src_bonus/sprites/sprites_render_utils_bonus.c \
	src_bonus/sprites/sprites_pixel_bonus.c

SRCS = $(COMMON_SRCS) $(MANDATORY_SRCS)
BONUS_SRCS = $(COMMON_SRCS) $(BONUS_ONLY_SRCS)

OBJS := $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

BONUS_OBJS := \
	$(patsubst src/%.c,$(OBJ_DIR)/bonus/%.o,\
	$(filter src/%,$(BONUS_SRCS))) \
	$(patsubst src_bonus/%.c,$(OBJ_DIR)/bonus/%.o,\
	$(filter src_bonus/%,$(BONUS_SRCS)))

all: $(NAME)

mandatory: all

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) \
		-L$(LIBFTDIR) -lft \
		$(MLX_FLAGS) \
		-o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(MLX) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) \
		-L$(LIBFTDIR) -lft \
		$(MLX_FLAGS) \
		-o $(BONUS_NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: src_bonus/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

.PHONY: all mandatory bonus clean fclean re
