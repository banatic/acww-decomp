/* collision_query_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020311bc @ 0x020311bc, 0xcc bytes, Thumb
 * func_02031168 @ 0x02031168, 0x54 bytes, Thumb
 * func_020310d0 @ 0x020310d0, 0x98 bytes, Thumb
 * func_020310c8 @ 0x020310c8, 0x8 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    void *vtable;
    Vec3 *src;
    Vec3 b;
    int flags;
    unsigned char unk_18;
    unsigned char pad[3];
} Block;

typedef struct {
    int pad_00;
    int pad_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} Result;

typedef struct {
    char pad[8];
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020311bc;

extern char data_020da1d4;
extern void func_02031e08(Vec3 *dst, Vec3 *src);
extern void func_02031e28(Vec3 *dst, Vec3 *src);
extern void func_02031e74(Block *block);
extern void func_0203429c(Result *result);
extern void func_02030ebc(Vec3 *b1, Vec3 *b2, Block *block, int flags, int arg5, int arg6);
extern void func_02034280(UnkStruct_020311bc *out, Result *result);
extern void func_02034298(Result *result);
extern void func_02031e68(Block *block);
extern void *func_02032adc(void *ctx);
extern int func_02032acc(void *ctx);
extern int func_02034270(void *big, Vec3 *pos, int c, int d);
extern int func_020341c8(void *big, int flag);
extern void func_0203423c(void *big);

int func_020311bc(UnkStruct_020311bc *out, Vec3 *a_ptr, Vec3 *b_ptr, int flags)
{
    Vec3 a, b1, b2;
    Block block;
    Result result;
    int ret;

    a.x = a_ptr->x;
    a.y = a_ptr->y;
    a.z = a_ptr->z;
    b1.x = b_ptr->x;
    b1.y = b_ptr->y;
    b1.z = b_ptr->z;
    b2.x = b_ptr->x;
    b2.y = b_ptr->y;
    b2.z = b_ptr->z;

    func_02031e08(&b1, &a);
    func_02031e28(&b2, &a);

    func_02031e74(&block);
    block.vtable = &data_020da1d4;

    func_0203429c(&result);

    result.unk_14 = 0;

    block.src = &a;
    block.b.x = b_ptr->x;
    block.b.y = b_ptr->y;
    block.b.z = b_ptr->z;
    block.flags = flags;
    block.unk_18 = 0;

    result.unk_18 = 0;
    result.unk_1C = 0;
    result.unk_20 = 0;

    func_02030ebc(&b1, &b2, &block, flags, 1, 0);

    if ((flags & 8) != 0) {
        a_ptr->x = a.x;
        a_ptr->y = a.y;
        a_ptr->z = a.z;
    }

    out->unk_08 = result.unk_08;
    out->unk_0C = result.unk_0C;
    out->unk_10 = result.unk_10;

    func_02034280(out, &result);

    ret = block.unk_18;
    block.vtable = &data_020da1d4;
    func_02034298(&result);
    func_02031e68(&block);

    return ret;
}

int func_02031168(int *out, int p1, const int *in, int p4, int p5)
{
    int s4 = p4 >> 1;
    int s5 = p5 >> 1;
    int a = in[0];
    int low1 = p1 + (a - s4);
    int high1 = (a + s4) - p1;
    int b = in[2];
    int low2 = p1 + (b - s5);
    int high2 = (b + s5) - p1;
    int changed = 0;

    if (out[0] < low1) {
        out[0] = low1;
        changed = 1;
    } else if (out[0] > high1) {
        out[0] = high1;
        changed = 1;
    }

    if (out[2] < low2) {
        out[2] = low2;
        changed = 1;
    } else if (out[2] > high2) {
        out[2] = high2;
        changed = 1;
    }

    return changed;
}

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
    if (func_020311bc((UnkStruct_020311bc *) ctx, &b, &a, flags) != 0) {
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

int func_020310c8(int value)
{
    return 512;
}
