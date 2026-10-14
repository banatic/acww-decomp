/* func_ov147_022997ec @ 0x022997ec, 0x2c0 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov147/Obj_ov147_0229aa28.h"
#include "types.h"

typedef Obj_ov147_0229aa28 UnkStruct_022997ec;
typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x29];
    UnkStruct_022997ec *unk_48;
} UnkStruct_022997ec_2;

extern "C" int data_ov147_0229aca4;
extern "C" u8 data_021f43e8;
extern "C" u8 data_ov147_0229a8a0[];
extern "C" int data_ov147_0229acb4;
extern "C" u8 data_ov147_0229a8a8[];
extern "C" int data_ov147_0229acb0;
extern "C" u8 data_ov147_0229a894[];
extern "C" int data_ov147_0229aca0;
extern "C" u8 data_ov147_0229a8c4[];
extern "C" int data_ov147_0229acb8;
extern "C" u8 data_ov147_0229a880[];
extern "C" char data_021dc7bc[];
extern "C" char data_021dc7a8[];
extern "C" u8 data_ov147_0229aa70[];
extern "C" u8 data_ov147_0229aa7c[];
extern "C" u8 data_ov147_0229aa88[];
extern "C" u8 data_ov147_0229aa94[];
extern "C" u8 data_ov147_0229aaa0[];
extern "C" u8 data_ov147_0229aaac[];
extern "C" u8 data_ov147_0229aab8[];
extern "C" u8 data_ov147_0229aac4[];
extern "C" int data_ov147_0229a8b0;
extern "C" u8 data_ov147_0229aad0[];

extern "C" void *func_020682e0(int a);
extern "C" int func_02098880(char *t);
extern "C" int func_0209f180(char *t);
extern "C" void func_02068440(void *a);
extern "C" void func_ov147_0229977c(UnkStruct_022997ec_2 *self, u8 *m);
extern "C" void func_ov147_022996b4(UnkStruct_022997ec_2 *self);
extern "C" void func_0206844c(void *a, u8 *p, int c);
extern "C" void func_020a1314(void);
extern "C" void func_020682fc(void *a);
extern "C" void func_020a1308(void);

extern "C" void func_ov147_022997ec(UnkStruct_022997ec_2 *self)
{
    u8 buf[8];
    void *a;
    int b;
    int c;

    if ((data_ov147_0229aca4 & 1) == 0) {
        data_ov147_0229a8a0[3] = data_021f43e8;
        data_ov147_0229aca4 |= 1;
    }
    if ((data_ov147_0229acb4 & 1) == 0) {
        data_ov147_0229a8a8[0] = data_021f43e8;
        data_ov147_0229a8a8[3] = data_021f43e8;
        data_ov147_0229acb4 |= 1;
    }
    if ((data_ov147_0229acb0 & 1) == 0) {
        data_ov147_0229a894[0] = data_021f43e8;
        data_ov147_0229a894[3] = data_021f43e8;
        data_ov147_0229acb0 |= 1;
    }
    if ((data_ov147_0229aca0 & 1) == 0) {
        data_ov147_0229a8c4[0] = data_021f43e8;
        data_ov147_0229a8c4[4] = data_021f43e8;
        data_ov147_0229aca0 |= 1;
    }
    if ((data_ov147_0229acb8 & 1) == 0) {
        data_ov147_0229a880[0] = data_021f43e8;
        data_ov147_0229acb8 |= 1;
    }
    a = func_020682e0(0);
    b = func_02098880(data_021dc7bc);
    c = func_0209f180(data_021dc7a8);
    if (*((u8 *) self->unk_48 + 0xa2) != 0) {
        func_02068440(a);
    } else {
        switch (self->unk_1E) {
            case 0x2d:
            case 0x2e:
            case 0x2f:
            case 0x31:
                if (b <= 0 && c != 0) {
                    func_ov147_0229977c(self, data_ov147_0229aa70);
                } else if (c == 0) {
                    func_ov147_0229977c(self, data_ov147_0229aa7c);
                } else if (b == 4) {
                    func_ov147_0229977c(self, data_ov147_0229aa88);
                } else {
                    func_ov147_0229977c(self, data_ov147_0229aa94);
                }
                break;
            case 1:
                if (b <= 0 && c != 0) {
                    func_ov147_0229977c(self, data_ov147_0229aaa0);
                } else if (c == 0) {
                    func_ov147_0229977c(self, data_ov147_0229aaac);
                } else if (b == 4) {
                    func_ov147_0229977c(self, data_ov147_0229aab8);
                } else {
                    func_ov147_0229977c(self, data_ov147_0229aac4);
                }
                break;
            case 0x27:
                func_020a1314();
                func_020682fc(a);
                self->unk_48->func_ov147_02299fc8(7);
                break;
            case 3:
                func_ov147_022996b4(self);
                break;
            case 6:
                func_0206844c(a, &data_021f43e8, 0);
                self->unk_48->func_ov147_02299fc8(4);
                break;
            case 11:
                func_0206844c(a, &data_021f43e8, 0);
                self->unk_48->func_ov147_02299fc8(5);
                break;
            case 5:
            case 10:
                buf[0] = 0x31;
                func_0206844c(a, buf, data_ov147_0229a8b0);
                break;
            case 0x37:
                self->unk_48->func_ov147_02299fc8(3);
                break;
            case 0:
                func_ov147_0229977c(self, data_ov147_0229aad0);
                break;
            case 0x30:
                func_ov147_0229977c(self, data_ov147_0229aad0);
                break;
            case 0x35:
                func_ov147_0229977c(self, data_ov147_0229aad0);
                break;
            case 0x24:
                func_020682fc(a);
                func_0206844c(a, &data_021f43e8, 0);
                func_020a1308();
                self->unk_48->func_ov147_02299fc8(7);
                break;
            case 0x32:
                func_0206844c(a, &data_021f43e8, 0);
                self->unk_48->func_ov147_02299fc8(3);
                break;
        }
    }
}
