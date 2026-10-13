/* func_020edf70 @ 0x020edf70, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int sSubOBJExtPltt;
extern void *func_020e9ed4(int a, int b, int c);
extern void MI_CpuFill8(void *dest, unsigned char fill, unsigned int size);

void *func_020edf70(int size)
{
    void *p;
    p = func_020e9ed4(sSubOBJExtPltt, size, -4);
    if (p == 0) {
        return 0;
    }
    MI_CpuFill8(p, 0, size);
    return p;
}
