/* func_ov003_0221ef44 @ 0x0221ef44, 0x2a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Vec3 {
    int x;
    int y;
    int z;
};

extern void func_020042c0(void *a, struct Vec3 *v);
extern void func_02004290(void *a, void *b);

void func_ov003_0221ef44(void *a, struct Vec3 *b, void *c)
{
    struct Vec3 local;

    local.x = b->x;
    local.y = b->y;
    local.z = b->z;
    func_020042c0(a, &local);
    func_02004290(a, c);
}
