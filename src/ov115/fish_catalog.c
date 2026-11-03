/* fish_catalog: 4 functions, module ov115
 * mwccarm 1.2/base -O4,s
 * func_ov115_0229ddf8 @ 0x0229ddf8, 0x18 bytes, Thumb
 * func_ov115_0229ddd0 @ 0x0229ddd0, 0x28 bytes, Thumb
 * func_ov115_0229ddb8 @ 0x0229ddb8, 0x18 bytes, Thumb
 * func_ov115_0229dda8 @ 0x0229dda8, 0x10 bytes, Thumb
 */

struct UnkStruct_0229ddb8 {
    unsigned char pad_00[0x1428];
    unsigned short flags;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *p);

void func_ov115_0229ddf8(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x94);
    func_ov002_02208098((void *) (self), 4);
}

unsigned char *func_ov115_0229ddd0(unsigned char *p)
{
    func_ov002_0220a164(p + 0x94);
    p[0x142c] = p[0x8d];
    return func_ov002_02208098((void *) (p), 5);
}

int func_ov115_0229ddb8(struct UnkStruct_0229ddb8 *p, unsigned short mask)
{
    return (p->flags & mask) != 0;
}

void func_ov115_0229dda8(char *p, unsigned short mask)
{
    *((unsigned short *) (p + 0x1428)) |= mask;
}
