/* func_020222dc @ 0x020222dc, 0x178 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_020222dc;
typedef struct {
    u8 pad_00[0x100];
    UnkStruct_020222dc *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122[2];
} UnkStruct_020222dc_4;
typedef struct {
    u8 pad_00[0x20];
    int unk_20;
    u16 unk_24;
} UnkStruct_020222dc_2;
typedef struct {
    int unk_00;
    u8 unk_04;
} UnkStruct_020222dc_3;

extern UnkStruct_020222dc_3 data_020c8cb0;

extern UnkStruct_020222dc_2 *func_0207f270(void *p);
extern int func_0207cc54(int mask, int count, int max);
extern void func_0208150c(void *p);
extern int func_020036e8(void);
extern void func_0202da38(UnkStruct_020222dc_4 *s, void *a, void *b, int c, int d, int e, int f, int g, int h);
extern void func_02015fb0(UnkStruct_020222dc_4 *s, int a, int b, int c, int d, int e);

int func_020222dc(UnkStruct_020222dc_4 *self)
{
    UnkStruct_020222dc_2 *o;
    u8 mask;
    u8 count;
    int f;
    int v;
    unsigned int n;

    if (self->unk_100->unk_830 != 0) {
        o = func_0207f270(self->unk_100->unk_830);
    } else {
        o = 0;
    }
    mask = 0;
    count = 0;
    if (o == 0) {
        goto fail;
    }
    v = o->unk_20;
    if (v < 0) {
        goto fail;
    }
    f = o->unk_24;
    if ((f & 1) || (f & 2) || (f & 4) || (f & 8) || (f & 0x10)) {
        mask |= 1;
        count++;
    }
    if (f & 0x20) {
        mask |= 2;
        count++;
    }
    if (f & 0x40) {
        mask |= 4;
        count++;
    }
    if (f & 0x80) {
        mask |= 8;
        count++;
    }
    if (f & 0x100) {
        mask |= 0x10;
        count++;
    }
    if (f & 0x200) {
        mask |= 0x20;
        count++;
    }
    if (f & 0x400) {
        mask |= 0x40;
        count++;
    }
    n = func_0207cc54(mask, count, 7);
    if (n >= 7) {
        n = 7;
    }
    func_0208150c(self->unk_100->unk_830);
    func_0202da38(self, self->unk_104, self->unk_122, 0x1e, func_020036e8(), data_020c8cb0.unk_00, data_020c8cb0.unk_04, n, 0);
    func_02015fb0(self, v, 0, 6, 0, 0);
    return 1;
fail:
    return 0;
}
