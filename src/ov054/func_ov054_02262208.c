/* func_ov054_02262208 @ 0x02262208, 0x50 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af1c(void *ptr, int x);
extern int func_02019d0c(void *ptr, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern unsigned short data_020c80f8;

int func_ov054_02262208(char *r4)
{
    struct Args {
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
        int g;
    } args;

    func_0201af1c(r4 + 0x350, 0);

    args.a = 0;
    args.b = 0;
    args.c = *(short *) (r4 + 0x804);
    args.d = 0;
    args.e = 0;
    args.f = data_020c80f8;
    args.g = 0;

    func_02019d0c(r4 + 0x564, 3, 1, 0, args.a, args.b, args.c, args.d, args.e, args.f, args.g);

    return 1;
}
