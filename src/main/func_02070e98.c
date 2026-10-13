/* func_02070e98 @ 0x02070e98, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02071298(void *p, unsigned short *v);

int func_02070e98(void *p)
{
    unsigned int i;
    unsigned short val;
    for (i = 0; i < 56; i++) {
        val = (i < 56) ? (unsigned short) (i + 0x12e8) : 0x12e8;
        if (func_02071298(p, &val) == 0) {
            return 0;
        }
    }
    return 1;
}
