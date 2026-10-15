/* func_0206f910 @ 0x0206f910, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a1d0(void);
extern int func_02066830(int, void *);
extern unsigned char data_021cfd68[];

void func_0206f910(void)
{
    int ret;
    ret = func_0209a1d0();
    if (ret) {
        func_02066830(ret, data_021cfd68);
    }
}
