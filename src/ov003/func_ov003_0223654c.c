/* func_ov003_0223654c @ 0x0223654c, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void *func_ov003_0223652c(void *obj);

void *func_ov003_0223654c(void)
{
    void *p;
    p = func_020edf70(0x50);
    if (p) {
        p = func_ov003_0223652c(p);
    }
    return p;
}
