/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msingh <msingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:19:17 by msingh            #+#    #+#             */
/*   Updated: 2026/06/11 16:42:17 by msingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
}

static void	destroy_display_ptr(void *mlx_ptr)
{
	if (!mlx_ptr)
		return ;
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}

void	init_mlx(t_game *game)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		free_exit(game, 1);
	ft_mlx(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		free(mlx);
		free_exit(game, 1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "CUB3D");
	if (!mlx->win_ptr)
	{
		destroy_display_ptr(mlx->mlx_ptr);
		free(mlx);
		free_exit(game, 1);
	}
	game->mlx = mlx;
}
