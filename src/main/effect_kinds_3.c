/* effect_kinds_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020924f4 @ 0x020924f4, 0x28 bytes, Thumb
 * func_020924e4 @ 0x020924e4, 0x10 bytes, Thumb
 * func_020924d4 @ 0x020924d4, 0x10 bytes, Thumb
 * func_020924ac @ 0x020924ac, 0x28 bytes, Thumb
 * func_02092484 @ 0x02092484, 0x28 bytes, Thumb
 * func_02092478 @ 0x02092478, 0xc bytes, Thumb
 */

extern int func_02094b58(int, int, int, int, int, int);
extern unsigned char data_020e284c[];
extern void func_02094c38(int a, void *b, int c);
extern char data_020d17b0[];
extern int func_02094bcc(int, void *, int);
extern unsigned char data_020e2874[];
extern unsigned char data_020e2954[];

void func_020924f4(int a, int b, int c, int d)
{
    int sp[2];
    sp[0] = d;
    sp[1] = (unsigned int) data_020e284c;
    func_02094b58(0x8d, a, b, c, sp[0], sp[1]);
}

void func_020924e4(int a)
{
    func_02094c38(a, data_020d17b0, 0);
}

int func_020924d4(int a)
{
    return func_02094bcc(a, ((int *) data_020d17b0), 0);
}

void func_020924ac(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2874;
    func_02094b58(0x4f, r0, r1, r2, sp[0], sp[1]);
}

void func_02092484(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2954;
    func_02094b58(0x92, r0, r1, r2, sp[0], sp[1]);
}

void func_02092478(int a)
{
    func_02094c38(a, 0, 0);
}
