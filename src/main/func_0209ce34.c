/* func_0209ce34 @ 0x0209ce34, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *, int, int);
extern unsigned char *func_0209cc30(void *, unsigned int, unsigned int);
extern int func_0209d034(int *record);
extern int func_02064328(int *, int, int, int);
extern int func_0206487c(int *);
extern int data_020e35d8;

int func_0209ce34(void *self)
{
    int sum;
    volatile int addend;
    unsigned int outer;
    unsigned int inner;
    unsigned char tmp[30];
    unsigned char buf[0x86];

    MI_CpuFill8(buf, 0, 0x86);
    sum = 0;
    outer = 0;
    addend = sum;
    for (; outer < 6; outer++) {
        for (inner = 0; inner < 6; inner++) {
            if (buf[func_0209d034((int *) func_0209cc30(self, inner, outer))] == 0) {
                {
                    int v = func_0209d034((int *) func_0209cc30(self, inner, outer));
                    func_02064328((int *) tmp, (int) &data_020e35d8, v >> 4, v);
                    sum += addend + func_0206487c((int *) tmp);
                }
                buf[func_0209d034((int *) func_0209cc30(self, inner, outer))] = 1;
            }
        }
    }
    return sum;
}
