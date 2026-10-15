/* func_020aabe0 @ 0x020aabe0, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern void func_020a7e64(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern void func_020a7e70(void);

int func_020aabe0(void)
{
    int r4;
    int r0;

    r4 = 0;
    if (func_020a7e50() != 0) {
        if (func_020a7ffc() != 0) {
            func_020a7e64();
            r4 = 1;
        }
    } else {
        if (func_020a7e44() != 0) {
            if (func_020a812c() != 0) {
                func_020a7e70();
                r4 = 1;
            }
        }
    }
    return r4;
}
