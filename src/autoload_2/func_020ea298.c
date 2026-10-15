/* func_020ea298 @ 0x020ea298, 0x74 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_0213e5a4;
extern int NNS_FndCreateExpHeapEx(void *p, void *q, unsigned short c);
extern void *func_020ea41c(void *a, void *p, void *q, int x, int r);

void *func_020ea298(void *a, void *b)
{
    char *q;
    char *p;
    int ret;

    q = (char *) b - 0x30;
    p = (char *) a + 0x30;
    ret = NNS_FndCreateExpHeapEx(p, q, data_0213e5a4);
    if (ret != 0) {
        if (a != 0) {
            func_020ea41c(a, p, q, 0, ret);
        }
        return a;
    }
    return 0;
}
