/* func_02082374 @ 0x02082374, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char *func_020824d0(void *p);

int func_02082374(unsigned short *p)
{
    int result = 0;
    if ((*p & 0xF000) >> 12 == 13) {
        signed char *q = func_020824d0(p);
        if (q != 0) {
            result = q[result];
        }
    }
    return result;
}
