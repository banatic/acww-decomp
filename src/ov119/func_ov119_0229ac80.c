/* func_ov119_0229ac80 @ 0x0229ac80, 0x34 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov119_0229ae50(void *receiver);
extern int func_02077c3c(char *p);
extern int func_02077e50(int x);

int func_ov119_0229ac80(void *receiver)
{
    int i;
    char *p;
    p = func_ov119_0229ae50(receiver);
    for (i = 0; i < 32; i++) {
        if (func_02077e50(func_02077c3c(p)) == 0) {
            return i;
        }
        p += 0x24;
    }
    return -1;
}
