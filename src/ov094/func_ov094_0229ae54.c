/* func_ov094_0229ae54 @ 0x0229ae54, 0x54 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a524(int, int);
extern int func_02088d9c(int);
extern int func_02088d94(int);

unsigned char func_ov094_0229ae54(int p0, int p1, int p2, int p3, int p4, unsigned char p5, unsigned char p6)
{
    int i;
    for (i = p5; i <= p6; i++) {
        int x;
        int y;
        int z;
        x = func_ov094_0229a524(p0, i);
        y = func_02088d9c(x);
        if (p1 >= y || y >= p3) {
            continue;
        }
        z = func_02088d94(x);
        if (p2 >= z || z >= p4) {
            continue;
        }
        return (unsigned char) i;
    }
    return 0x23;
}
