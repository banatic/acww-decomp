/* villager_talk_scene_3: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202dac0 @ 0x0202dac0, 0x44 bytes, Thumb
 * func_0202da88 @ 0x0202da88, 0x36 bytes, Thumb
 * func_0202da74 @ 0x0202da74, 0x14 bytes, Thumb
 * func_0202da38 @ 0x0202da38, 0x3a bytes, Thumb
 * func_0202da08 @ 0x0202da08, 0x30 bytes, Thumb
 * func_0202d9dc @ 0x0202d9dc, 0x2c bytes, Thumb
 * func_0202d9d0 @ 0x0202d9d0, 0xc bytes, Thumb
 * func_0202d9c4 @ 0x0202d9c4, 0xc bytes, Thumb
 */

typedef struct Pair {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_0202dac0 {
    char pad_00[0xb0];
    Pair arr[3];
} UnkStruct_0202dac0;

typedef struct {
    int a;
    int b;
} UnkStruct_0202da74;

typedef struct {
    unsigned char pad_00[0xd0];
    UnkStruct_0202da74 v;
} UnkStruct_0202da74_2;

typedef struct {
    char pad_00[0x100];
    int member;
} UnkStruct_0202da08;

extern Pair __ptmf_null;
extern int func_0200368c(int a, int b, int c, int d);
extern int func_020644cc(int a);
extern int func_0201ce50(int);
extern int func_02015d60(void *a);

void func_0202dac0(UnkStruct_0202dac0 *p)
{
    Pair tmp;
    p->arr[0] = __ptmf_null;
    tmp = __ptmf_null;
    p->arr[1] = tmp;
    p->arr[2] = tmp;
}

void func_0202da88(unsigned long long *dst, const unsigned long long *src)
{
    dst[0x16] = src[0];
    dst[0x17] = src[1];
    dst[0x18] = src[2];
}

void func_0202da74(UnkStruct_0202da74_2 *p, UnkStruct_0202da74 v)
{
    p->v = v;
}

int func_0202da38(int p0, int p1, unsigned char *p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    int result;

    unsigned char product;
    unsigned char selected;
    product = (unsigned char) ((*(unsigned char *) &p6) * p7);
    selected = (*(unsigned char *) &p6);
    if ((*(unsigned char *) &p8)) {
        selected = (*(unsigned char *) &p8);
    }
    func_0200368c(p1, p3, p5, (*(unsigned char *) &p4));
    result = product + func_020644cc(selected);
    *p2 = (unsigned char) result;
    return result;
}

int func_0202da08(UnkStruct_0202da08 *base, int mode)
{
    int v;

    switch (mode) {
        case 0:
            return base->member;
        case 1:
            v = base->member;
            if (v != 0) {
                return func_0201ce50(v);
            }
            // fall through
        default:
            return 0;
    }
}

void *func_0202d9dc(void *a)
{
    void *result = 0;
    int t = func_02015d60(a);
    void *p = (void *) func_0202da08((UnkStruct_0202da08 *) a, t);
    if (p) {
        result = *(void **) ((char *) p + 0x830);
    }
    return result;
}

void func_0202d9d0(unsigned int *ptr, unsigned int value)
{
    ptr[0x55] = value;
}

unsigned int func_0202d9c4(unsigned int *r0)
{
    return r0[0x55];
}
