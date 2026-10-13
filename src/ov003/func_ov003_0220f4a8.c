/* func_ov003_0220f4a8 @ 0x0220f4a8, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0220f4a8 {
    int x;
    int y;
    int z;
};

extern void func_020109a0(void *a, int b, int c, int d);
extern void func_ov003_0220f524(void *a, struct UnkStruct_0220f4a8 s);
extern void func_ov003_0220f508(void *a, struct UnkStruct_0220f4a8 *s);

void func_ov003_0220f4a8(void *self, void *other)
{
    struct UnkStruct_0220f4a8 local;
    struct UnkStruct_0220f4a8 *src;

    func_020109a0(self, 0x7a, 3, 0);
    src = (struct UnkStruct_0220f4a8 *) ((char *) other + 0xc);
    local.x = src->x;
    local.y = src->y;
    local.z = src->z;
    func_ov003_0220f524((char *) self + 0x7d4, local);
    func_ov003_0220f508((char *) self + 0x8f0, &local);
}
