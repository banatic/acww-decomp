/* room_object_parts_4: 13 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220da50 @ 0x0220da50, 0x2 bytes, Thumb
 * func_ov004_0220da44 @ 0x0220da44, 0xa bytes, Thumb
 * func_ov004_0220da38 @ 0x0220da38, 0xc bytes, Thumb
 * func_ov004_0220da2c @ 0x0220da2c, 0xc bytes, Thumb
 * func_ov004_0220da20 @ 0x0220da20, 0xc bytes, Thumb
 * func_ov004_0220da14 @ 0x0220da14, 0xc bytes, Thumb
 * func_ov004_0220da10 @ 0x0220da10, 0x4 bytes, Thumb
 * func_ov004_0220da04 @ 0x0220da04, 0xa bytes, Thumb
 * func_ov004_0220d9f8 @ 0x0220d9f8, 0xc bytes, Thumb
 * func_ov004_0220d9ec @ 0x0220d9ec, 0xc bytes, Thumb
 * func_ov004_0220d9e0 @ 0x0220d9e0, 0xc bytes, Thumb
 * func_ov004_0220d9d4 @ 0x0220d9d4, 0xc bytes, Thumb
 * func_ov004_0220d9bc @ 0x0220d9bc, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[40];
    unsigned long unk_28;
} UnkStruct_0220da10;

extern unsigned int func_021077e8(unsigned int *resource);

void func_ov004_0220da50(void *object) {}

void func_ov004_0220da44(int *p, int v, int i)
{
    p[i & 1] = v;
}

void func_ov004_0220da38(void *self, int v, int i)
{
    *(int *) ((char *) self + ((i & 1) << 2) + 0x8) = v;
}

void func_ov004_0220da2c(void *self, int v, int i)
{
    *(int *) ((char *) self + ((i & 1) << 2) + 0x10) = v;
}

void func_ov004_0220da20(void *self, int v, int i)
{
    *(int *) ((char *) self + ((i & 1) << 2) + 0x18) = v;
}

void func_ov004_0220da14(void *self, int v, int i)
{
    *(int *) ((char *) self + ((i & 1) << 2) + 0x20) = v;
}

void func_ov004_0220da10(UnkStruct_0220da10 *p, unsigned long v)
{
    p->unk_28 = v;
}

int func_ov004_0220da04(int *p, int i)
{
    return p[i & 1];
}

int func_ov004_0220d9f8(void *self, int i)
{
    return *(int *) ((char *) self + ((i & 1) << 2) + 0x8);
}

int func_ov004_0220d9ec(void *self, int i)
{
    return *(int *) ((char *) self + ((i & 1) << 2) + 0x10);
}

int func_ov004_0220d9e0(void *self, int i)
{
    return *(int *) ((char *) self + ((i & 1) << 2) + 0x18);
}

int func_ov004_0220d9d4(void *self, int i)
{
    return *(int *) ((char *) self + ((i & 1) << 2) + 0x20);
}

int func_ov004_0220d9bc(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x28) != 0x0) {
        return func_021077e8((unsigned int *) *(int *) (self + 0x28));
    }
    return 0x0;
}
