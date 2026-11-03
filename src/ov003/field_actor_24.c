/* field_actor_24: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02211df8 @ 0x02211df8, 0x40 bytes, Thumb
 * func_ov003_02211db0 @ 0x02211db0, 0x46 bytes, Thumb
 * func_ov003_02211da0 @ 0x02211da0, 0x10 bytes, Thumb
 */

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_02211db0;

struct Dst {
    char tag;
    int x;
    int y;
    int z;
};

struct Src {
    int x;
    int y;
    int z;
};

extern int func_02056f94(int);
extern int func_02008258(int, int);
extern int func_0200d4e8(int, int, int, int);
extern void func_ov003_02211e38(UnkStruct_02211db0 *obj);
extern int func_0201100c(UnkStruct_02211db0 *obj);
extern void func_02010d64(UnkStruct_02211db0 *obj);
extern unsigned int func_02011398(int a, int b);
extern void func_0201107c(UnkStruct_02211db0 *obj, unsigned int *p);

void func_ov003_02211df8(int r0)
{
    int r4;
    int r1;
    int r2;
    int r3;

    r4 = r0;
    if (func_02056f94(r4 + 0x2d0) != 0) {
        r1 = *(int *) (r4 + 0x7f0);
        r0 = func_02008258(r4, r1);
        *(int *) (r4 + 0x7fc) = r0;
        func_0200d4e8(r4, 3, 1, -1);
    }
}

void func_ov003_02211db0(UnkStruct_02211db0 *obj)
{
    int val;
    unsigned int result;
    unsigned int tmp;

    func_ov003_02211e38(obj);
    func_0201100c(obj);
    func_02010d64(obj);

    val = obj->unk_98;
    if (val < 0) {
        val = -val;
    }

    result = func_02011398(val, 0);
    tmp = result * -1;

    func_0201107c(obj, &tmp);
    func_ov003_02211df8((int) obj);
}

void func_ov003_02211da0(struct Dst *dst, char tag, const struct Src *src)
{
    dst->tag = tag;
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}
