/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:58:43 by codespace         #+#    #+#             */
/*   Updated: 2023/11/24 13:07:16 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	ft_input(int key, void *param)
{
	double	moveSpeed = 0.5;
	double	rotSpeed = 0.1;
	t_data	*dt;
	
	dt = (t_data *)param;
	if ((key == 124 || key == 2))
	{
		double oldDirX = dt->pos_dir.dirX;
		dt->pos_dir.dirX = dt->pos_dir.dirX * cos(-rotSpeed) - dt->pos_dir.dirY * sin(-rotSpeed);
		dt->pos_dir.dirY = oldDirX * sin(-rotSpeed) + dt->pos_dir.dirY * cos(-rotSpeed);
		double oldPlaneX = dt->pos_dir.planeX;
		dt->pos_dir.planeX = dt->pos_dir.planeX * cos(-rotSpeed) - dt->pos_dir.planeY * sin(-rotSpeed);
		dt->pos_dir.planeY = oldPlaneX * sin(-rotSpeed) + dt->pos_dir.planeY * cos(-rotSpeed);
	}
	else if ((key == 123 || key == 0))
	{
		double oldDirX = dt->pos_dir.dirX;
		dt->pos_dir.dirX = dt->pos_dir.dirX * cos(rotSpeed) - dt->pos_dir.dirY * sin(rotSpeed);
		dt->pos_dir.dirY = oldDirX * sin(rotSpeed) + dt->pos_dir.dirY * cos(rotSpeed);
		double oldPlaneX = dt->pos_dir.planeX;
		dt->pos_dir.planeX = dt->pos_dir.planeX * cos(rotSpeed) - dt->pos_dir.planeY * sin(rotSpeed);
		dt->pos_dir.planeY = oldPlaneX * sin(rotSpeed) + dt->pos_dir.planeY * cos(rotSpeed);
	}
	else if ((key == 125 || key == 1))
	{
		if (worldMap[(int)(dt->pos_dir.posX - dt->pos_dir.dirX * moveSpeed)][(int)dt->pos_dir.posY] == 0)
			dt->pos_dir.posX -= dt->pos_dir.dirX * moveSpeed;
		if (worldMap[(int)dt->pos_dir.posX][(int)(dt->pos_dir.posY - dt->pos_dir.dirY * moveSpeed)] == 0)
			dt->pos_dir.posY -= dt->pos_dir.dirY * moveSpeed;
	}
	else if ((key == 126 || key == 13))
	{
		if (worldMap[(int)(dt->pos_dir.posX + dt->pos_dir.dirX * moveSpeed)][(int)dt->pos_dir.posY] == 0)
			dt->pos_dir.posX += dt->pos_dir.dirX * moveSpeed;
		if (worldMap[(int)dt->pos_dir.posX][(int)(dt->pos_dir.posY + dt->pos_dir.dirY * moveSpeed)] == 0)
			dt->pos_dir.posY += dt->pos_dir.dirY * moveSpeed;
	}
	else if (key == 53)
		ft_close(0, NULL);
	ft_update_img(dt);
	return (0);
}

int	main(void)
{
	t_data	dt;

	dt.mlx = mlx_init();
	dt.w = screenWidth;
	dt.h = screenHeight;
	dt.pos_dir.posX = 22;
	dt.pos_dir.posY = 16;  //x and y start position
	dt.pos_dir.dirX = -1;
	dt.pos_dir.dirY = 0; //initial direction vector
	dt.pos_dir.planeX = 0;
	dt.pos_dir.planeY = 0.66; //the 2d raycaster version of camera plane
	//double time = 0; //time of current frame
	//double oldTime = 0; //time of previous frame

	dt.mlx_w = mlx_new_window(dt.mlx, screenWidth, screenHeight, "Raycaster");
	ft_update_img(&dt);
	mlx_key_hook(dt.mlx_w, *ft_input, &dt);
	mlx_hook(dt.mlx_w, 17, 0, ft_close, NULL);
	mlx_loop(dt.mlx);
	return (0);
}