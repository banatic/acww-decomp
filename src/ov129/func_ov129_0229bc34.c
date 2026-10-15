/* func_ov129_0229bc34 @ 0x0229bc34, 0x70 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_022996d8(unsigned int);
extern int func_ov127_022996c8(unsigned int);
extern int func_ov127_022996e4(unsigned short *, int, int);
extern int func_ov129_0229be7c(void *, unsigned short, unsigned int);

int func_ov129_0229bc34(void *arg0, unsigned int arg1)
{
    unsigned short local[10];
    int count;
    int i;
    int x, y;
    x = func_ov127_022996d8(arg1);
    y = func_ov127_022996c8(arg1);
    count = func_ov127_022996e4(local, x, y);
    for (i = 0; i < count; i++) {
        if (((unsigned char *) arg0 + local[i])[0x2f98] == 1) {
            return 0;
        }
    }
    for (i = 0; i < count; i++) {
        if (func_ov129_0229be7c(arg0, local[i], arg1) == 0) {
            return 1;
        }
    }
    return 3;
}
