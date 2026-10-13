/* func_020310d0 @ 0x020310d0, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02032adc(void *ctx);
extern void func_02032acc(void *ctx);
extern int func_020311bc(void *ctx, Vec3 *b, Vec3 *a, int flags);
extern void func_02034270(void *big, Vec3 *pos, int c, int d);
extern int func_020341c8(void *big, int flag);
extern void func_0203423c(void *big);

int func_020310d0(Vec3 *pos, int *out, int flags)
{
    unsigned char ctx[0x14];
    Vec3 a;
    Vec3 b;
    unsigned char big[0x44];
    int r;

    func_02032adc(ctx);
    flags = flags & 0xfffffff9;
    a.x = pos->x;
    a.y = pos->y;
    a.z = pos->z;
    b.x = pos->x;
    b.y = pos->y;
    b.z = pos->z;
    a.y = 0x64000;
    b.y = -0x64000;
    if (func_020311bc(ctx, &b, &a, flags) != 0) {
        if (out != 0) {
            *out = ctx[0];
        }
        r = b.y;
        func_02032acc(ctx);
        return r;
    }
    func_02034270(big, pos, 0, 0);
    if (out != 0) {
        *out = *(int *) (big + 0x34);
    }
    r = func_020341c8(big, 0);
    func_0203423c(big);
    func_02032acc(ctx);
    return r;
}
