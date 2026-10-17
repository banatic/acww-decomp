/* Overlay 139: a block shared by the screens of overlays 140 (overlay group 0x21, at 0x8e8 of
 * its scene) and 141 (group 0x22, GroupParams mode 0x3d of overlay 92's dispatcher, at 0x94),
 * both drawn from the files of "menu/res/".
 *
 * It begins with a message window of ov002's (ov002/message_window.h) and keeps twenty text
 * labels for six rows of two columns (each row's two six-character names: the first through
 * menu message 0x66, the second as it is) and three headings (menu messages 0x65, 0xc2, 0xc1).
 * Row N is written in colour 14 - N of the background's palette 7 ("menu/res/bg7.bpl"), which
 * ResRows_FadeRow blends towards colour 15 and a layer task queues when it changed. Overlay
 * 140 fills the rows from a list of 32 entries of 0x23 bytes, six a page. */
#ifndef CLEAN_OV139_RES_ROWS_H
#define CLEAN_OV139_RES_ROWS_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/message_window.h"
#include "types.h"

#define RES_ROWS_LABELS 20
#define RES_ROWS_ROWS 6
#define RES_ROWS_NAME_LENGTH 6
#define RES_ROWS_COLORS 16

/* In `flags`. */
enum ResRowsFlag {
    RES_ROWS_FLAG_PALETTE = 0x1 /* `palette` is to be queued */
};

typedef struct ResRows {
    MessageWindow window;              /* 0x000 */
    TextLabel labels[RES_ROWS_LABELS]; /* 0x0cc */
    LayerTask palette_task;            /* 0x93c: `palette` to the layer's palette 7 */
    u16 palette_file[RES_ROWS_COLORS]; /* 0x960: "menu/res/bg7.bpl" */
    u16 palette[RES_ROWS_COLORS];      /* 0x980: its copy, the rows' colours faded */
    u16 flags;                         /* 0x9a0: ResRowsFlag */
    u8 layer;                          /* 0x9a2: the background layer of the labels and palette */
    u8 label_count;                    /* 0x9a3: the labels taken (ResRows_TakeLabel) */
} ResRows;

void ResRows_ClearFlags(ResRows *self, unsigned short mask);
u16 *ResRows_SetFlags(ResRows *self, unsigned short mask);
int ResRows_TestFlags(const ResRows *self, unsigned short mask);
unsigned int ResRows_Cells(unsigned int unused, unsigned int index);
void ResRows_SetSecondColumn(ResRows *self, int row, const u16 *name, int color);
void ResRows_SetFirstColumn(ResRows *self, int row, const u16 *name, int color);
TextLabel *ResRows_TakeLabel(ResRows *self);
void ResRows_ReleaseLabels(ResRows *self);
void ResRows_ClearRow(ResRows *self, int row);
void ResRows_SetRow(ResRows *self, int row, const u16 *names);
void ResRows_MakeHeadings(ResRows *self);
void ResRows_FadeRow(ResRows *self, int row, int step, int steps, int color);
void ResRows_LoadObjFiles(ResRows *self);
void ResRows_ClearRows(ResRows *self);
void ResRows_LoadBg(ResRows *self);
void ResRows_DrawAt(ResRows *self, int x, int y);
void ResRows_QueuePalette(ResRows *self);
void ResRows_Teardown(ResRows *self);
void ResRows_End(ResRows *self);
void ResRows_Open(ResRows *self, unsigned char layer, int message);
ResRows *ResRows_Destroy(ResRows *self);
ResRows *ResRows_Construct(ResRows *self);

#endif
