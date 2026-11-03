/* card_save: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a16e0 @ 0x020a16e0, 0x58 bytes, Thumb
 * func_020a16b0 @ 0x020a16b0, 0x30 bytes, Thumb
 * func_020a1628 @ 0x020a1628, 0x88 bytes, Thumb
 */

extern void func_0209fb70(int *);
extern int func_020a1738(int, int *);
extern int func_0209faf4(int *);
extern void func_0209fb6c(int *);
extern int func_02050af8(void *base, unsigned int mask, char *flag, int param);
extern unsigned int data_021c8188;
extern int func_020a1368(void);
extern void func_0209fb5c(int);
extern void func_0209e5e4(int);
extern int data_021f3ba0;
extern int data_021dc7a8;
extern int data_020d1c20[3];

int func_020a16e0(void)
{
    int a, b;
    func_0209fb70(&a);
    func_020a1738(0, &a);
    func_0209fb70(&b);
    func_020a1738(1, &b);
    if (func_0209faf4(&a) == func_0209faf4(&b)) {
        func_0209fb6c(&b);
        func_0209fb6c(&a);
        return 1;
    } else {
        func_0209fb6c(&b);
        func_0209fb6c(&a);
        return 0;
    }
}

int func_020a16b0(void)
{
    char flag = 0;
    if (func_02050af8(&data_021c8188, 0x0003fffc, &flag, 1) == 1) {
        return 1;
    } else {
        return 0;
    }
}

int func_020a1628(void)
{
    int r4, r5, r6, r7;

    r4 = func_020a1368();
    r7 = (int) &data_021f3ba0;
    func_0209fb5c(r7);
    func_0209e5e4(r4);

    r6 = r4 + 0xc800;
    r5 = r7 - (int) &data_021dc7a8;
    r4 = r6 - r4;

    if (func_02050af8((void *) ((int) ((int *) &data_021c8188)), data_020d1c20[0] + r5, (char *) r7, 4) == 1) {
        return 1;
    }
    if (func_02050af8((void *) ((int) ((int *) &data_021c8188)), data_020d1c20[1] + r5, (char *) r7, 4) == 1) {
        return 1;
    }
    if (func_02050af8((void *) ((int) ((int *) &data_021c8188)), data_020d1c20[2] + r4, (char *) r6, 1) == 1) {
        return 1;
    }

    return 0;
}
