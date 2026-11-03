/* field_actor_looks_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020106a8 @ 0x020106a8, 0x70 bytes, Thumb
 * func_02010680 @ 0x02010680, 0x28 bytes, Thumb
 * func_0201063c @ 0x0201063c, 0x44 bytes, Thumb
 */

typedef struct {
    char pad_00[0x290];
    int unk_290;
    char pad_294[0x774 - 0x294];
    int unk_774;
    int unk_778;
} my_struct;

extern int func_020110e8(void *);
extern int func_0201111c(int);
extern int func_0205f874(int, int);
extern int func_0205f848(int, int);
extern int func_02011368(void *a);
extern void func_0205d3d4(void *a, int b, int c, int d, int e);
extern int func_0205d25c(void *p);
extern int func_0203cfa8(unsigned int *);
extern int func_020b9d3c(void *p, int b, void *c, int d, int e, int f);
extern int data_020d8408;

void func_020106a8(int p0, int p1, int p2)
{
    int k = func_020110e8((void *) p0);
    int r4;
    int r1;

    if (k >= 0x10) {
        if (k >= 0x18) {
            r4 = 0x19;
        } else {
            r4 = 0x11;
        }
    } else {
        if (k >= 8) {
            r4 = 9;
        } else {
            r4 = 1;
        }
    }

    if (func_0201111c(p0) != 0) {
        r4 -= 0x10;
        r1 = p2 + r4 * 8;
    } else {
        r1 = p2 + r4 * 8;
    }

    r4 = p2 + ((p1 << 3) + 0x80);

    if (r1 < 0x80) {
        func_0205f874(p0 + 0x7a0, r1);
    }
    if (r4 >= 0x80 && r4 < 0xc0) {
        func_0205f848(p0 + 0x7a0, r4);
    }
}

void func_02010680(void *a, int b)
{
    func_0205d3d4((char *) a + 0x774, b, func_02011368(a), 0, 0);
}

int func_0201063c(my_struct *self)
{
    int val = self->unk_290;
    return func_020b9d3c(&self->unk_778, val, &data_020d8408, (func_0203cfa8((unsigned int *) func_0205d25c(&self->unk_774))),
                         0, 0);
}
