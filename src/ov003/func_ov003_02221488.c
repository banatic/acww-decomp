/* func_ov003_02221488 @ 0x02221488, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02222860(void *);
extern void func_020044a0(void *);

void func_ov003_02221488(void *p)
{
    int i;
    for (i = 0; i < 20; i++) {
        if (*(int *) ((char *) p + 4) != 0) {
            func_ov003_02222860(p);
        }
        func_020044a0((char *) p + 0x60);
        p = (char *) p + 0xa4;
    }
}
