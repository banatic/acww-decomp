/* func_020b65d0 @ 0x020b65d0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern unsigned char func_020b65c4(void);
extern int func_020b660c(int);

int func_020b65d0(void)
{
    unsigned char b = data_020e54a8;
    int flag1;
    unsigned int flag2;

    flag1 = b ? 0 : 1;
    if (flag1 != 0) {
        goto calls;
    }
    flag2 = (b == 1) ? 1u : 0u;
    if (flag2 == 0) {
        goto ret0;
    }
calls:
    return func_020b660c(func_020b65c4());
ret0:
    return 0;
}
