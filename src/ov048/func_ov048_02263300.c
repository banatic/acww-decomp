/* func_ov048_02263300 @ 0x02263300, 0x120 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02263300 {
    u8 pad_00[0x618];
    u8 unk_618;
    u8 pad_619[0x658 - 0x618 - 1];
    u8 unk_658;
    u8 pad_659[0x676 - 0x658 - 1];
    u8 unk_676;
    u8 pad_677[0xe6e - 0x676 - 1];
    u16 unk_E6E;
    u8 pad_E70[0xe71 - 0xe6e - 2];
    u8 unk_E71;
};

extern int func_02014868(void *);
extern int func_0203ad88(void);
extern int func_ov004_0222d518(void);
extern int func_020ec1e8(void);
extern void func_02073100(void);
extern int func_020eb7ac(void);
extern void func_020732b4(void *, int);
extern void func_020742b4(void);
extern int func_020e8840(void *);
extern unsigned int func_02073044(void);
extern int func_020ec920(void);
extern int func_0203e020(void *);
extern void func_ov048_02262618(void *, int, int);
extern void *func_020984e8(void);
extern void *func_020642a4(const void *);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int func_02099870(void *);
extern void *func_020950a8(int);
extern void func_020730c8(void);
extern int func_020eb9f0(void *, int);
extern void *data_020ccf94;
extern const char data_021dc7aa[];

int func_ov048_02263300(struct UnkStruct_02263300 *self)
{
    u8 buf[0x1c];

    switch (self->unk_E71) {
        case 0:
            if (func_02014868(&self->unk_618) == 0) {
                self->unk_E71 = 1;
            }
            break;
        case 1:
            if (func_0203ad88() == 0) {
                func_ov004_0222d518();
                self->unk_E6E = 0x3c;
                self->unk_E71 = 2;
                if (func_020ec1e8() == 4) {
                    func_02073100();
                    func_020eb7ac();
                    func_020732b4(data_020ccf94, 0);
                    func_020742b4();
                }
            }
            break;
        case 2:
            if (func_020e8840(&self->unk_E6E) == 0) {
                if (self->unk_676 == 0x46 || self->unk_676 == 0x6c) {
                    if (func_020ec1e8() == 3) {
                        func_02073044();
                        if (func_020ec920() != 0) {
                            func_0203e020(self);
                        }
                    } else {
                        void *v;
                        func_ov048_02262618(&self->unk_658, 1, 0);
                        v = func_020984e8();
                        MI_CpuCopy8(func_020642a4(data_021dc7aa), buf, 12);
                        MI_CpuCopy8(func_020950a8((int) func_02099870(v)), buf + 12, 12);
                        buf[0x18] = 0;
                        func_020730c8();
                        func_020eb9f0(buf, 0x1a);
                        func_020742b4();
                        func_0203e020(self);
                    }
                }
            } else {
                if (func_020ec1e8() == 3) {
                    func_02073044();
                    func_020ec920();
                }
            }
            break;
        default:
            break;
    }
    return 1;
}
