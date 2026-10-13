/* func_ov009_02264d48 @ 0x02264d48, 0x18 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264884(void);

int func_ov009_02264d48(void)
{
    int *p = (int *) func_ov009_02264884();
    if (p) {
        return p[2];
    }
    return 0;
}
