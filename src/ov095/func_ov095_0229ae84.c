/* func_ov095_0229ae84 @ 0x0229ae84, 0x68 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov095_0229e714;
extern char data_ov095_0229e744;
extern void func_02088df8(int a, char *b, void *c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);

void func_ov095_0229ae84(void *p1, void *p2, void *p3)
{
    func_02088df8(1, &data_ov095_0229e714, p2, p3, ((unsigned char *) p1)[0x19], 1, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, &data_ov095_0229e744, p2, p3, ((unsigned char *) p1)[0x1a], 1, 0x1000, 0x1000, 0, -1, 0, 0);
}
