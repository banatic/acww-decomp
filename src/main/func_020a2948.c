/* func_020a2948 @ 0x020a2948, 0x314 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020a2948 {
    u8 pad_00[0xa1];
    u8 state;
    u8 pad_A2[0xef - 0xa2];
    u8 arr_ef[0x101 - 0xef];
    u8 unk_101;
    u8 pad_102[0x10b - 0x102];
    u8 unk_10B;
    u8 pad_10C[2];
    unsigned char bf_lo : 4;
    unsigned char bf_hi : 4;
} UnkStruct_020a2948;

extern int data_021dc7a8;
extern int data_021f3ba0;
extern void *data_020ccf94;

extern int func_02073fdc(int);
extern void func_02074078(void);
extern int func_020a259c(UnkStruct_020a2948 *, int);
extern int func_020a11c4(void);
extern void func_0209e6ec(void *, int);
extern void func_0209e604(void *);
extern void func_0209f128(void *, int);
extern void func_0203d394(void);
extern int func_020a2120(UnkStruct_020a2948 *, int);
extern int func_020a238c(UnkStruct_020a2948 *);
extern void func_0209fb54(void *);
extern void func_0209fb4c(void *);
extern void func_020732b4(void *, int);
extern int func_02075aa4(int, u16);
extern int func_020ec1f8(void);
extern int func_0209ffb0(void *receiver);
extern int func_020a0174(void);
extern int func_020a0848(UnkStruct_020a2948 *, u8 *, int, int, u16, int);
extern void func_020a25cc(void *receiver);
extern void func_020a4e94(UnkStruct_020a2948 *, int);

void func_020a2948(UnkStruct_020a2948 *self)
{
    int r;
    int mask;

    switch (self->state) {
        case 0:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else if (func_020a259c(self, 0) != 0) {
                self->state = 1;
            }
            break;
        case 1:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a11c4();
                if (r > 0 && r < 4) {
                    self->state = 2;
                }
            }
            break;
        case 2:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else if (self->unk_101 != 0) {
                if (self->unk_10B == 0) {
                    func_0209e6ec(&data_021dc7a8, 5);
                    func_0209e604(&data_021dc7a8);
                } else {
                    func_0209f128(&data_021dc7a8, 0x12);
                }
                func_0203d394();
                self->state = 3;
            }
            break;
        case 3:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a2120(self, 2);
                if (r == 1) {
                    self->state = 0xb;
                } else if (r == 0) {
                    self->state = 4;
                }
            }
            break;
        case 4:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a238c(self);
                if (r == 1) {
                    self->state = 0xb;
                } else if (r != 3) {
                    func_0209fb54(&data_021f3ba0);
                    self->state = 5;
                }
            }
            break;
        case 5:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = func_020a2120(self, self->bf_hi);
                if (r == 1) {
                    self->state = 0xb;
                } else if (r == 0) {
                    self->state = 6;
                }
            }
            break;
        case 6:
            if (func_02073fdc(-1) != 0) {
                func_02074078();
            } else {
                r = self->arr_ef[func_020a11c4()];
                if (r == 1) {
                    func_0209fb4c(&data_021f3ba0);
                    self->arr_ef[func_020a11c4()] = 0;
                    func_020732b4(data_020ccf94, 2);
                    self->state = 7;
                } else if (r == 2) {
                    self->state = 0x11;
                }
            }
            break;
        case 7:
            func_02073fdc(-1);
            r = func_020a2120(self, self->bf_hi);
            if (r == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
            } else if (r == 0) {
                self->state = 8;
            }
            break;
        case 8:
            if (func_02073fdc(-1) != 0) {
                func_0209fb54(&data_021f3ba0);
                self->state = 0xa;
            } else if (func_02075aa4(1, (u16) (1 << func_020a11c4())) != 0) {
                func_020732b4(data_020ccf94, 0);
                self->state = 9;
            }
            break;
        case 9:
            mask = func_020ec1f8();
            if ((mask & (1 << func_020a11c4())) == 0) {
                if (func_0209ffb0(self) != 0) {
                    func_020a0174();
                }
                self->state = 0x16;
            }
            break;
        case 0xa:
            func_02073fdc(-1);
            r = func_020a2120(self, self->bf_hi);
            if (r == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
            } else if (r == 0) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0x11;
            }
            break;
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
            func_020a0848(self, &self->state, 0xb, 0x11, (u16) (1 << func_020a11c4()), 1);
            break;
        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xe);
            break;
    }
}
