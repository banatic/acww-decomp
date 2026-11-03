/* keyboard_entry_states: 14 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a0e10 @ 0x022a0e10, 0x88 bytes, Thumb
 * func_ov126_022a0db4 @ 0x022a0db4, 0x5c bytes, Thumb
 * func_ov126_022a0d8c @ 0x022a0d8c, 0x28 bytes, Thumb
 * func_ov126_022a0d30 @ 0x022a0d30, 0x5c bytes, Thumb
 * func_ov126_022a0d00 @ 0x022a0d00, 0x30 bytes, Thumb
 * func_ov126_022a0cd0 @ 0x022a0cd0, 0x30 bytes, Thumb
 * func_ov126_022a0c64 @ 0x022a0c64, 0x6c bytes, Thumb
 * func_ov126_022a0c34 @ 0x022a0c34, 0x30 bytes, Thumb
 * func_ov126_022a0c1c @ 0x022a0c1c, 0x16 bytes, Thumb
 * func_ov126_022a0c00 @ 0x022a0c00, 0x1c bytes, Thumb
 * func_ov126_022a0be0 @ 0x022a0be0, 0x20 bytes, Thumb
 * func_ov126_022a0bc8 @ 0x022a0bc8, 0x16 bytes, Thumb
 * func_ov126_022a0bb0 @ 0x022a0bb0, 0x16 bytes, Thumb
 * func_ov126_022a0b90 @ 0x022a0b90, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x19c];
    unsigned char sub;
} Obj_ov126_022a20c8;

typedef struct {
    u8 pad_00[0xae];
    u8 unk_AE;
    u8 pad_AF[0x19c - 0xae - 1];
    u8 unk_19C;
} UnkStruct_022a0d30;

struct SParameter {
    unsigned char pad_00[0xae];
    unsigned char unk_AE;
};

typedef struct {
    char pad_00[0xae];
    unsigned char unk_AE;
} UnkStruct_022a0cd0;

extern int func_0208e484(const void *);
extern const void *func_ov095_02299a00(const void *);
extern int func_ov126_022a03dc(const void *, const void *);
extern void func_ov095_0229bf3c(const void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov095_0229c8e4(const void *, const void *);
extern void func_ov095_0229cce0(const void *);
extern void func_ov126_0229fec0(const void *);
extern unsigned short data_021fbe40;
extern int func_ov095_0229bf0c(void *);
extern void *func_ov095_0229c548(void *);
extern void *func_ov095_0229c448(void *, void *, int);
extern void func_ov126_0229fea0(const unsigned char *);
extern int func_ov126_022a027c(UnkStruct_022a0d30 *self, int val);
extern int func_ov126_0229f7c8(UnkStruct_022a0d30 *self, int val);
extern void func_ov126_0229ff0c(UnkStruct_022a0d30 *self);
extern int func_ov126_022a0a50(UnkStruct_022a0d30 *self);
extern void func_ov126_022a0978(struct SParameter *param);
extern int func_ov002_0220a700(char *);
extern int func_0208e4bc(char *);
extern int func_ov002_0220a6e0(char *);
extern int func_ov002_0220a768(char *, int);
extern int func_ov002_0220a72c(char *, int);
extern void func_ov002_0220a0b4(char *, int, int);
extern int func_ov126_0229ffdc(char *);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov095_0229bf48(void *p);
extern int func_ov002_0220b8ac(void *p, int flag);
extern void func_ov002_02207fc0(void *p);
extern void func_ov126_022a0000(void *p);
extern int func_0206fe60(void);

int func_ov126_022a0be0(int param);

void func_ov126_022a0e10(const void *self)
{
    if (func_0208e484((const char *) self + 0x3f90) != 0) {
        const void *r4 = func_ov095_02299a00((const char *) self + 0x19c);
        const void *tmp = (const void *) func_ov095_0229c448((void *) ((const char *) self + 0x19c), (void *) r4, 9);
        int ret = func_ov126_022a03dc(self, tmp);
        if (ret == 1 && ((data_021fbe40 & 1) != 0)) {
            func_ov095_0229bf3c((const char *) self + 0x19c);
            func_ov002_02208098((void *) (self), 0xa);
            func_ov095_0229c8e4((const char *) self + 0x19c, r4);
            return;
        }
        if (ret == 4) {
            func_ov095_0229cce0((const char *) self + 0x19c);
            return;
        } else if (ret == 3) {
            return;
        } else {
            func_ov126_0229fec0(self);
        }
    }
}

void func_ov126_022a0db4(Obj_ov126_022a20c8 *self)
{
    void *r4;
    void *ret;

    if (!(data_021fbe40 & 1)) {
        func_ov126_0229fec0((const void *) self);
    } else {
        if (func_ov095_0229bf0c(&self->sub) == 0) {
            return;
        }
        r4 = func_ov095_0229c548(&self->sub);
        ret = func_ov095_0229c448(&self->sub, r4, 9);
        func_ov126_022a03dc((const void *) self, (const void *) ret);
        func_ov095_0229c8e4((const void *) (&self->sub), (const void *) r4);
    }
}

void func_ov126_022a0d8c(const unsigned char *p)
{
    if (func_0208e484((const void *) (p + 0x3f90)) != 0) {
        func_ov126_0229fea0(p);
        func_ov002_02208098((void *) (p), 4);
    }
}

void func_ov126_022a0d30(UnkStruct_022a0d30 *self)
{
    if (((*(u16 *) &data_021fbe40) & 2) == 0) {
        func_ov002_02208098((void *) (self), self->unk_AE);
    } else {
        if (func_ov095_0229bf0c(&self->unk_19C) != 0) {
            if (func_ov126_022a027c(self, 0) != 0) {
                if (func_ov126_0229f7c8(self, 0x80) != 0) {
                    func_ov126_0229ff0c(self);
                }
            } else {
                func_ov126_022a0a50(self);
            }
        }
    }
}

void func_ov126_022a0d00(struct SParameter *param)
{
    if ((data_021fbe40 & 0x200) != 0) {
        return;
    }
    func_ov002_02208098((void *) (param), param->unk_AE);
    func_ov126_022a0978(param);
}

void func_ov126_022a0cd0(UnkStruct_022a0cd0 *self)
{
    if ((data_021fbe40 & 0x100) != 0) {
        return;
    }
    func_ov002_02208098((void *) (self), self->unk_AE);
    func_ov126_022a0978((struct SParameter *) self);
}

void func_ov126_022a0c64(char *param)
{
    if (func_ov002_0220a700(param + 0x3dc4) != 0) {
        if (func_0208e4bc(param + 0x3f90) != 0) {
            int v4 = func_ov002_0220a6e0(param + 0x3dc4);
            int v6 = func_ov002_0220a768(param + 0x3dc4, -1);
            int v2 = func_ov002_0220a72c(param + 0x3dc4, -1);
            func_ov002_0220a0b4(param + 0x3f90, v4 + v6, v4 + v2);
        }
    } else {
        func_ov126_0229ffdc(param);
        func_ov002_022080a0((void *) (param), 1);
    }
}

void func_ov126_022a0c34(void *p)
{
    func_ov095_0229bf48((char *) p + 0x19c);
    if (func_ov002_0220b8ac((char *) p + 0x412c, 1)) {
        func_ov126_022a0be0((int) p);
    }
}

unsigned char *func_ov126_022a0c1c(void *arg)
{
    func_ov126_0229ffdc((char *) arg);
    return func_ov002_02208098((void *) (arg), 0);
}

unsigned char *func_ov126_022a0c00(void *p)
{
    func_ov002_02207fc0(p);
    func_ov126_022a0000(p);
    return func_ov002_02208098((void *) (p), 4);
}

int func_ov126_022a0be0(int param)
{
    if (func_0206fe60()) {
        return (int) func_ov126_022a0c1c((void *) param);
    } else {
        return (int) func_ov126_022a0c00((void *) param);
    }
}

int func_ov126_022a0bc8(int p)
{
    func_ov126_0229ffdc((char *) p);
    return (int) func_ov002_02208098((void *) (p), 3);
}

int func_ov126_022a0bb0(int arg)
{
    func_ov002_02207fc0((void *) arg);
    return (int) func_ov002_02208098((void *) (arg), 5);
}

void func_ov126_022a0b90(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov126_022a0bc8(r4);
    } else {
        func_ov126_022a0bb0(r4);
    }
}
