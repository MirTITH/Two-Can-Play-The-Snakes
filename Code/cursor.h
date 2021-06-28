#pragma once

#define cursor_r_default 15
#define cursor_color PX_COLOR(200, 102, 204, 255)

// 初始化自定义光标
void cursor_init();

// 绘制自定义光标
void cursor_draw(px_surface* psurface);

void cursor_CURSORDOWN();
void cursor_CURSORUP();
void cursor_CURSORRDOWN();
void cursor_CURSORRUP();