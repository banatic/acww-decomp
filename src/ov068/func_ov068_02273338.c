/* func_ov068_02273338 @ 0x02273338, 0x1d8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c5c8(void *self, void *data);
extern int func_ov004_0222c3c4(void *ptr, int flags);
extern int func_02055140(void *ptr, void *g);
extern void func_02055060(void *ptr, int val, int mode, int size, int arg4, int arg5);
extern void func_02055050(void *ptr);
extern int func_ov004_0222c3a4(void *ptr, int flags);
extern int func_ov004_0222c3b4(void *ptr, int flags);
extern int func_0205650c(void *ptr, int val, void *g);
extern void func_02056478(void *ptr, int val, int mode, int size, int arg4);
extern int func_02055e00(void *ptr);
extern void func_020563dc(void *ptr, int val);
extern void func_ov004_0222c62c(void *data, void *p1, void *p2, void *p3);

extern unsigned char data_ov068_0227795c;
extern unsigned char data_ov068_02277968;
extern unsigned char data_ov068_02277978;
extern void *data_021c9b24;

void func_ov068_02273338(void *self)
{
    char *b = (char *) self;

    func_ov004_0222c5c8(b, &data_ov068_0227795c);

    if (func_ov004_0222c3c4(b + 0x1a4, 0) && func_02055140(b + 0xec, data_021c9b24)) {
        func_02055060(b + 0xec, func_ov004_0222c3c4(b + 0x1a4, 0), 0, 0x1000, 0, 0);
        func_02055050(b + 0xec);
    }

    if (func_ov004_0222c3a4(b + 0x1a4, 0) && func_0205650c(b + 0x2b0, *(int *) (b + 0x148), data_021c9b24)) {
        func_02056478(b + 0x2b0, func_ov004_0222c3a4(b + 0x1a4, 0), 0, 0x1000, 0);
        func_020563dc(b + 0x2b0, func_02055e00(b + 0xec));
    }

    if (func_ov004_0222c3b4(b + 0x1a4, 0) && func_0205650c(b + 0x290, *(int *) (b + 0x148), data_021c9b24)) {
        func_02056478(b + 0x290, func_ov004_0222c3b4(b + 0x1a4, 0), 0, 0x1000, 0);
        func_020563dc(b + 0x290, func_02055e00(b + 0xec));
    }

    func_ov004_0222c62c(&data_ov068_02277968, b + 0x2d0, b + 0x388, b + 0x42c);

    if (func_ov004_0222c3c4(b + 0x388, 0) && func_02055140(b + 0x2d0, data_021c9b24)) {
        func_02055060(b + 0x2d0, func_ov004_0222c3c4(b + 0x388, 0), 1, 0x1000, 0, 0);
        func_02055050(b + 0x2d0);
    }

    func_ov004_0222c62c(&data_ov068_02277978, b + 0x434, b + 0x4ec, b + 0x590);

    if (func_ov004_0222c3c4(b + 0x4ec, 0) && func_02055140(b + 0x434, data_021c9b24)) {
        func_02055060(b + 0x434, func_ov004_0222c3c4(b + 0x4ec, 0), 0, 0x1000, 0, 0);
        func_02055050(b + 0x434);
    }
}
