#pragma once

#define cursor_r_default 15
#define Default_cursor_color_R 102
#define Default_cursor_color_G 204
#define Default_cursor_color_B 255
#define Default_cursor_color_A 200

extern px_color cursor_color;
extern int cursor_color_A;
// 初始化自定义光标
void cursor_init();

// 绘制自定义光标
void cursor_draw(px_surface* psurface);

void cursor_CURSORDOWN();
void cursor_CURSORUP();
void cursor_CURSORRDOWN();
void cursor_CURSORRUP();