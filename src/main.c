#include <mlx.h>
#include <stdio.h>

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
    if (mlx == NULL)
    {
        printf("error: mlx_init() failed\n");
        return (1);
    }
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    (void)mlx_win;
	mlx_loop(mlx);
}
