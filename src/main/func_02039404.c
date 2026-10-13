/* func_02039404 @ 0x02039404, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021c6738;
extern int data_020ca144[];
extern int data_020ca134[];
extern void func_02039efc(unsigned char *p, int i, int a, int b);

void func_02039404(unsigned char *base)
{
    int i;

    data_021c6738 = base;
    for (i = 0; i < 4; i++) {
        func_02039efc(base + 4 + i * 0xB8, i, data_020ca144[i], data_020ca134[i]);
    }
}
