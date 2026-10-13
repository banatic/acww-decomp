/* func_ov119_0229adc4 @ 0x0229adc4, 0x4a bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov119_0229ae50(void);
extern int func_02077c3c(void *);
extern int func_02077e50(int);

void func_ov119_0229adc4(unsigned char *p)
{
    unsigned char *base;
    int i;
    int count;

    base = func_ov119_0229ae50();
    count = 0;
    for (i = 0; i < 0x20; i++) {
        if (func_02077e50(func_02077c3c(base + i * 0x24))) {
            (p + count)[0xbc] = i;
            count++;
        }
    }
    for (; count < 0x20; count++) {
        (p + count)[0xbc] = 0x20;
    }
}
