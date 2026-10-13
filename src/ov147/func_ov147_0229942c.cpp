/* func_ov147_0229942c @ 0x0229942c, 0x26c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0229942c;
typedef void (UnkStruct_0229942c::*PMF)();

struct UnkStruct_0229942c_2 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    void *unk_40;
    char pad_44[4];
    void *unk_48;
};

extern char data_021dc7bc[];
extern char data_021dc7a8[];
extern u8 data_021f43e8;
extern PMF *data_ov147_0229a9fc[];

extern PMF data_0213dd98;
extern PMF data_ov147_0229a8f4;
extern PMF data_ov147_0229a904;
extern PMF data_ov147_0229a924;
extern PMF data_ov147_0229a92c;
extern PMF data_ov147_0229a93c;
extern PMF data_ov147_0229a944;
extern PMF data_ov147_0229a964;
extern PMF data_ov147_0229a984;
extern PMF data_ov147_0229a8ec;
extern PMF data_ov147_0229a90c;
extern PMF data_ov147_0229a914;

extern "C" {
void *func_020682e0(int a);
void *func_0206837c(void *h);
int func_020ab504(void *g);
int func_02098880(char *t);
int func_0209f180(char *t);
void func_0206844c(void *a, u8 *p, int c);
void func_ov147_02299fc8(void *p, int n);
void func_ov147_02299374(UnkStruct_0229942c_2 *self);
void func_ov147_0229942c(UnkStruct_0229942c_2 *self);
}

void func_ov147_0229942c(UnkStruct_0229942c_2 *self)
{
    void *h;
    int k;
    int b;
    int c;
    int idx;

    h = func_020682e0(0);
    k = func_020ab504(func_0206837c(h));
    b = func_02098880(data_021dc7bc);
    c = func_0209f180(data_021dc7a8);
    {
        static PMF t0[4] = {data_0213dd98, data_ov147_0229a8f4, data_0213dd98, data_ov147_0229a904};
        static PMF t1[4] = {data_ov147_0229a924, data_ov147_0229a92c, data_0213dd98, data_ov147_0229a93c};
        static PMF t2[4] = {data_ov147_0229a944, data_ov147_0229a964, data_0213dd98, data_ov147_0229a984};
        static PMF t3[5] = {data_ov147_0229a8ec, data_0213dd98, data_ov147_0229a90c, data_0213dd98, data_ov147_0229a914};
    }
    idx = 3;
    switch (self->unk_1E) {
        case 0:
            if (k == 0) {
                func_0206844c(h, &data_021f43e8, 0);
                func_ov147_02299fc8(self->unk_48, 8);
            }
            break;
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x31:
            if (b <= 0 && c != 0) {
                idx = 0;
            } else if (c == 0) {
                idx = 1;
            } else if (b == 4) {
                idx = 2;
            }
            if (data_ov147_0229a9fc[idx][k] != 0) {
                (((UnkStruct_0229942c *) self)->*data_ov147_0229a9fc[idx][k])();
            }
            break;
        case 0x30:
            if (k == 0) {
                func_0206844c(h, &data_021f43e8, 0);
                func_ov147_02299fc8(self->unk_48, 9);
            }
            break;
        case 0x35:
            if (k == 0) {
                func_0206844c(self->unk_40, &data_021f43e8, 0);
                func_ov147_02299fc8(self->unk_48, 0xa);
            }
            break;
        case 3:
            func_ov147_02299374(self);
            break;
    }
}
