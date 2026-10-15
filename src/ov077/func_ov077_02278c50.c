/* func_ov077_02278c50 @ 0x02278c50, 0x50 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200442c(void *dst, void *src, int size, int fill);
extern void func_ov003_02219648(void);

void func_ov077_02278c50(void *obj, int mode)
{
    switch (mode) {
        case 0:
            func_ov003_02219648();
            break;
        case 1:
            func_0200442c((char *) (*(int *) ((char *) obj + 0xb8)) + 0x514, (void *) 0x7f4, 0x7f, 0);
            break;
        case 2:
            func_0200442c((char *) (*(int *) ((char *) obj + 0xb8)) + 0x514, (void *) 0x7f5, 0x7f, 0);
            break;
    }
}
