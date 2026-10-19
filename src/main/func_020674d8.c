/* func_020674d8 @ 0x020674d8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a8298(int);
extern void func_0200467c(unsigned short);
extern unsigned short data_020cce84[];

void func_020674d8(int arg)
{
    int ret;
    unsigned short cmd;

    ret = func_020a8298(arg + 0x14ac);
    if (ret < 2) {
        cmd = data_020cce84[ret];
        if (cmd != 0) {
            func_0200467c(cmd);
        }
    }
}
