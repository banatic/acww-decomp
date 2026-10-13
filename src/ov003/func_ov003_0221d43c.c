/* func_ov003_0221d43c @ 0x0221d43c, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xec];
    char unk_EC;
    char pad_ED[0x10a - 0xed];
    u8 unk_10A;
    char pad_10B[0x12c - 0x10b];
    int unk_12C;
    char pad_130[0x136 - 0x130];
    u16 unk_136;
    char pad_138[0x236 - 0x138];
    unsigned char f236_a : 1;
    unsigned char f236_b : 1;
    unsigned char f236_c : 6;
    u8 unk_237;
} UnkStruct_0221d43c;

typedef struct {
    char b[0x20];
} Buf;
typedef struct {
    int pad_00;
    Buf b;
} BufW;

extern void *func_0207cec0(void *p, int idx);
extern void func_020a8164(void *p, void *q);
extern int func_0207f1d4(void *h);
extern int func_0208150c(void *h);
extern int func_020036e8(int q);
extern void func_02094fd4(Buf *b);
extern void func_02003618(int a, Buf *b);
extern void func_02068404(int a, int b, Buf *c);
extern void func_02094fbc(Buf *b);

extern char data_021e5a2c[];
extern char data_ov003_02239064[];
extern char data_ov003_02239074[];
extern u8 data_ov003_0223664c[];
extern u8 data_ov003_02236644[];

void func_ov003_0221d43c(UnkStruct_0221d43c *self)
{
    unsigned int ok = 0;
    u16 id;
    int idx;
    void *h;
    BufW w;

    id = self->unk_136;
    if (id >= 0x5001 && id <= 0x5008) {
        ok = 1;
    }
    if (ok != 0) {
        idx = id - 0x5001;
    } else {
        idx = -1;
    }

    h = func_0207cec0(data_021e5a2c, idx);
    func_020a8164(&self->unk_EC, data_ov003_02239064);
    if (func_0207f1d4(h) == 0) {
        self->unk_10A = 6;
    } else if (self->f236_b != 0) {
        func_020a8164(&self->unk_EC, data_ov003_02239074);
        self->unk_10A = 0;
    } else {
        int q = func_0208150c(h);
        if (q != 0) {
            if (self->unk_237 == 0) {
                self->unk_10A = data_ov003_0223664c[func_020036e8(q)];
            } else {
                self->unk_10A = data_ov003_02236644[func_020036e8(q)];
            }
        }
    }
    func_02094fd4(&w.b);
    func_02003618(func_0208150c(h), &w.b);
    func_02068404(self->unk_12C, 0, &w.b);
    func_02094fbc(&w.b);
}
