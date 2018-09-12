#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "demo.h"
#include "3dgfx/3dgfx.h"
#include "3dgfx/mesh.h"
#include "3dgfx/polyfill.h"
#include "screen.h"
#include "cfgopt.h"
#include "gfxutil.h"

static int init(void);
static void destroy(void);
static void start(long trans_time);
static void draw(void);
static int gen_phong_tex(struct pimage *img, int xsz, int ysz, float sexp,
		float offx, float offy,	int dr, int dg, int db, int sr, int sg, int sb);

static struct screen scr = {
	"example",
	init,
	destroy,
	start, 0,
	draw
};

static float cam_theta = -29, cam_phi = 20;
static float cam_dist = 6;

static struct pimage phongtex;
static struct g3d_mesh torus;

struct screen *example_screen(void)
{
	return &scr;
}

#define PHONG_TEX_SZ	128

static int init(void)
{
	gen_phong_tex(&phongtex, PHONG_TEX_SZ, PHONG_TEX_SZ, 5.0f, 0, 0, 10, 50, 92, 192, 192, 192);

	if(gen_torus_mesh(&torus, 1.0f, 0.35, 16, 8) == -1) {
		return -1;
	}
	return 0;
}

static void destroy(void)
{
	free(phongtex.pixels);
}

static void start(long trans_time)
{
	g3d_matrix_mode(G3D_PROJECTION);
	g3d_load_identity();
	g3d_perspective(50.0f, 1.333333f, 0.5f, 100.0f);

	g3d_enable(G3D_CULL_FACE);
	g3d_enable(G3D_LIGHTING);
	g3d_enable(G3D_LIGHT0);
}

static void update(void)
{
	mouse_orbit_update(&cam_theta, &cam_phi, &cam_dist);
}

static void draw(void)
{
	float t = (float)time_msec / 10.0f;

	update();

	g3d_matrix_mode(G3D_MODELVIEW);
	g3d_load_identity();
	g3d_translate(0, 0, -cam_dist);
	g3d_rotate(cam_phi, 1, 0, 0);
	g3d_rotate(cam_theta, 0, 1, 0);
	if(opt.sball) {
		g3d_mult_matrix(sball_matrix);
	}

	memset(fb_pixels, 0, fb_width * fb_height * 2);

	/* draw floor */
	g3d_push_matrix();
	g3d_translate(0, -1, 0);

	g3d_disable(G3D_LIGHTING);
	g3d_polygon_mode(G3D_FLAT);

	g3d_begin(G3D_QUADS);
	g3d_color3b(80, 192, 80);
	g3d_vertex(-2, 0, 2);
	g3d_vertex(2, 0, 2);
	g3d_vertex(2, 0, -2);
	g3d_vertex(-2, 0, -2);
	g3d_end();

	g3d_enable(G3D_LIGHTING);
	g3d_pop_matrix();

	/* draw phong torus */
	g3d_push_matrix();
	g3d_translate(0, 0.35, 0);
	g3d_rotate(t, 0, 1, 0);
	g3d_rotate(t, 1, 0, 0);

	g3d_polygon_mode(G3D_TEX_GOURAUD);
	g3d_enable(G3D_TEXTURE_GEN);
	g3d_set_texture(phongtex.width, phongtex.height, phongtex.pixels);

	g3d_mtl_diffuse(1, 1, 1);

	zsort_mesh(&torus);
	draw_mesh(&torus);

	g3d_disable(G3D_TEXTURE_GEN);
	g3d_pop_matrix();

	swap_buffers(fb_pixels);
}

static int gen_phong_tex(struct pimage *img, int xsz, int ysz, float sexp,
		float offx, float offy,	int dr, int dg, int db, int sr, int sg, int sb)
{
	int i, j;
	float u, v, du, dv;
	uint16_t *pix;

	if(!(img->pixels = malloc(xsz * ysz * sizeof *pix))) {
		return -1;
	}
	pix = img->pixels;

	du = 2.0f / (float)(xsz - 1);
	dv = 2.0f / (float)(ysz - 1);

	v = -1.0f - offy;
	for(i=0; i<ysz; i++) {
		u = -1.0f - offx;
		for(j=0; j<xsz; j++) {
			float d = sqrt(u * u + v * v);
			float val = pow(cos(d * M_PI / 2.0f), sexp);
			int ival = abs(val * 255.0f);

			int r = dr + ival * sr / 256;
			int g = dg + ival * sg / 256;
			int b = db + ival * sb / 256;

			if(r > 255) r = 255;
			if(g > 255) g = 255;
			if(b > 255) b = 255;

			*pix++ = PACK_RGB16(r, g, b);

			u += du;
		}
		v += dv;
	}

	img->width = xsz;
	img->height = ysz;
	return 0;
}
