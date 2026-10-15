/* func_ov046_022615d4 @ 0x022615d4, 0x134 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int b[8];
} Obj20;
typedef struct {
    int b[0x45];
} Obj114;

struct UnkStruct_022615d4 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x80];
    u8 c4;
    u8 c5;
    char pad_C6[2];
    int arr[5];
};

extern void *func_0206837c(void *p);
extern void func_020ab5e4(void *p);
extern void *func_020b1954(Obj20 *o);
extern int func_020b4980(Obj20 *o, char *sep, int z);
extern int func_020b1394(Obj20 *o, int cur);
extern void *func_020b55d0(Obj114 *o);
extern int func_020ab550(void *p, int i);
extern int func_020a89dc(Obj114 *o, Obj20 *src);
extern int func_020ab798(int v);
extern void *func_020a8bb8(int a, Obj114 *o);
extern void *func_020b55b8(Obj114 *o);
extern void func_020ab778(int v, char *sep);
extern int func_020ab39c(int one);
extern void func_020ab774(int v, int r);
extern void func_020ab71c(int v);
extern void func_020ab4bc(void *p, int i);
extern void func_020ab4a8(void *p);
extern void func_02068388(void *p, int one);
extern void *func_020b193c(Obj20 *o);

void func_ov046_022615d4(struct UnkStruct_022615d4 *s)
{
    int v;
    char sep;
    Obj20 o1;
    Obj20 o2;
    Obj114 o3;
    void *p;
    int i;
    int cur;

    p = func_0206837c(s->unk_40);
    sep = 0xf;
    func_020ab5e4(p);
    func_020b1954(&o1);
    func_020b1954(&o2);
    sep = 0x7d;
    func_020b4980(&o2, &sep, 0);

    for (i = 0; i < 5; i++) {
        s->arr[i] = -1;
    }

    cur = s->c4;
    i = 0;
    while (cur < 0x10 && i < 4 && s->c5 != 0) {
        if (func_020b1394(&o1, cur) != 0) {
            func_020b55d0(&o3);
            v = func_020ab550(p, i);
            func_020a89dc(&o3, &o1);
            func_020a89dc(&o3, &o2);
            func_020a8bb8(func_020ab798(v), &o3);
            s->arr[i] = cur;
            i++;
            s->c5 = s->c5 - 1;
            func_020b55b8(&o3);
        }
        cur++;
    }

    s->c4 = cur;
    if (s->c4 >= 0x10) {
        s->c4 = 0xf;
    }

    sep = 0xf;
    if (s->c5 == 0) {
        sep = 0x10;
    }

    v = func_020ab550(p, i);
    func_020ab778(v, &sep);
    func_020ab774(v, func_020ab39c(1));
    func_020ab71c(v);
    func_020ab4bc(p, i + 1);
    func_020ab4a8(p);
    func_02068388(s->unk_40, 1);
    func_020b193c(&o2);
    func_020b193c(&o1);
}
