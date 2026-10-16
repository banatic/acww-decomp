/* The 3D engine's set-up: the start-up state, the clear colour and depth, the toon table, the
 * per-frame reset and the view (camera) matrix with its inverse. */
#ifndef CLEAN_MAIN_DISPLAY_3D_H
#define CLEAN_MAIN_DISPLAY_3D_H

#include "autoload_2/matrix.h"
#include "types.h"

void Display3D_ApplyClearColor(void);
void Display3D_SetClearColor(u16 color);
void Display3D_SetClearDepth(int depth);
void Display3D_LoadToonTable(void);
void Display3D_SetViewMatrix(const Mtx43 *view);
void Display3D_Reset(void);
void Display3D_Init(void);
void Display3D_InitEngine(void);

#endif
