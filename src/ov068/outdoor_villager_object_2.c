/* outdoor_villager_object_2: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226d664 @ 0x0226d664, 0x2c bytes, Thumb
 * func_ov068_0226d5f4 @ 0x0226d5f4, 0x70 bytes, Thumb
 */

extern int func_ov068_02266e7c(void *);
extern void func_ov068_02266e78(void *, int);
extern void func_0202e118(void *dst, void *src);
extern int func_02012508(void *a, void *b, void *c, int d, int e);
extern void func_02012444(void *a, unsigned short b, int c);
extern char *func_020121e0(void *a, int b);
extern unsigned short data_020c80f8;

int func_ov068_0226d664(void *self)
{
    if (func_ov068_02266e7c((char *) self + 0x9f4)) {
        func_ov068_02266e78((char *) self + 0x9f4, 0);
        return 1;
    }
    return 0;
}

void func_ov068_0226d5f4(void *param)
{
    unsigned short local[2];

    func_0202e118(&local[0], param);
    if (local[0] == 0xfff1) {
        return;
    }
    func_0202e118(&local[1], param);
    func_02012508((char *) param + 0x9b4, param, &local[1], 0, 0);
    func_02012444((char *) param + 0x9b4, data_020c80f8, 0);
    func_020121e0((char *) param + 0x9b4, 0x1000);
    *((unsigned char *) param + 0x9f0) = 1;
}
