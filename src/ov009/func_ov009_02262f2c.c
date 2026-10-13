/* func_ov009_02262f2c @ 0x02262f2c, 0x26 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    unsigned char flag;
} UnkStruct_02262f2c;

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Triple;

extern void func_020044d0(UnkStruct_02262f2c *a, Triple *t);

void func_ov009_02262f2c(UnkStruct_02262f2c *a, Triple *b)
{
    if (a->flag != 0) {
        Triple local;
        local.x = b->x;
        local.y = b->y;
        local.z = b->z;
        func_020044d0(a, &local);
    }
}
