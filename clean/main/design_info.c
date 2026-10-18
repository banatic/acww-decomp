/* A design's pixels and information (design_info.h). */
#include "design_info.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "clean.h"
#include "design_assets.h"
#include "name_texts.h"
#include "player_id.h"
#include "player_record.h"
#include "player_records.h"
#include "text_base.h"

static_assert(sizeof(DesignTitle) == 0x14, "title");
static_assert(sizeof(DesignTitleWide) == 0x24, "wide title");

/* The two halves of DesignInfo.palette_and_kind. */
#define KIND_MASK 0x0f
#define PALETTE_SHIFT 4
#define PALETTE_MASK 0xf0

/* The town part of a creator: its number and name (0xe bytes), compared by DesignInfo_Equals. */
#define TOWN_NAME_SIZE 12

extern void MI_CpuCopy8(const void *src, void *dst, int size);

static Design *design_at(unsigned int address)
{
    return (Design *) (uintptr_t) address;
}

/* Copies `count` halfwords in ascending order, as the game does (which decides the result when
 * the two overlap). */
static void copy_halves(u16 *dst, const u16 *src, int count)
{
    for (int i = 0; i < count; i++) {
        dst[i] = src[i];
    }
}

/* func_020728f8: copies a design over another, all but its last byte (padding).
 * REQUIRES: the two designs are the same or do not overlap. */
void Design_Assign(Design *dst, const Design *src)
{
    memcpy(dst->pixels, src->pixels, DESIGN_PIXELS_SIZE);
    dst->info.creator = src->info.creator;
    memcpy(dst->info.title, src->info.title, sizeof(dst->info.title));
    dst->info.palette_and_kind = src->info.palette_and_kind;
}
CLEAN_AS(func_020728f8, Design_Assign)

/* func_02072d4c: a design's information, after its pixels. */
unsigned int Design_Info(unsigned int design)
{
    return (unsigned int) (uintptr_t) &design_at(design)->info;
}
CLEAN_AS(func_02072d4c, Design_Info)

/* func_02072d58: paints a design's pixels all with one colour (0-15).
 * REQUIRES: the pixels are word aligned (they always are). */
void Design_Fill(unsigned int *pixels, unsigned int colour)
{
    u8 two_pixels = (u8) (colour | (colour << 4));
    unsigned int word = 0x01010101u * two_pixels;
    for (unsigned int i = 0; i < DESIGN_PIXELS_SIZE / 4; i++) {
        pixels[i] = word;
    }
}
CLEAN_AS(func_02072d58, Design_Fill)

/* func_02072d84: sets a design's pixels from 0x200 bytes. */
void Design_SetPixels(Design *design, const void *pixels)
{
    MI_CpuCopy8(pixels, Design_Pixels(design), DESIGN_PIXELS_SIZE);
}
CLEAN_AS(func_02072d84, Design_SetPixels)

/* func_02072da0: a design's pixels, at its start. */
void *Design_Pixels(Design *design)
{
    return design;
}
CLEAN_AS(func_02072da0, Design_Pixels)

/* func_02072da4 */
Design *Design_Destruct(Design *design)
{
    DesignInfo_Destruct(&design->info);
    return design;
}
CLEAN_AS(func_02072da4, Design_Destruct)

/* func_02072dbc */
char *Design_Construct(char *design)
{
    DesignInfo_Construct(&((Design *) design)->info);
    return design;
}
CLEAN_AS(func_02072dbc, Design_Construct)

/* func_02072dd4: whether two designs are the same: their information, then their pixels.
 * REQUIRES: both designs are word aligned (the pixels are compared a word at a time). */
int Design_Equals(char *a, char *b)
{
    Design *design_a = (Design *) a;
    Design *design_b = (Design *) b;
    if (DesignInfo_Equals(&design_a->info, &design_b->info) == 0) {
        return 0;
    }
    return memcmp(design_a->pixels, design_b->pixels, DESIGN_PIXELS_SIZE) == 0;
}
CLEAN_AS(func_02072dd4, Design_Equals)

/* func_02072e18: sets the kind (0-15, the low four bits of byte 0x32). */
void DesignInfo_SetKind(u8 *info, int kind)
{
    DesignInfo *self = (DesignInfo *) info;
    self->palette_and_kind = (u8) ((self->palette_and_kind & PALETTE_MASK) | (kind & KIND_MASK));
}
CLEAN_AS(func_02072e18, DesignInfo_SetKind)

/* func_02072e30 */
int DesignInfo_Kind(DesignInfo *info)
{
    return info->palette_and_kind & KIND_MASK;
}
CLEAN_AS(func_02072e30, DesignInfo_Kind)

/* func_02072e3c */
void DesignInfo_SetTitle(DesignInfo *info, DesignTitle *title)
{
    copy_halves(info->title, title->chars, DESIGN_TITLE_LENGTH);
}
CLEAN_AS(func_02072e3c, DesignInfo_SetTitle)

/* func_02072e50: sets the title from a wide text, unless that is longer than a title. */
void DesignInfo_SetTitleFromWide(DesignInfo *info, DesignTitleWide *text)
{
    NameWideText_CopyOut((NameWideText *) text, info->title, DESIGN_TITLE_LENGTH);
}
CLEAN_AS(func_02072e50, DesignInfo_SetTitleFromWide)

/* func_02072e64: sets the title from an 8-bit text, through a wide one. */
void DesignInfo_SetTitleFromText(DesignInfo *info, void *text)
{
    DesignTitleWide wide;
    NameWideText_Construct((NameWideText *) &wide);
    TextBase_BytesToWide((WideTextBase *) &wide, text);
    DesignInfo_SetTitleFromWide(info, &wide);
    NameWideText_Destruct((NameWideText *) &wide);
}
CLEAN_AS(func_02072e64, DesignInfo_SetTitleFromText)

/* func_02072e90 */
void DesignInfo_GetTitle(DesignInfo *info, DesignTitle *title)
{
    copy_halves(title->chars, info->title, DESIGN_TITLE_LENGTH);
}
CLEAN_AS(func_02072e90, DesignInfo_GetTitle)

/* func_02072ea4: the title into a wide text. */
void DesignInfo_TitleToWide(char *info, DesignTitleWide *text)
{
    TextBase_SetWide(text, ((DesignInfo *) info)->title, DESIGN_TITLE_LENGTH);
}
CLEAN_AS(func_02072ea4, DesignInfo_TitleToWide)

/* func_02072eb8: the title into an 8-bit text, through a wide one. */
void DesignInfo_TitleToText(DesignInfo *info, void *text)
{
    DesignTitleWide wide;
    NameWideText_Construct((NameWideText *) &wide);
    DesignInfo_TitleToWide((char *) info, &wide);
    TextBase_WideToBytes(text, (WideTextBase *) &wide, 0, 0);
    NameWideText_Destruct((NameWideText *) &wide);
}
CLEAN_AS(func_02072eb8, DesignInfo_TitleToText)

/* func_02072ee8: the creator, at the start of the information. */
DesignCreator *DesignInfo_Creator(DesignInfo *info)
{
    return &info->creator;
}
CLEAN_AS(func_02072ee8, DesignInfo_Creator)

/* func_02072eec: copies a creator in, field by field in ascending order. */
void DesignInfo_SetCreator(DesignInfo *info, DesignCreator *creator)
{
    DesignCreator *to = &info->creator;
    to->town_id = creator->town_id;
    copy_halves(to->town_name, creator->town_name, 6);
    to->player_id = creator->player_id;
    copy_halves(to->player_name, creator->player_name, 6);
    to->unk_1c = creator->unk_1c;
    to->unk_1d = creator->unk_1d;
}
CLEAN_AS(func_02072eec, DesignInfo_SetCreator)

/* func_02072f38: makes this system's player the creator.
 * REQUIRES: there is such a player (without one the creator is read from address 0x247e). */
void DesignInfo_SetCreatorLocal(DesignInfo *info)
{
    int creator = (int) (uintptr_t) PlayerRecord_Player(PlayerRecords_Current());
    DesignInfo_SetCreator(info, (DesignCreator *) (uintptr_t) creator);
}
CLEAN_AS(func_02072f38, DesignInfo_SetCreatorLocal)

/* func_02072f54: sets the palette (0-15, the high four bits of byte 0x32). */
void DesignInfo_SetPalette(DesignInfo *info, int palette)
{
    info->palette_and_kind = (u8) ((info->palette_and_kind & KIND_MASK) | ((palette & 0xf) << PALETTE_SHIFT));
}
CLEAN_AS(func_02072f54, DesignInfo_SetPalette)

/* func_02072f74 */
unsigned char DesignInfo_Palette(DesignInfo *info)
{
    return (unsigned char) (info->palette_and_kind >> PALETTE_SHIFT);
}
CLEAN_AS(func_02072f74, DesignInfo_Palette)

/* func_02072f88: the 16 colours of the design's palette. */
int DesignInfo_PaletteColours(DesignInfo *info)
{
    DesignManager *manager = (DesignManager *) (uintptr_t) DesignManager_Get();
    return (int) DesignManager_Palette(manager, DesignInfo_Palette(info));
}
CLEAN_AS(func_02072f88, DesignInfo_PaletteColours)

/* func_02072fac */
int DesignInfo_Destruct(DesignInfo *info)
{
    PlayerId_Destruct(&info->creator);
    return (int) (uintptr_t) info;
}
CLEAN_AS(func_02072fac, DesignInfo_Destruct)

/* func_02072fbc */
int DesignInfo_Construct(DesignInfo *info)
{
    PlayerId_Construct(&info->creator);
    return (int) (uintptr_t) info;
}
CLEAN_AS(func_02072fbc, DesignInfo_Construct)

/* func_02072fcc: whether two designs' information is the same: kind and palette, the creator's
 * town (number and name) and player (func_0209518c), and the title. */
int DesignInfo_Equals(DesignInfo *a, DesignInfo *b)
{
    if (a->palette_and_kind != b->palette_and_kind) {
        return 0;
    }
    if (a->creator.town_id != b->creator.town_id) {
        return 0;
    }
    if (memcmp(a->creator.town_name, b->creator.town_name, TOWN_NAME_SIZE) != 0) {
        return 0;
    }
    if (PlayerId_SamePlayer(&a->creator, &b->creator) == 0) {
        return 0;
    }
    return memcmp(a->title, b->title, sizeof(a->title)) == 0;
}
CLEAN_AS(func_02072fcc, DesignInfo_Equals)
