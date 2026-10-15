/* func_02022034 @ 0x02022034, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    Vec pos;
    u8 pad_68[0x830 - 0x68];
    void *unk_830;
} UnkStruct_02022034;

typedef struct {
    u8 d[0x28];
} Cell;

typedef struct {
    Cell *base;
    u32 w;
    u32 h;
} Tbl;

typedef struct {
    u8 pad_00[0x100];
    UnkStruct_02022034 *unk_100;
    u8 unk_104[0x122 - 0x104];
    u8 unk_122;
} UnkStruct_02022034_2;

typedef struct {
    int a;
    u8 b;
} UnkStruct_02022034_3;

extern Tbl *data_021c80bc;
extern volatile u8 data_020e54a8;
extern UnkStruct_02022034_3 data_020c8c50;

extern int func_020b6680(void);
extern int func_020b66b0(void);
extern int func_0207f294(void *);
extern int func_02037d64(Cell *, int);
extern unsigned int func_0208150c(void *);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(UnkStruct_02022034_2 *, u8 *, u8 *, int, int, int, int scale, int, int);

int func_02022034(UnkStruct_02022034_2 *p)
{
    Tbl *t;
    Cell *c;
    Vec *v;
    int mode;
    int x, y;
    int q;
    int chk;

    mode = 4;
    t = data_021c80bc;
    if (func_020b6680()) {
        q = func_020b66b0();
        if (q == func_0207f294(p->unk_100->unk_830)) {
            mode = 3;
        } else {
            goto skip;
        }
    } else {
    skip:
        if (t) {
            chk = (data_020e54a8 == 0);
            if (chk) {
                v = &p->unk_100->pos;
                y = v->z >> 17;
                x = v->x >> 17;
                if ((u32) x < t->w && (u32) y < t->h && t->base != 0) {
                    c = t->base + (x + y * t->w);
                } else {
                    c = 0;
                }
                if (c) {
                    if (func_02037d64(c, 0x200) == 1) {
                        mode = 0;
                    } else if (func_02037d64(c, 2) == 1) {
                        mode = 1;
                    } else if (func_02037d64(c, 0x800) == 1) {
                        mode = 2;
                    }
                }
            }
        }
    }
    func_0202da38(p, p->unk_104, &p->unk_122, 0x1e, func_020036e8((unsigned char *) func_0208150c(p->unk_100->unk_830)),
                  data_020c8c50.a, data_020c8c50.b, mode, 0);
    return 1;
}
