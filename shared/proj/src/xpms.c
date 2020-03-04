#include "xpms.h"

extern dot_t pto;

int drawMainMenu()
{
	xpm_image_t menu;
  	uint8_t *map = xpm_load(main_menu_xpm, XPM_8_8_8, &menu);
  	if (map == NULL)
  		return 1;
  	draw_pix_map(menu, 0, 0);
	return 0;
}

int drawBackground()
{
	xpm_image_t bg;
    uint8_t *map = xpm_load(background_xpm, XPM_8_8_8, &bg);
    if (map == NULL)
    	return 1;
    draw_pix_map(bg, 0, 0);
    return 0;
}

int drawInstructions()
{
	xpm_image_t how_to;
    uint8_t *map = xpm_load(instructions_xpm, XPM_8_8_8, &how_to);
    if (map == NULL)
    	return 1;
    draw_pix_map(how_to, 0, 0);
    return 0;
}

int drawYouWin()
{
    xpm_image_t youwin;
    uint8_t *map = xpm_load(youwin_xpm, XPM_8_8_8, &youwin);
    if (map == NULL)
    	return 1;
    draw_pix_map(youwin, 0, 0);
    return 0;
}

int drawYouLose()
{
    xpm_image_t youlose;
    uint8_t *map = xpm_load(youlose_xpm, XPM_8_8_8, &youlose);
    if (map == NULL)
    	return 1;
    draw_pix_map(youlose, 0, 0);
    return 0;
}

int drawRedDot(uint32_t x_pos, uint32_t y_pos)
{
	uint8_t *map = xpm_load(dot_xpm, XPM_8_8_8, &pto.dot);
	if(map == NULL) return 1;
    draw_pix_map(pto.dot, pto.x_pos, pto.y_pos);
    return 0;
}

int drawSpace(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t space;
    uint8_t *map = xpm_load(space_xpm, XPM_8_8_8, &space);
    if (map == NULL) return 1;
    draw_pix_map(space, x_pos, y_pos);
    return 0;
}

int drawA(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t a;
    uint8_t *map = xpm_load(a_xpm, XPM_8_8_8, &a);
    if (map == NULL) return 1;
    draw_pix_map(a, x_pos, y_pos);
    return 0;
}
int drawB(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t b;
    uint8_t *map = xpm_load(b_xpm, XPM_8_8_8, &b);
    if (map == NULL) return 1;
    draw_pix_map(b, x_pos, y_pos);
    return 0;
}
int drawC(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t c;
    uint8_t *map = xpm_load(c_xpm, XPM_8_8_8, &c);
    if (map == NULL) return 1;
    draw_pix_map(c, x_pos, y_pos);
    return 0;
}
int drawD(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t d;
    uint8_t *map = xpm_load(d_xpm, XPM_8_8_8, &d);
    if (map == NULL) return 1;
    draw_pix_map(d, x_pos, y_pos);
    return 0;
}
int drawE(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t e;
    uint8_t *map = xpm_load(e_xpm, XPM_8_8_8, &e);
    if (map == NULL) return 1;
    draw_pix_map(e, x_pos, y_pos);
    return 0;
}
int drawF(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t f;
    uint8_t *map = xpm_load(f_xpm, XPM_8_8_8, &f);
    if (map == NULL) return 1;
    draw_pix_map(f, x_pos, y_pos);
    return 0;
}
int drawG(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t g;
    uint8_t *map = xpm_load(g_xpm, XPM_8_8_8, &g);
    if (map == NULL) return 1;
    draw_pix_map(g, x_pos, y_pos);
    return 0;
}
int drawH(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t h;
    uint8_t *map = xpm_load(h_xpm, XPM_8_8_8, &h);
    if (map == NULL) return 1;
    draw_pix_map(h, x_pos, y_pos);
    return 0;
}
int drawI(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t i;
    uint8_t *map = xpm_load(i_xpm, XPM_8_8_8, &i);
    if (map == NULL) return 1;
    draw_pix_map(i, x_pos, y_pos);
    return 0;
}
int drawJ(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t j;
    uint8_t *map = xpm_load(j_xpm, XPM_8_8_8, &j);
    if (map == NULL) return 1;
    draw_pix_map(j, x_pos, y_pos);
    return 0;
}
int drawK(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t k;
    uint8_t *map = xpm_load(k_xpm, XPM_8_8_8, &k);
    if (map == NULL) return 1;
    draw_pix_map(k, x_pos, y_pos);
    return 0;
}
int drawL(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t l;
    uint8_t *map = xpm_load(l_xpm, XPM_8_8_8, &l);
    if (map == NULL) return 1;
    draw_pix_map(l, x_pos, y_pos);
    return 0;
}
int drawM(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t m;
    uint8_t *map = xpm_load(m_xpm, XPM_8_8_8, &m);
    if (map == NULL) return 1;
    draw_pix_map(m, x_pos, y_pos);
    return 0;
}
int drawN(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n;
    uint8_t *map = xpm_load(n_xpm, XPM_8_8_8, &n);
    if (map == NULL) return 1;
    draw_pix_map(n, x_pos, y_pos);
    return 0;
}
int drawO(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t o;
    uint8_t *map = xpm_load(o_xpm, XPM_8_8_8, &o);
    if (map == NULL) return 1;
    draw_pix_map(o, x_pos, y_pos);
    return 0;
}
int drawP(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t p;
    uint8_t *map = xpm_load(p_xpm, XPM_8_8_8, &p);
    if (map == NULL) return 1;
    draw_pix_map(p, x_pos, y_pos);
    return 0;
}
int drawQ(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t q;
    uint8_t *map = xpm_load(q_xpm, XPM_8_8_8, &q);
    if (map == NULL) return 1;
    draw_pix_map(q, x_pos, y_pos);
    return 0;
}
int drawR(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t r;
    uint8_t *map = xpm_load(r_xpm, XPM_8_8_8, &r);
    if (map == NULL) return 1;
    draw_pix_map(r, x_pos, y_pos);
    return 0;
}
int drawS(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t s;
    uint8_t *map = xpm_load(s_xpm, XPM_8_8_8, &s);
    if (map == NULL) return 1;
    draw_pix_map(s, x_pos, y_pos);
    return 0;
}
int drawT(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t t;
    uint8_t *map = xpm_load(t_xpm, XPM_8_8_8, &t);
    if (map == NULL) return 1;
    draw_pix_map(t, x_pos, y_pos);
    return 0;
}
int drawU(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t u;
    uint8_t *map = xpm_load(u_xpm, XPM_8_8_8, &u);
    if (map == NULL) return 1;
    draw_pix_map(u, x_pos, y_pos);
    return 0;
}
int drawV(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t v;
    uint8_t *map = xpm_load(v_xpm, XPM_8_8_8, &v);
    if (map == NULL) return 1;
    draw_pix_map(v, x_pos, y_pos);
    return 0;
}
int drawW(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t w;
    uint8_t *map = xpm_load(w_xpm, XPM_8_8_8, &w);
    if (map == NULL) return 1;
    draw_pix_map(w, x_pos, y_pos);
    return 0;
}
int drawX(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t x;
    uint8_t *map = xpm_load(x_xpm, XPM_8_8_8, &x);
    if (map == NULL) return 1;
    draw_pix_map(x, x_pos, y_pos);
    return 0;
}
int drawY(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t y;
    uint8_t *map = xpm_load(y_xpm, XPM_8_8_8, &y);
    if (map == NULL) return 1;
    draw_pix_map(y, x_pos, y_pos);
    return 0;
}
int drawZ(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t z;
    uint8_t *map = xpm_load(z_xpm, XPM_8_8_8, &z);
    if (map == NULL) return 1;
    draw_pix_map(z, x_pos, y_pos);
    return 0;
}

int draw0(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n0;
    uint8_t *map = xpm_load(n0_xpm, XPM_8_8_8, &n0);
    if (map == NULL) return 1;
    draw_pix_map(n0, x_pos, y_pos);
    return 0;
}

int draw1(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n1;
    uint8_t *map = xpm_load(n1_xpm, XPM_8_8_8, &n1);
    if (map == NULL) return 1;
    draw_pix_map(n1, x_pos, y_pos);
    return 0;
}

int draw2(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n2;
    uint8_t *map = xpm_load(n2_xpm, XPM_8_8_8, &n2);
    if (map == NULL) return 1;
    draw_pix_map(n2, x_pos, y_pos);
    return 0;
}

int draw3(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n3;
    uint8_t *map = xpm_load(n3_xpm, XPM_8_8_8, &n3);
    if (map == NULL) return 1;
    draw_pix_map(n3, x_pos, y_pos);
    return 0;
}

int draw4(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n4;
    uint8_t *map = xpm_load(n4_xpm, XPM_8_8_8, &n4);
    if (map == NULL) return 1;
    draw_pix_map(n4, x_pos, y_pos);
    return 0;
}

int draw5(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n5;
    uint8_t *map = xpm_load(n5_xpm, XPM_8_8_8, &n5);
    if (map == NULL) return 1;
    draw_pix_map(n5, x_pos, y_pos);
    return 0;
}

int draw6(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n6;
    uint8_t *map = xpm_load(n6_xpm, XPM_8_8_8, &n6);
    if (map == NULL) return 1;
    draw_pix_map(n6, x_pos, y_pos);
    return 0;
}

int draw7(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n7;
    uint8_t *map = xpm_load(n7_xpm, XPM_8_8_8, &n7);
    if (map == NULL) return 1;
    draw_pix_map(n7, x_pos, y_pos);
    return 0;
}

int draw8(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n8;
    uint8_t *map = xpm_load(n8_xpm, XPM_8_8_8, &n8);
    if (map == NULL) return 1;
    draw_pix_map(n8, x_pos, y_pos);
    return 0;
}

int draw9(uint32_t x_pos, uint32_t y_pos)
{
    xpm_image_t n9;
    uint8_t *map = xpm_load(n9_xpm, XPM_8_8_8, &n9);
    if (map == NULL) return 1;
    draw_pix_map(n9, x_pos, y_pos);
    return 0;
}
