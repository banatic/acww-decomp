/* func_ov143_022999a4 @ 0x022999a4, 0x94 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov143_022997d8(unsigned int a, unsigned int b);
extern void func_02089300(int p1, void *p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9);
extern void func_02088df8(int p1, void *p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12);

extern void *data_ov143_0229b178[];
extern unsigned char data_ov143_0229af08[];
extern unsigned char data_ov143_0229b038[];
extern unsigned char data_ov143_0229b050[];

void func_ov143_022999a4(int a, unsigned int b, int c, int d)
{
    void *p;
    int result;
    int diff;
    unsigned int field;
    void *ptr;

    p = data_ov143_0229b178[b];
    result = func_ov143_022997d8(a, b);
    diff = d - (result << 1);

    if (b == 15) {
        func_02089300(1, data_ov143_0229af08, c - 0x5c, diff - 0x18, -1, 2, 0x1000, 0xeaab, 0);
    } else {
        field = (*(unsigned int *) ((char *) p + 0x14) << 16) >> 28;
        if (b < 6 || b == 14) {
            ptr = data_ov143_0229b038;
        } else {
            ptr = data_ov143_0229b050;
        }
        func_02088df8(1, ptr, c, diff, field, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
