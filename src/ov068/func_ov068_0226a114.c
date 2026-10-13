/* func_ov068_0226a114 @ 0x0226a114, 0xa4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct F_0226a114 {
    unsigned char pad_00[0x1c];
    unsigned char flag;
    unsigned char pad_1D[3];
    unsigned int value;
} F_0226a114;

typedef int (*vfunc_t)(void *);
typedef struct UnkStruct_0226a114 {
    vfunc_t *vtable;
} UnkStruct_0226a114;

extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern void func_02019c6c(void *p, int v, unsigned short s);
extern unsigned short data_020c80f8;
extern int data_ov068_022767b8[];
extern int func_ov068_0226ae80(F_0226a114 *self, void *other);
extern int func_ov068_0226c0e0(F_0226a114 *self, void *other);
extern UnkStruct_0226a114 *func_0201ce50(void *other);
extern void func_0201ce5c(void *other, int v);
extern void func_0201ce44(void *other, int v);
extern void func_ov068_0226cce8(F_0226a114 *self, void *other, int v);
extern void func_ov068_0226cbf4(F_0226a114 *self);

void func_ov068_0226a114(F_0226a114 *self, void *other)
{
    if (func_02019e00((char *) other + 0x564) == 3 && func_02019de8((char *) other + 0x564) != 0) {
        func_02019c6c((char *) other + 0x564, 1, data_020c80f8);
        self->flag = 1;
        {
            int res = func_ov068_0226ae80(self, other);
            if (res < 5) {
                self->value = data_ov068_022767b8[res];
            } else {
                self->value = 0x64;
            }
        }
        return;
    }

    if (func_ov068_0226c0e0(self, other) != 0) {
        UnkStruct_0226a114 *obj = func_0201ce50(other);
        if (obj != 0) {
            if (obj->vtable[47](obj) != 0) {
                func_0201ce5c(other, 0);
                func_0201ce44(other, 0);
                func_ov068_0226cce8(self, other, 0x13);
                func_ov068_0226cbf4(self);
            }
        }
    }
}
