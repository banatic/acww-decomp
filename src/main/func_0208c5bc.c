/* func_0208c5bc @ 0x0208c5bc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);

int func_0208c5bc(void)
{
    int r4 = 0;
    int r0;

    if (func_020a7e50() != 0) {
        if (func_020a7ffc() != 0) {
            r4 = 1;
        }
    } else {
        if (func_020a7e44() != 0) {
            if (func_020a812c() != 0) {
                r4 = 1;
            }
        }
    }
    return r4;
}
