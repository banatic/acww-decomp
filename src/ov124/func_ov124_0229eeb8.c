/* func_ov124_0229eeb8 @ 0x0229eeb8, 0x50 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b1a4(void *p0, void *p1, void *p2, int p3);
extern void func_02088df8(int p0, void *p1, void *p2, void *p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10,
                          int p11);
extern int data_ov124_0229f5b0;

void func_ov124_0229eeb8(void *arg0, void *arg1, void *arg2)
{
    func_ov002_0220b1a4((char *) arg0 + 0x6c, arg1, arg2, -1);
    func_02088df8(1, &data_ov124_0229f5b0, (char *) arg1 + 0x80, (char *) arg2 + 0x60,
                  *(unsigned char *) ((char *) arg0 + 0xe9), 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
