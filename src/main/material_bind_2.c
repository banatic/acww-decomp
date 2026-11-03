/* material_bind_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020574b4 @ 0x020574b4, 0x10 bytes, Thumb
 * func_020574b0 @ 0x020574b0, 0x2 bytes, Thumb
 * func_020574a0 @ 0x020574a0, 0x10 bytes, Thumb
 * func_02057468 @ 0x02057468, 0x36 bytes, Thumb
 * func_02057430 @ 0x02057430, 0x36 bytes, Thumb
 * func_02057428 @ 0x02057428, 0x8 bytes, Thumb
 * func_020573f0 @ 0x020573f0, 0x36 bytes, Thumb
 * func_020573b8 @ 0x020573b8, 0x36 bytes, Thumb
 * func_0205738c @ 0x0205738c, 0x2a bytes, Thumb
 */

struct StructName {
    char pad_00[4];
    signed char unk_04;
};

extern int func_02057a50(int, int);
extern int func_0205720c(int a, int b, int d);
extern int func_02057238(int a, int b, int c);
extern int func_0205712c(int a, int b, int d);
extern int func_02057a40(int a, int b);

int func_02057430(int a0, int a1, int a2);
void func_02057428(signed char *p0);
int func_0205738c(int a, int b, int c);

int func_020574b4(int arg)
{
    func_02057428((signed char *) arg);
    return arg;
}

void func_020574b0(void *object) {}

int func_020574a0(struct StructName *s)
{
    if (s->unk_04 == -1) {
        return 0;
    }
    return 1;
}

int func_02057468(int arg0, int arg1, int arg2)
{
    int r0;
    int r1;
    int r2;
    int r4;
    int r5;
    int r6;

    r5 = arg0;
    r4 = arg1;
    r6 = arg2;
    r0 = func_020574a0((struct StructName *) ((void *) arg0));
    if (r0 == 0) {
        r0 = func_02057a50(r4, r6);
        r2 = (r0 << 0x18) >> 0x18;
        r0 = 0;
        r1 = ~r0;
        if (r2 != r1) {
            r0 = func_02057430(r5, r4, r2);
        } else {
            r0 = 0;
        }
    } else {
        r0 = 0;
    }
    return r0;
}

int func_02057430(int a0, int a1, int a2)
{
    int r5 = a0;
    int r6 = a1;
    int r4 = a2;
    int r0;

    if (func_020574a0((struct StructName *) ((void *) a0)) == 0) {
        r0 = -1;
        if (r4 != r0) {
            r0 = *(unsigned char *) (r6 + *(int *) (r6 + 8) + 5);
            if (r4 < r0) {
                *(unsigned char *) (r5 + 4) = r4;
                *(int *) r5 = r6;
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

void func_02057428(signed char *p0)
{
    p0[4] = (~0);
}

int func_020573f0(int a, int b, int c, int d)
{
    int ret = (func_0205738c(a, b, c) & 1) != 0;
    return (ret & func_0205720c(a, b, d)) != 0;
}

int func_020573b8(int a, int b, int c, int d)
{
    int ret = (func_02057238(a, b, c) & 1) != 0;
    return (ret & func_0205712c(a, b, d)) != 0;
}

int func_0205738c(int a, int b, int c)
{
    if (c != 0) {
        return func_02057238(a, b, func_02057a40(b, c));
    } else {
        return 1;
    }
}
