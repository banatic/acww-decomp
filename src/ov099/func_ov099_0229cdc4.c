/* func_ov099_0229cdc4 @ 0x0229cdc4, 0x40 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229bba4(void *, int arg1, int arg2);
extern int func_ov094_0229b30c(void *, int);
extern int func_ov099_0229ce04(void *, int);

int func_ov099_0229cdc4(void *p1, int p2, int p3, int p4)
{
    int result = func_ov094_0229bba4((char *) p1 + 0xb2c, p2, p3);
    if (result != 0x37) {
        if (p4 != 0 && func_ov094_0229b30c((char *) p1 + 0xb2c, result) != 0) {
            return 29;
        }
        return func_ov099_0229ce04(p1, result);
    } else {
        return 29;
    }
}
