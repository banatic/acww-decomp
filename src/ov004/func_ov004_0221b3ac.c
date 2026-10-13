/* func_ov004_0221b3ac @ 0x0221b3ac, 0x104 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 a, b, c, d, e, unk_0A;
} UnkStruct_0221b3ac;

extern int func_0203ee14(void *, void *);
extern void func_020a8164(void *, void *);
extern int func_02071298(void *, u16 *);
extern int func_020712b0(void *, u16 *);
extern int func_ov004_0221ba88(char *);
extern unsigned int func_ov004_0221b9f4(char *);
extern int data_021f38f8;
extern int data_ov004_022534cc;

int func_ov004_0221b3ac(char *self)
{
    // DECLS
    UnkStruct_0221b3ac s;
    void *p;
    unsigned int i;
    unsigned int t;
    unsigned int k;
    // ENDDECLS

    self[0x155] = 0;
    for (i = 0; i < *(unsigned int *) (self + 0x168); i++) {
        s.d = (*(u16 **) (self + 0x164))[i];
        if (func_02071298(&data_021f38f8, &s.d) != 0) {
            self[0x155] = (char) i;
            break;
        }
    }
    s.e = (*(u16 **) (self + 0x164))[(u8) self[0x155]];
    p = self;
    if (self != 0) {
        p = self + 0xec;
    }
    func_0203ee14(self, p);
    func_020a8164(self + 0xec, &data_ov004_022534cc);
    if (func_ov004_0221ba88(self) == 0) {
        self[0x10a] = 0;
    } else {
        t = *(unsigned int *) (self + 0x15c);
        if (t == 3) {
            if (*(unsigned int *) (self + 0x168) == 1) {
                self[0x10a] = 5;
            } else {
                self[0x10a] = (char) *(short *) (self + 0x160);
            }
        } else if (t <= 1) {
            k = func_ov004_0221b9f4(self);
            if (k > 3) {
                k = 3;
            }
            self[0x10a] = (char) ((k - 1) % 3 + 5);
        } else {
            if (func_020712b0(&data_021f38f8, &s.e) != 2) {
                self[0x10a] = 1;
            } else {
                self[0x10a] = 2;
            }
        }
    }
    *(int *) (*(char **) (self + 0x12c) + 8) = 1;
    return 1;
}
