/* A design's own methods (design.h): its pixels, and its information (creator, title, kind and
 * palette): reading and setting each part, comparing two designs, and the constructors.
 *
 * Two kinds of text object carry a title in and out: a wide one of 10 characters
 * (DesignTitleWide, func_02062e50 builds it) and the game's 8-bit text objects, converted to
 * and from it by func_020a87e0 and func_020a8a70. */
#ifndef CLEAN_MAIN_DESIGN_INFO_H
#define CLEAN_MAIN_DESIGN_INFO_H

#include "design.h"
#include "types.h"

#define DESIGN_TITLE_LENGTH 10

typedef struct DesignTitle {
    u16 chars[DESIGN_TITLE_LENGTH];
} DesignTitle;

/* The wide text object of a title (0x24 bytes; a vtable, then its characters at 0xe). */
typedef struct DesignTitleWide {
    u32 words[9];
} DesignTitleWide;

void Design_Assign(Design *dst, const Design *src);
unsigned int Design_Info(unsigned int design);
void Design_Fill(unsigned int *pixels, unsigned int colour);
void Design_SetPixels(Design *design, const void *pixels);
void *Design_Pixels(Design *design);
Design *Design_Destruct(Design *design);
char *Design_Construct(char *design);
int Design_Equals(char *a, char *b);
void DesignInfo_SetKind(u8 *info, int kind);
int DesignInfo_Kind(DesignInfo *info);
void DesignInfo_SetTitle(DesignInfo *info, DesignTitle *title);
void DesignInfo_SetTitleFromWide(DesignInfo *info, DesignTitleWide *text);
void DesignInfo_SetTitleFromText(DesignInfo *info, void *text);
void DesignInfo_GetTitle(DesignInfo *info, DesignTitle *title);
void DesignInfo_TitleToWide(char *info, DesignTitleWide *text);
void DesignInfo_TitleToText(DesignInfo *info, void *text);
DesignCreator *DesignInfo_Creator(DesignInfo *info);
void DesignInfo_SetCreator(DesignInfo *info, DesignCreator *creator);
void DesignInfo_SetCreatorLocal(DesignInfo *info);
void DesignInfo_SetPalette(DesignInfo *info, int palette);
unsigned char DesignInfo_Palette(DesignInfo *info);
int DesignInfo_PaletteColours(DesignInfo *info);
int DesignInfo_Destruct(DesignInfo *info);
int DesignInfo_Construct(DesignInfo *info);
int DesignInfo_Equals(DesignInfo *a, DesignInfo *b);

#endif
