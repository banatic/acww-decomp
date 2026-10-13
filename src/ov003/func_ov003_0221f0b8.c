/* func_ov003_0221f0b8 @ 0x0221f0b8, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221f0d0(void);

int func_ov003_0221f0b8(void)
{
    int *p;
    p = (int *) func_ov003_0221f0d0();
    if (p != 0) {
        return p[4];
    }
    return 0;
}
