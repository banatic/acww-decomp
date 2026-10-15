/* func_ov003_0221ffec @ 0x0221ffec, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    void *a[4];
    void *b[4];
    void *c;
    void *d;
} UnkStruct_0221ffec;

extern void *data_021c9b1c;
extern void *data_021fbe94;
extern int data_021f34b0;

extern const char data_ov003_02239bf8[];
extern const char data_ov003_02239c1c[];
extern const char data_ov003_02239c40[];
extern const char data_ov003_02239c58[];

extern unsigned char *func_020b3750(void *record);
extern int func_020b38c0(void *p, int i);
extern int func_ov003_022203dc(void);
extern void *func_02064960(void *a, int b, const char *f, int d, ...);
extern void *func_021077e8(void *p);
extern int func_020560e0(void *p, int x);
extern void *func_020561cc(void *p, void *q);
extern void func_020e9898(void *p);
extern int func_02056064(void *p, int x);
extern void *func_02064b2c(const char *f, void *g, int n, int z);
extern void *NNS_G3dGetJntAnmSet(void *p);
extern void *func_02107b44(void *p, int x);

int func_ov003_0221ffec(UnkStruct_0221ffec *self)
{
    int rem;
    void *m;
    void *g1;
    int neg4;
    u8 i;
    int z1;
    int z2;
    int idx;
    s8 letter;
    void *t;

    g1 = data_021c9b1c;
    i = 0;
    neg4 = -4;
    z2 = 0;
    z1 = 0;
    do {
        idx = func_020b38c0(func_020b3750(&data_021f34b0), i);
        letter = (s8) (idx / 5 + 0x41);
        rem = idx % 5;
        t = data_021fbe94;
        m = func_02064960(t, neg4, data_ov003_02239bf8, letter, letter, rem, func_ov003_022203dc());
        self->a[i] = func_021077e8(m);
        if (func_020560e0(self->a[i], z1) != 0) {
            self->a[i] = func_020561cc(self->a[i], data_021c9b1c);
        }
        func_020e9898(m);
        m = func_02064960(data_021fbe94, neg4, data_ov003_02239c1c, letter, letter, rem);
        self->b[i] = func_021077e8(m);
        if (func_02056064(self->b[i], z2) != 0) {
            self->b[i] = func_020561cc(self->b[i], g1);
        }
        func_020e9898(m);
        i = (u8) (i + 1);
    } while (i < 4);
    self->c = func_02107b44(NNS_G3dGetJntAnmSet(func_02064b2c(data_ov003_02239c40, g1, 4, 0)), 0);
    self->d = func_02107b44(NNS_G3dGetJntAnmSet(func_02064b2c(data_ov003_02239c58, g1, 4, 0)), 0);
    return 1;
}
