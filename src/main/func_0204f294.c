/* func_0204f294 @ 0x0204f294, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204f2b8(int a, int qx, int qy, int rx, int ry);

int func_0204f294(int a, int x, int y)
{
    int qx;
    int qy;
    int rx;
    int ry;

    qx = x >> 4;
    qy = y >> 4;
    ry = y - (qy << 4);
    rx = x - (qx << 4);

    return func_0204f2b8(a, qx, qy, rx, ry);
}
