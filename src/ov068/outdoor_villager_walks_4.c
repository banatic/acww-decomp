/* outdoor_villager_walks_4: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226c820 @ 0x0226c820, 0x90 bytes, Thumb
 * func_ov068_0226c7dc @ 0x0226c7dc, 0x44 bytes, Thumb
 * func_ov068_0226c7bc @ 0x0226c7bc, 0x20 bytes, Thumb
 * func_ov068_0226c754 @ 0x0226c754, 0x66 bytes, Thumb
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3_0226c8;

typedef struct UnkStruct_0226c7dc {
    char pad_00[0x5c];
    char unk_5C;
    char pad_5D[0x37];
    short unk_94;
    char pad_96[2];
    int unk_98;
} UnkStruct_0226c7dc;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    Vec3 v;
} UnkStruct_0226c754;

extern int func_0203dff0(void);
extern int func_020eaa2c(void *, void *);
extern int func_02096190(int);
extern int func_0203dfac(void);
extern void func_020eaca0(void *, void *, void *);
extern int FX_MulFunc(int, int);
extern unsigned char data_021fbee8[];
extern void func_020ea6e0(void *buf, int val);
extern void func_020eaaa8(Vec3 *dst, int scale);
extern void func_01ffd070(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern int func_020ea990(int v, const Vec3 *vec);

int func_ov068_0226c820(void *self, void *arg1, Vec3_0226c8 *arg2)
{
    int t4;
    int t6;
    Vec3_0226c8 v1;
    Vec3_0226c8 v2;
    int diff1;
    int diff2;

    if (func_0203dff0() == 0) {
        goto fail;
    }
    if (func_020eaa2c(arg2, (void *) data_021fbee8) == 0) {
        goto fail;
    }

    t4 = func_02096190(4);
    t6 = func_0203dfac();
    if (t4 == 0) {
        goto fail;
    }
    if (t6 == 0) {
        goto fail;
    }

    func_020eaca0(&v1, (char *) t4 + 0x5c, arg1);
    func_020eaca0(&v2, (char *) t6 + 0x5c, arg1);

    diff1 = FX_MulFunc(arg2->x, v1.z) - FX_MulFunc(arg2->z, v1.x);
    diff2 = FX_MulFunc(arg2->x, v2.z) - FX_MulFunc(arg2->z, v2.x);

    if (FX_MulFunc(diff1, diff2) > 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

int func_ov068_0226c7dc(void *a, UnkStruct_0226c7dc *b)
{
    int local[3];

    if (b->unk_98 != 0) {
        local[0] = 0;
        local[1] = 0;
        local[2] = 0x1000;
        func_020ea6e0(local, b->unk_94);
        return func_ov068_0226c820(a, &b->unk_5C, (Vec3_0226c8 *) local);
    } else {
        return 0;
    }
}

int func_ov068_0226c7bc(void *a, void *b, void *c)
{
    char sp[12];
    func_020eaca0(sp, b, c);
    return func_ov068_0226c820(a, c, (Vec3_0226c8 *) sp);
}

int func_ov068_0226c754(int a, int b, int c)
{
    if (func_0203dff0()) {
        UnkStruct_0226c754 *p1 = (UnkStruct_0226c754 *) func_02096190(4);
        UnkStruct_0226c754 *p2 = (UnkStruct_0226c754 *) func_0203dfac();
        if (p1 != 0 && p2 != 0) {
            Vec3 v1, v2;
            func_020eaca0((void *) (&v1), (void *) (&p1->v), (void *) (&p2->v));
            func_020eaaa8(&v1, 1);
            func_01ffd070(&v2, &p1->v, &v1);
            {
                int r = func_020ea990(b, &v2);
                if (r < 0) {
                    r = -r;
                }
                if (r <= c) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
