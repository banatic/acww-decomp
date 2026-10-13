/* func_ov003_0222c41c @ 0x0222c41c, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void *func_020edf70(unsigned int n);
void *func_ov003_02228e8c(void *p);

void *func_ov003_0222c41c(void)
{
    void *p = func_020edf70(0x88);
    if (p != 0) {
        p = func_ov003_02228e8c(p);
    }
    return p;
}
