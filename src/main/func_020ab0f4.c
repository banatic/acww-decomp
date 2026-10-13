/* func_020ab0f4 @ 0x020ab0f4, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern int func_020a7e64(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern int func_020a7e70(void);

int func_020ab0f4(void)
{
    int result;

    result = 0;
    if (func_020a7e50() != 0) {
        if (func_020a7ffc() != 0) {
            func_020a7e64();
            result = 1;
        }
    } else {
        if (func_020a7e44() != 0) {
            if (func_020a812c() != 0) {
                func_020a7e70();
                result = 1;
            }
        }
    }
    return result;
}
