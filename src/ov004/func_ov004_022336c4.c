/* func_ov004_022336c4 @ 0x022336c4, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022339e0(void *);
extern int func_020044a0(void *);

void func_ov004_022336c4(void *p)
{
    int i;
    for (i = 0; i < 15; i++) {
        if (*(int *) ((char *) p + 4) != 0) {
            func_ov004_022339e0(p);
        }
        func_020044a0((char *) p + 0x4c);
        p = (char *) p + 0x94;
    }
}
