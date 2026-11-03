/* outdoor_villager_chat_2: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226a1b8 @ 0x0226a1b8, 0xa8 bytes, Thumb
 * func_ov068_0226a114 @ 0x0226a114, 0xa4 bytes, Thumb
 * func_ov068_0226a0dc @ 0x0226a0dc, 0x38 bytes, Thumb
 * func_ov068_0226a098 @ 0x0226a098, 0x42 bytes, Thumb
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

extern void *func_0201ce50(void *);
extern void *func_0201c314(void *, void *);
extern void func_ov068_0226cfd4(void *);
extern int func_02019d0c(void *, int, int, int, int, int, void *, int, int, unsigned short, int);
extern void func_ov068_02266c34(void *, void *, int, int, void *, void *, int, int, int);
extern void func_0202e188(void *);
extern void func_ov068_0226ad78(void *, void *, int, int, int);
extern void func_0201cbc4(void *);
extern unsigned short data_020c80f8;
extern int data_020c814c;
extern unsigned char data_021fbee8;
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern int func_02019c6c(void *p, int v, unsigned short s);
extern int data_ov068_022767b8[];
extern int func_ov068_0226ae80(F_0226a114 *self, void *other);
extern int func_ov068_0226c0e0(F_0226a114 *self, void *other);
extern void func_0201ce5c(void *other, int v);
extern void func_0201ce44(void *other, int v);
extern void func_ov068_0226cce8(F_0226a114 *self, void *other, int v);
extern void func_ov068_0226cbf4(F_0226a114 *self);
extern int func_020ea990(void *, void *);
extern int func_02096190(int);
extern int func_0201c390(int, int);

int func_ov068_0226a1b8(void *p1, void *p2)
{
    void *r7;
    void *r6;

    r7 = func_0201ce50(p2);
    r6 = func_0201c314(p2, r7);
    func_ov068_0226cfd4(p2);
    func_02019d0c((char *) p2 + 0x564, 3, 1, 0, 0, 0, r6, 0, 0, data_020c80f8, 0);
    func_ov068_02266c34((char *) p2 + 0x898, p2, 2, 0, r7, (void *) &data_021fbee8, 4, data_020c814c, 1);
    ((char *) p1)[0x1c] = 0;
    func_0202e188(p2);
    func_ov068_0226ad78(p1, p2, 0, 0, 1);
    func_0201cbc4((char *) p2 + 0x83c);
    return 1;
}

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
        UnkStruct_0226a114 *obj = (UnkStruct_0226a114 *) func_0201ce50(other);
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

int func_ov068_0226a0dc(int unused, char *arg)
{
    char *result = func_0201ce50(arg);
    int r = 0;
    if (result) {
        arg += 0x5c;
        result += 0x5c;
        r = func_020ea990(arg, result);
    }
    if (r > 0 && r < 0x3c00) {
        return 1;
    }
    return 0;
}

int func_ov068_0226a098(int arg0, int arg1)
{
    int a, b, ret, t;

    ret = 0;
    a = func_02096190(4);
    b = (int) func_0201ce50((void *) arg1);
    if (a != 0 && b != 0) {
        ret = func_0201c390(arg1, a);
        t = func_0201c390(b, a);
        if (ret >= t) {
            ret = t;
        }
    }
    return ret;
}
