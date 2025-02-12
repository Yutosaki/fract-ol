#include "fractol.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

static void put_pixel(char* data, t_point p, int color, int size_line, int bpp)
{
    int index;

    index = p.y * size_line + p.x * (bpp / 8);
    *(int *)(data + index) = color;
}

static int calc_mandelbrot(double c_re, double c_im, t_env* env)
{
    int iter;
    double zx;
    double zy;
    double tmp;

    iter = 0;
    zx = 0;
    zy = 0;
    while ((zx * zx + zy * zy) < 4 && iter < MAX_ITER)
    {
        tmp = zx * zx - zy * zy + c_re;
        zy = 2 * zx * zy + c_im;
        zx = tmp;
        iter++;
    }
    if (iter == MAX_ITER)
        return 0x000000;
    return ((((iter * 0xFFFFFF) / MAX_ITER) + env->color_offset) & 0xFFFFFF);
}

static void render_mandelbrot_line(int y, t_env* env, char* data, int size_line, int bpp)
{
    t_point p;
    int color;
    double c_re;
    double c_im;

    p.y = y;
    p.x = 0;
    while (p.x < WIDTH)
    {
        c_re = p.x * (env->scale / WIDTH) + env->offset_re;
        c_im = p.y * (env->scale / HEIGHT) + env->offset_im;
        color = calc_mandelbrot(c_re, c_im, env);
        put_pixel(data, p, color, size_line, bpp);
        p.x++;
    }
}

static void render_mandelbrot_lines(t_env* env, char* data, int size_line, int bpp)
{
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        render_mandelbrot_line(y, env, data, size_line, bpp);
        y++;
    }
}

void render_mandelbrot(t_env* env)
{
    void* img;
    char* data;
    int bpp;
    int size_line;
    int endian;

    img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    render_mandelbrot_lines(env, data, size_line, bpp);
    mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
    mlx_destroy_image(env->mlx, img);
}

static int calc_julia(double zx, double zy, t_julia* julia, t_env* env)
{
    int iter;
    double tmp;

    iter = 0;
    while ((zx * zx + zy * zy) < 4 && iter < MAX_ITER)
    {
        tmp = zx * zx - zy * zy + julia->c_re;
        zy = 2 * zx * zy + julia->c_im;
        zx = tmp;
        iter++;
    }
    if (iter == MAX_ITER)
        return 0x000000;
    return ((((iter * 0xFFFFFF) / MAX_ITER) + env->color_offset) & 0xFFFFFF);
}

static void render_julia_line(int y, t_env* env, t_julia* julia, char* data, int size_line, int bpp)
{
    t_point p;
    int color;
    double zx;
    double zy;

    p.y = y;
    p.x = 0;
    while (p.x < WIDTH)
    {
        zx = p.x * (env->scale / WIDTH) + env->offset_re;
        zy = p.y * (env->scale / HEIGHT) + env->offset_im;
        color = calc_julia(zx, zy, julia, env);
        put_pixel(data, p, color, size_line, bpp);
        p.x++;
    }
}

static void render_julia_lines(t_env* env, t_julia* julia, char* data, int size_line, int bpp)
{
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        render_julia_line(y, env, julia, data, size_line, bpp);
        y++;
    }
}

void render_julia(t_env* env, t_julia* julia)
{
    void* img;
    char* data;
    int bpp;
    int size_line;
    int endian;

    img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    render_julia_lines(env, julia, data, size_line, bpp);
    mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
    mlx_destroy_image(env->mlx, img);
}

static int calc_burning_ship(double c_re, double c_im, t_env* env)
{
    int iter;
    double zx;
    double zy;
    double tmp;

    iter = 0;
    zx = 0;
    zy = 0;
    while ((zx * zx + zy * zy) < 4 && iter < MAX_ITER)
    {
        tmp = zx * zx - zy * zy + c_re;
        zy = fabs(2 * zx * zy) + c_im;
        zx = fabs(tmp);
        iter++;
    }
    if (iter == MAX_ITER)
        return 0x000000;
    return ((((iter * 0xFFFFFF) / MAX_ITER) + env->color_offset) & 0xFFFFFF);
}

static void render_burning_ship_line(int y, t_env* env, char* data, int size_line, int bpp)
{
    t_point p;
    int color;
    double c_re;
    double c_im;

    p.y = y;
    p.x = 0;
    while (p.x < WIDTH)
    {
        c_re = p.x * (env->scale / WIDTH) + env->offset_re;
        c_im = p.y * (env->scale / HEIGHT) + env->offset_im;
        color = calc_burning_ship(c_re, c_im, env);
        put_pixel(data, p, color, size_line, bpp);
        p.x++;
    }
}

static void render_burning_ship_lines(t_env* env, char* data, int size_line, int bpp)
{
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        render_burning_ship_line(y, env, data, size_line, bpp);
        y++;
    }
}

void render_burning_ship(t_env* env)
{
    void* img;
    char* data;
    int bpp;
    int size_line;
    int endian;

    img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    render_burning_ship_lines(env, data, size_line, bpp);
    mlx_put_image_to_window(env->mlx, env->win, img, 0, 0);
    mlx_destroy_image(env->mlx, img);
}
