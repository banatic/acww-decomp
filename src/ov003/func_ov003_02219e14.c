/* func_ov003_02219e14 @ 0x02219e14, 0x42 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, int c);

int func_ov003_02219e14(int p0, int p1)
{
    int x = 0, y = 0, z = 0, w = 0;
    func_0204f818(&x, &y, p1);
    func_0204f818(&z, &w, p0);
    if (x == z && y == w) {
        return 1;
    } else {
        return 0;
    }
}
