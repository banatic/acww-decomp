/* func_ov095_0229b9e0 @ 0x0229b9e0, 0x2a bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229ba28(void *a, void *b);
extern int func_ov095_0229ba0c(void *a, void *b);

int func_ov095_0229b9e0(void *a, void *b)
{
    if (func_ov095_0229ba28(a, b) != 0 || func_ov095_0229ba0c(a, b) != 0) {
        return 1;
    }
    return 0;
}
