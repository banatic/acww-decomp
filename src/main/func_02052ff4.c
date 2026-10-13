/* func_02052ff4 @ 0x02052ff4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02052f3c(void);
extern void func_02053088(void);

int func_02052ff4(void)
{
    if (func_02052f3c() != 0) {
        func_02053088();
        return 1;
    }
    return 0;
}
