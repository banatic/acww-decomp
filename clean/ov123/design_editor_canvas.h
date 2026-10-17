/* The design editor's drawing on its pixels (design_editor.h): the pens, stamps, lines, boxes,
 * ellipses, the flood fill, the pattern and the clear, and the characters made from the
 * pixels. */
#ifndef CLEAN_OV123_DESIGN_EDITOR_CANVAS_H
#define CLEAN_OV123_DESIGN_EDITOR_CANVAS_H

#include "design_editor.h"
#include "types.h"

void DesignEditor_Stamp(DesignEditor *self, int px, int py, int colour, int stamp);
unsigned int DesignEditor_PaintWord(unsigned int unused, unsigned int word, unsigned int mask, unsigned int colour);
void DesignEditor_Fill(DesignEditor *self, u8 px, u8 py, int colour);
int DesignEditor_RunRight(DesignEditor *self, int px, int py, int colour);
int DesignEditor_RunLeft(DesignEditor *self, int px, int py, int colour);
int DesignEditor_FindInRow(DesignEditor *self, int left, int right, int py, int colour);
unsigned char DesignEditor_PixelAt(DesignEditor *self, unsigned int px, unsigned int py);
void DesignEditor_PaintPattern(DesignEditor *self, int colour);
void DesignEditor_Clear(DesignEditor *self, int colour);
void DesignEditor_Ellipse(DesignEditor *self, int left, int top, int right, unsigned char bottom, int colour, int filled);
void DesignEditor_Rectangle(DesignEditor *self, unsigned char left, unsigned char top, unsigned int right, unsigned int bottom,
                            int colour);
int DesignEditor_Line(DesignEditor *self, unsigned int x0, unsigned int y0, unsigned int x1, unsigned char y1, int colour,
                      int brush);
int DesignEditor_PaintBrush(DesignEditor *self, u8 px, u8 py, int colour, int brush, int unused);
int DesignEditor_SetPixel(DesignEditor *self, int px, int py, int colour);
void DesignEditor_ZoomPixels(DesignEditor *self);
void DesignEditor_MakeChars(DesignEditor *self);

#endif
