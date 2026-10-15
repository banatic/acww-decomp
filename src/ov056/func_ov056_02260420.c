/* func_ov056_02260420 @ 0x02260420, 0x2c bytes, Thumb, module ov056
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned long);
extern void *func_020ee660(void *arg0);
extern char data_020da13c;
extern char data_ov056_022604b0;

void *func_ov056_02260420(void)
{
    void *ret;
    volatile unsigned int *p;

    ret = func_020edf70(0x50);
    if (ret != 0) {
        func_020ee660((void *) ret);
        p = (volatile unsigned int *) ret;
        p[0] = (unsigned int) &data_020da13c;
        p[0] = (unsigned int) &data_ov056_022604b0;
    }
    return ret;
}
