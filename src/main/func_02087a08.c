/* func_02087a08 @ 0x02087a08, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_0204f800(int *, int *, int, int, int, int);
extern int func_02088024(int, int, int);

int func_02087a08(int unused, int *p, int b)
{
    int yEnd, xEnd;
    int vA = 0;
    int vB = 0;
    int count = 0;
    int x, y;

    func_0204f800(&vA, &vB, p[0], p[1], 0, 0);

    xEnd = vA + 16;
    yEnd = vB;
    yEnd += 16;

    for (y = vB; y < yEnd; y++) {
        for (x = vA; x < xEnd; x++) {
            if (func_02088024(x, y, b) != 0) {
                count++;
            }
        }
    }
    return count;
}
