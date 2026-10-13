/* func_02055e10 @ 0x02055e10, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_Copy36B(void *, void *);
extern void func_0210581c(void *, void *);
extern void func_021057f4(void *);
extern void NNS_G3dGlbFlushP(void);
extern unsigned int data_027e0148[];
extern char data_027e0184[];

void func_02055e10(void *p0, void *p1)
{
    volatile unsigned int *base;
    unsigned int arr[3];

    base = data_027e0148;
    MI_Copy36B((char *) p0 + 0x64, data_027e0184);
    base[0x1f] &= ~0xa4;
    func_0210581c((char *) p0 + 0x88, (void *) base);

    if (p1 == 0) {
        arr[2] = 0x1000;
        arr[1] = 0x1000;
        arr[0] = 0x1000;
        func_021057f4(arr);
    } else {
        func_021057f4(p1);
    }

    NNS_G3dGlbFlushP();
}
