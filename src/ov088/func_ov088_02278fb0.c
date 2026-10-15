/* func_ov088_02278fb0 @ 0x02278fb0, 0x150 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_0206837c(int);
extern void *func_02094fd4(void *);
extern void *func_020ab8dc(void *);
extern void func_020ab5e4(int);
extern int func_0203fa14(int);
extern int func_0203fa58(void);
extern int func_ov088_02279100(void *, void *, int);
extern int func_020ab550(int, int);
extern int func_020b4a20(void *, void *, void *);
extern int func_020ab798(int);
extern void *func_020a8bb8(int, void *);
extern void func_020ab778(int, void *);
extern int func_020ab39c(int);
extern void func_020ab774(int, int);
extern void func_020ab71c(int);
extern void func_020ab4bc(int, int);
extern void func_020ab4a8(int);
extern void func_02068388(int, int);
extern void *func_020ab8c4(void *);
extern void *func_02094fbc(void *);

extern char data_ov088_02279da8[];
extern char data_ov088_02279db4[];

struct UnkStruct_02278fb0 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[0xBD - 0x44];
    u8 bd[0x1E];
    u8 db[0x04];
};

void func_ov088_02278fb0(struct UnkStruct_02278fb0 *self, int arg2)
{
    int p;
    int res;
    int a;
    char c[2];
    unsigned int x[8];
    unsigned int y[23];
    int i;
    int r6;
    int tmp;

    func_020984e8();
    p = func_0206837c(self->unk_40);
    c[0] = 0;
    func_02094fd4(x);
    c[1] = 5;
    func_020ab8dc(y);
    func_020ab5e4(p);

    self->bd[0] = 1;
    for (i = 0; i < func_0203fa58(); i++) {
        self->bd[func_0203fa14(i)] = 1;
    }

    i = 0;
    a = 0;
    for (; i < 4; i++) {
        if (arg2 == 0) {
            r6 = func_ov088_02279100(self, self->bd, 0x1E);
            if (r6 != ~a) {
                if (self->bd[r6] == 0) {
                    self->bd[r6] = 1;
                }
            } else {
                r6 = 1;
            }
            self->db[i] = r6;
        } else if (arg2 == 1) {
            r6 = self->db[i];
        } else {
            r6 = func_0203fa14(i);
        }
        res = func_020ab550(p, i);
        c[1] = r6;
        if (arg2 != 2) {
            func_020b4a20(y, &c[1], data_ov088_02279db4);
        } else {
            func_020b4a20(y, &c[1], data_ov088_02279da8);
        }
        tmp = func_020ab798(res);
        func_020a8bb8(tmp, y);
    }

    if (arg2 == 2) {
        res = func_020ab550(p, i);
        r6 = res;
        c[1] = 5;
        func_020ab778(r6, &c[1]);
        {
            int t = func_020ab39c(1);
            func_020ab774(r6, t);
        }
        func_020ab71c(r6);
        func_020ab4bc(p, i + 1);
        func_020ab4a8(p);
    } else {
        func_020ab4bc(p, i);
    }
    func_02068388(self->unk_40, 1);
    func_020ab8c4(y);
    func_02094fbc(x);
}
