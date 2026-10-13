/* func_02070edc @ 0x02070edc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02071298(int param, unsigned short *arg1);

unsigned int func_02070edc(int param)
{
    unsigned int i;
    unsigned short val;
    for (i = 0; i < 20; i++) {
        val = (i < 20) ? (0x3894 + i * 4) : 0x3894;
        if (func_02071298(param, &val) == 0) {
            return 0;
        }
    }
    return 1;
}
