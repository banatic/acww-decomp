/* func_ov139_022999c4 @ 0x022999c4, 0x32 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_0229964c(void *, int, int, int);
extern void func_ov139_022995e4(void *, int, int, int);

void func_ov139_022999c4(void *p)
{
    int i;
    int a, b;
    i = 0;
    a = 0;
    b = 0;
    do {
        func_ov139_0229964c(p, i, a, 0xe);
        func_ov139_022995e4(p, i, b, 0xe);
        i++;
    } while (i < 6);
}
