/* func_02017b44 @ 0x02017b44, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(const void *);
extern int func_02057cf4(void);
extern int func_02057d0c(int, const void *);
extern void func_02016764(const void *, const void *, int, unsigned short, int, int, int, int);
extern void func_0200442c(const void *, int, int, int);
extern void func_02019af0(const void *, int);
extern unsigned short data_020c80f8;

void func_02017b44(unsigned char *arg0, unsigned char *arg1)
{
    int state;

    if (func_020164cc(arg1 + 0x334) == 0) {
        return;
    }

    state = func_02057cf4();

    if (state == 5) {
        goto state5;
    }
    if (state != 7) {
        goto else_block;
    }

    // state == 7
    if (func_02057d0c(7, arg1) == 0) {
        return;
    }
    func_02016764(arg1 + 0x334, arg1, 0x2d, data_020c80f8, 3, 0x1000, 0, 0);
    arg0[0x98] = 0x12;
    goto end;

state5:
    if (func_02057d0c(5, arg1) == 0) {
        return;
    }
    func_02016764(arg1 + 0x334, arg1, 0x2e, data_020c80f8, 1, 0x1000, 0, 0);
    func_0200442c(arg1 + 0x514, 0x4f, 0x7f, 0);
    arg0[0x98] = 5;
    goto end;

else_block:
    func_02016764(arg1 + 0x334, arg1, 0x24, data_020c80f8, 0, 0x1000, 0, 0);
    func_02019af0(arg0, 1);
    arg0[0x98] = 0x14;

end:
    return;
}
