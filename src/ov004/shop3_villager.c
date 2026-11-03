/* shop3_villager: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02221910 @ 0x02221910, 0x3c bytes, Thumb
 * func_ov004_0222190c @ 0x0222190c, 0x2 bytes, Thumb
 * func_ov004_02221908 @ 0x02221908, 0x2 bytes, Thumb
 * func_ov004_022218e8 @ 0x022218e8, 0x20 bytes, Thumb
 * func_ov004_022218a4 @ 0x022218a4, 0x44 bytes, Thumb
 * func_ov004_02221878 @ 0x02221878, 0x2c bytes, Thumb
 * func_ov004_02221850 @ 0x02221850, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct Vt Vt;

typedef struct UnkStruct_022218a4 {
    Vt *vt;
} UnkStruct_022218a4;

struct Vt {
    void (*unk_00)(UnkStruct_022218a4 *);
    void (*unk_04)(UnkStruct_022218a4 *);
    void (*unk_08)(UnkStruct_022218a4 *);
};

extern int func_0200366c(int argument0, int argument1, int argument2, int argument3);
extern int func_020644cc(int argument0);
extern int func_0208150c(unsigned int argument0);
extern void *data_ov004_02254094;
extern void *data_ov004_02257f20;
extern int func_02014868(int);
extern int func_0201c2a4(void *, int);
extern void func_02016108(void *, int);
extern void func_ov004_02221a64(void *, int);
extern void *func_ov004_02221994(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern char data_ov004_02253fd4[];

int func_ov004_02221910(char *self, char *a1)
{
    // DECLS
    int v1;
    int v5;
    // ENDDECLS
    v1 = *(int *) (self + 0x1a4);
    func_0200366c((int) (func_0208150c((unsigned int) ((unsigned int) (*(int *) ((char *) v1 + 0x830))))),
                  (int) (&data_ov004_02257f20), (int) (0x28), (int) (&data_ov004_02254094));
    *(void **) (a1) = &data_ov004_02257f20;
    v5 = func_020644cc(0x5);
    *(u8 *) (a1 + 0x4) = v5;
    return v5;
}

void func_ov004_0222190c(void) {}

void func_ov004_02221908(void) {}

int func_ov004_022218e8(int arg0)
{
    int result;
    int ret;

    result = func_02014868(arg0 + 0x618);
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

void func_ov004_022218a4(u8 *self, int op)
{
    UnkStruct_022218a4 *s;
    switch (op) {
        case 0:
            s = (UnkStruct_022218a4 *) (self + 0x89c);
            s->vt->unk_08(s);
            func_02016108(self + 0x89c, func_0201c2a4(self, 4));
            func_ov004_02221a64(self, 0);
            break;
        case 8:
            func_ov004_02221a64(self, 2);
            break;
    }
}

void *func_ov004_02221878(void *s)
{
    *(void **) s = &data_ov004_02253fd4;
    func_ov004_02221994((char *) s + 0x89c);
    func_0202e5e0(s);
    func_020edf54(s);
    return s;
}

void *func_ov004_02221850(char *self)
{
    *(const void **) self = ((void *const *) data_ov004_02253fd4);
    func_ov004_02221994(self + 0x89c);
    func_0202e5e0(self);
    return self;
}
