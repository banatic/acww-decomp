/* func_02083d1c @ 0x02083d1c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f7e0(int a, void *p);

int func_02083d1c(int a, int b, unsigned short *c, int *d)
{
    struct {
        int x;
        int y;
        int z;
    } local;
    int t = d[2] + 0x6000;

    local.x = d[0] - 0x4000;
    local.y = 0;
    local.z = t;
    func_0204f7e0(b, &local);
    c[1] = 0;
    return 1;
}
