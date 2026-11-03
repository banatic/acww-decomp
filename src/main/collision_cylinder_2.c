/* collision_cylinder_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203072c @ 0x0203072c, 0xc bytes, Thumb
 * func_0203071c @ 0x0203071c, 0x10 bytes, Thumb
 * func_02030718 @ 0x02030718, 0x2 bytes, Thumb
 * func_02030708 @ 0x02030708, 0x10 bytes, Thumb
 * func_020306a4 @ 0x020306a4, 0x62 bytes, Thumb
 * func_02030690 @ 0x02030690, 0x14 bytes, Thumb
 * func_02030678 @ 0x02030678, 0x18 bytes, Thumb
 * func_02030668 @ 0x02030668, 0x10 bytes, Thumb
 * func_02030658 @ 0x02030658, 0x10 bytes, Thumb
 * func_02030640 @ 0x02030640, 0x16 bytes, Thumb
 * func_020305b0 @ 0x020305b0, 0x90 bytes, Thumb
 * func_02030580 @ 0x02030580, 0x30 bytes, Thumb
 * func_020304d4 @ 0x020304d4, 0xac bytes, Thumb
 */

typedef struct {
    int x;
    int pad_04;
    int y;
    int threshold;
} Point;

struct UnkStruct_02030690 {
    char pad_00[16];
    int unk_10;
};

typedef struct {
    char unk_00[0x10];
    int unk_10;
} UnkStruct_02030678;

typedef struct UnkStruct_020305b0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020305b0_2;

typedef struct UnkStruct_020305b0_3 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020305b0_4;

typedef struct ObjA {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} ObjA;

typedef struct ObjB {
    int unk_00;
    int unk_04;
} ObjB;

typedef struct ObjC {
    int unk_00;
    int unk_04;
} ObjC;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C, unk_10;
} ObjA_020304d4;

typedef struct {
    int x, y, z;
} Vec3;

extern int FX_MulFunc(int, int);
extern int func_020ea990(UnkStruct_020305b0_2 *a, UnkStruct_020305b0_4 *b);
extern int func_020ea838(int *vec);
extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int FX_Div(int a, int b);

void func_02030708(void *dst, const void *src, unsigned int val);

void func_0203072c(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

int func_0203071c(int x, const void *argument1, unsigned int argument2)
{
    func_02030708((void *) x, (const void *) argument1, (unsigned int) argument2);
    return x;
}

void func_02030718(void) {}

void func_02030708(void *dst, const void *src, unsigned int val)
{
    unsigned int *d = (unsigned int *) dst;
    const unsigned int *s = (const unsigned int *) src;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = val;
}

int func_020306a4(Point *a, Point *b)
{
    int dx = b->x - a->x;
    int dy = b->y - a->y;
    int dy2, dx2, limit2;

    if ((dx < 0 ? -dx : dx) > a->threshold) {
        return 0;
    }
    if ((dy < 0 ? -dy : dy) > a->threshold) {
        return 0;
    }
    dy2 = FX_MulFunc(dy, dy);
    dx2 = FX_MulFunc(dx, dx);
    limit2 = FX_MulFunc(a->threshold, a->threshold);
    if (dx2 + dy2 > limit2) {
        return 0;
    }
    return 1;
}

struct UnkStruct_02030690 *func_02030690(struct UnkStruct_02030690 *arg)
{
    func_0203072c((int *) arg);
    arg->unk_10 = 0;
    return arg;
}

void *func_02030678(UnkStruct_02030678 *obj, int a, int b, int c)
{
    func_0203071c((int) obj, (const void *) a, (unsigned int) b);
    obj->unk_10 = c;
    return obj;
}

int func_02030668(int x)
{
    func_02030718();
    return x;
}

int func_02030658(int arg)
{
    func_02030718();
    return arg;
}

void func_02030640(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r3;
    func_02030708((void *) r0, (const void *) r1, (unsigned int) r2);
    *(int *) (r5 + 0x10) = r4;
}

int func_020305b0(UnkStruct_020305b0_2 *a, UnkStruct_020305b0_4 *b, int c)
{
    int ret;
    int vec[3];
    int val;
    int overlap;
    ret = func_020ea990(a, b);
    if (ret < (c + a->unk_0C)) {
        if (b->unk_04 < (a->unk_04 + a->unk_10)) {
            val = b->unk_08 - a->unk_08;
            vec[0] = b->unk_00 - a->unk_00;
            vec[1] = 0;
            vec[2] = val;
            if (func_020ea838(vec) != 0) {
                overlap = (c + a->unk_0C) - ret;
                b->unk_00 += FX_MulFunc(vec[0], overlap);
                b->unk_08 += FX_MulFunc(vec[2], overlap);
                return 1;
            }
        }
        goto return0;
    } else {
        if (ret > ((c + a->unk_0C) + 0x200)) {
            goto return0;
        }
        if (b->unk_04 >= (a->unk_04 + a->unk_10)) {
            goto return0;
        }
        return 1;
    }
return0:
    return 0;
}

int func_02030580(ObjA *a, ObjB *b, ObjC *c)
{
    int sum = a->unk_04 + a->unk_10;
    if (c->unk_04 >= sum && b->unk_04 < sum && func_020306a4((Point *) a, (Point *) b)) {
        b->unk_04 = sum;
        return 1;
    }
    return 0;
}

static __inline void VEC_Set(Vec3 *p, int x, int y, int z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

int func_020304d4(ObjA_020304d4 *a, Vec3 *b, Vec3 *c)
{
    int sum = a->unk_04 + a->unk_10;
    Vec3 c2;
    Vec3 b2;
    Vec3 result;
    Vec3 out;
    int t, yy, zz;

    VEC_Set(&c2, c->x, c->y, c->z);
    if (c2.y > sum) {
        VEC_Set(&b2, b->x, b->y, b->z);
        if (b2.y < sum) {
            func_020eaca0(&result, &b2, &c2);
            if (func_020ea838((int *) (&result)) != 0) {
                int ry = result.y;
                int ay = ry < 0 ? -ry : ry;
                if (ay >= 4) {
                    t = FX_Div(sum - c2.y, ry);
                    zz = c2.z + FX_MulFunc(result.z, t);
                    yy = c2.y + FX_MulFunc(result.y, t);
                    out.x = c2.x + FX_MulFunc(result.x, t);
                    out.y = yy;
                    out.z = zz;
                    if (func_020306a4((Point *) a, (Point *) (&out)) != 0) {
                        b->x = out.x;
                        b->y = out.y;
                        b->z = out.z;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
