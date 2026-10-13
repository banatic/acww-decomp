/* func_02090a2c @ 0x02090a2c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02090a2c {
    char pad[0x1C];
    unsigned int flags;
};

struct UnkStruct_02090a2c_2 {
    int first;
    char pad[8];
    struct UnkStruct_02090a2c *inner;
};

void func_02090a2c(struct UnkStruct_02090a2c_2 *p)
{
    struct UnkStruct_02090a2c *inner;
    inner = p->inner;
    if (inner != 0) {
        inner->flags = (inner->flags & ~1) | 1;
    }
    p->first = -1;
}
