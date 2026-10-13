/* func_ov129_0229c8b8 @ 0x0229c8b8, 0x34 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov129_0229c644(void *);
extern void func_ov129_0229c684(void *);

void func_ov129_0229c8b8(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x3a0) != 0) {
        if (*(unsigned char *) ((char *) arg0 + 0xaf) != 0) {
            func_ov129_0229c644(arg0);
        } else {
            func_ov129_0229c684(arg0);
        }
    }
}
