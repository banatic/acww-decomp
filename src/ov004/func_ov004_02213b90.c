/* func_ov004_02213b90 @ 0x02213b90, 0x150 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct SELF {
    unsigned char pad_00[0x594];
    void *unk_594;
    unsigned char pad_598[0x844 - 0x598];
    int unk_844;
};

extern int func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(int a, int b);
extern void *func_0209847c(int k);
extern void *func_02099870(void *p);
extern int func_020950c0(void *p);
extern int func_0205790c(void *, const char *);
extern void *func_02072614(void);
extern void *func_02072630(void *a, int b, int c);
extern int func_02057084(void *p1, const char *p2, void *p3, void *p4, int p5);
extern const char data_ov004_022531c8[];
extern const char data_ov004_022531cc[];
extern const char data_ov004_022531d0[];

int func_ov004_02213b90(struct SELF *self)
{
    // DECLS
    volatile u16 raw;
    unsigned int f;
    unsigned int id;
    int v;
    int kind;
    int sub;
    void *ent;
    void *w;
    // ENDDECLS

    raw = func_0204bc50(func_ov004_0220fde0(self), 0);
    f = 0;
    v = -1;
    self->unk_844 = -1;
    id = raw;
    if (id >= 0x3d84 && id <= 0x3e03) {
        f = 1;
    }
    if (f != 0) {
        v = (id >= 0x3d84 && id <= 0x3e03) ? (int) (id - 0x3d84) >> 2 : -1;
    } else if (id >= 0x3ea4 && id <= 0x3f23) {
        v = (id >= 0x3ea4 && id <= 0x3f23) ? (int) (id - 0x3ea4) >> 2 : -1;
    } else if (id >= 0x4224 && id <= 0x42a3) {
        v = (id >= 0x4224 && id <= 0x42a3) ? (int) (id - 0x4224) >> 2 : -1;
    } else if (id >= 0x3f24 && id <= 0x3fa3) {
        v = (id >= 0x3f24 && id <= 0x3fa3) ? (int) (id - 0x3f24) >> 2 : -1;
    }
    if (v == -1) {
        v = 0;
    }
    kind = (v >> 3) & 3;
    sub = v & 7;
    ent = func_0209847c(kind);
    if (ent != 0) {
        if (func_020950c0(func_02099870(ent)) == 0) {
            self->unk_844 = func_0205790c(self->unk_594, data_ov004_022531cc);
        } else {
            self->unk_844 = func_0205790c(self->unk_594, data_ov004_022531d0);
        }
    }
    w = self->unk_594;
    func_02057084(w, data_ov004_022531c8, func_02072630(func_02072614(), (unsigned char) kind, (unsigned char) sub), 0, 0);
    return 1;
}
