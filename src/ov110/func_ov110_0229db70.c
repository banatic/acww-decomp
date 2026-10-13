/* func_ov110_0229db70 @ 0x0229db70, 0x34 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov110_0229c3b8(void *, int);
extern void func_ov110_0229c9e8(void *);

void func_ov110_0229db70(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x22e0)) {
        if (*(unsigned char *) ((char *) arg0 + 0xf5) == 0x1e) {
            func_ov110_0229c3b8(arg0, 1);
        } else {
            func_ov110_0229c9e8(arg0);
        }
    }
}
