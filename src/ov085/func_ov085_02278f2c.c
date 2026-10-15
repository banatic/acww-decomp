/* func_ov085_02278f2c @ 0x02278f2c, 0x120 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_021e5a2c;

extern void *func_0206837c(void *p);
extern void *func_02094fd4(void *buf);
extern void func_020ab5e4(void *p);
extern int func_0207cec0(void *g, int byte);
extern int func_0208150c(int a);
extern int func_02003704(int a);
extern int func_02003618(int a, void *buf);
extern int func_020ab550(void *p, int i);
extern int func_020ab798(int);
extern void *func_020a8bb8(int a, void *buf);
extern int func_0207cad4(void *g);
extern void func_020ab778(int v, void *sep);
extern int func_020ab39c(int zero);
extern void func_020ab774(int v, int r);
extern void func_020ab71c(int v);
extern void func_020ab4bc(void *p, int i);
extern void func_020ab4a8(void *p);
extern void func_02068388(void *p, int one);
extern void *func_02094fbc(void *buf);

struct UnkStruct_02278f2c {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb8 - 0x44];
    u8 byte;
    char pad_B9[0xbc - 0xb9];
    int arr[5];
};

void func_ov085_02278f2c(struct UnkStruct_02278f2c *s)
{
    void *p = func_0206837c(s->unk_40);
    char sep = 0x3d;
    int buf[8];
    int i;
    int cur;
    int temp;

    func_02094fd4(buf);
    func_020ab5e4(p);

    for (i = 0; i < 5; i++) {
        s->arr[i] = -1;
    }

    if (func_02003704(func_0208150c(func_0207cec0(&data_021e5a2c, s->byte))) == 0) {
        s->byte = 0;
    }

    cur = s->byte;
    i = 0;
    while (cur < 8 && i < 4) {
        temp = func_0207cec0(&data_021e5a2c, cur);
        if (func_02003704(func_0208150c(temp)) != 0) {
            func_02003618(func_0208150c(temp), buf);
            func_020a8bb8(func_020ab798((int) func_020ab550(p, i)), buf);
            s->arr[i] = cur;
            i++;
        }
        cur++;
    }

    s->byte = cur;
    if (s->byte >= 8) {
        s->byte = 0;
    }

    if (func_0207cad4(&data_021e5a2c) > 4) {
        int v = func_020ab550(p, i);
        func_020ab778(v, &sep);
        func_020ab774(v, func_020ab39c(0));
        func_020ab71c(v);
        i++;
    }

    func_020ab4bc(p, i);
    if (func_0207cad4(&data_021e5a2c) > 4) {
        func_020ab4a8(p);
    }

    func_02068388(s->unk_40, 1);
    func_02094fbc(buf);
}
