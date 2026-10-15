/* func_ov048_02261380 @ 0x02261380, 0x12c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern void *data_ov048_02263d20;

extern void *func_02073138(void *a);
extern void *func_020984e8(void);
extern void *func_02073144(void *a);
extern void func_02073100(void);
extern int func_020eb8a0(int a);
extern void func_ov048_02260e28(void *self, int a, int b);
extern int func_020eb704(int a);
extern void func_ov048_022616b8(void *self, int a);
extern int func_020eb6b8(void *a);
extern void *func_02099664(void *a);
extern void *func_02077bc8(void *a);
extern void *func_02077d68(void *object);
extern void func_020eb6a0(void *a, void *b);
extern void func_02077bcc(void);
extern void MI_CpuCopy8(void *dst, void *src, int size);
extern int func_020a15ac(void);
extern int func_ov048_02260a60(void *self);
extern void func_0206844c(void *target, void *buf, void *g);
extern void func_ov048_02262378(void *self);

void func_ov048_02261380(void *self)
{
    void *r7 = data_020ccf94;
    void *r4;
    void *r6;
    u8 b;

    r4 = func_02073138(r7);
    r6 = func_020984e8();

    if (*(u8 *) ((char *) self + 0x1e) == 0x62) {
        int r4_val;
        int ret;
        u8 byte;

        r6 = func_02073144(r7);
        r4_val = *(int *) ((char *) self + 0x3ec);
        func_02073100();
        ret = func_020eb8a0(r4_val);
        byte = *(u8 *) ((char *) r6 + ret * 0x23 + 0x1a0);
        if (byte != 6 || ret == ~0) {
            func_ov048_02260e28(self, 0x78, 1);
        } else {
            r4_val = *(int *) ((char *) self + 0x3ec);
            func_02073100();
            func_020eb704(r4_val);
            *(u16 *) (*(char **) ((char *) self + 0xb8) + 0xe6e) = 0x960;
            func_ov048_022616b8(self, 5);
        }
        return;
    }

    {
        int val;
        if (func_020eb6b8((char *) r4 + 0x20) != 0) {
            void *a1 = func_02099664(r6);
            void *a2 = func_02077bc8(a1);
            void *a3 = func_02077d68(a2);
            void *b2;

            func_020eb6a0((char *) r4 + 0x20, a3);
            func_02099664(r6);
            func_02077bcc();
            asm {
                mov b2, r0
            }
            r4 = (char *) r4 + 0x20;
            MI_CpuCopy8(r4, b2, 0x40);
            if (func_020a15ac() == 0) {
                val = 0x75;
            } else {
                val = 2;
            }
        } else {
            val = func_ov048_02260a60(self);
        }
        b = val;
    }

    func_0206844c(*(void **) ((char *) self + 0x40), &b, data_ov048_02263d20);

    if (*(u8 *) ((char *) self + 0x813) == 0 || *(u8 *) ((char *) self + 0x810) != 0) {
        func_ov048_022616b8(self, 0x14);
    } else {
        func_ov048_02262378(self);
        func_ov048_022616b8(self, 0);
    }
}
