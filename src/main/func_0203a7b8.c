/* func_0203a7b8 @ 0x0203a7b8, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct UnkStruct_0203a7b8 {
    int pad_00;
    int m[4][3];
    int pad_34[7];
    int low;
    int high;
} UnkStruct_0203a7b8;

extern int FX_MulFunc(int a, int b);
extern void MTX_MultVec43(int a, int b, Vec *c);

int func_0203a7b8(UnkStruct_0203a7b8 *self, int a1, int a2, int threshold, Vec *vec)
{
    int s1, t1, u1;
    int s2, t2, u2;
    int s3, t3, u3;
    int s4, t4, u4;

    MTX_MultVec43(a2, a1, vec);

    if (-vec->z < self->low - threshold) {
        return 0x7fffffff;
    }
    if (-vec->z > self->high + threshold) {
        return 0x7fffffff;
    }

    s1 = FX_MulFunc(vec->z, self->m[0][2]);
    t1 = FX_MulFunc(vec->x, self->m[0][0]);
    u1 = FX_MulFunc(vec->y, self->m[0][1]);
    if (s1 + (t1 + u1) > threshold) {
        return 0x7fffffff;
    }

    s2 = FX_MulFunc(vec->z, self->m[1][2]);
    t2 = FX_MulFunc(vec->x, self->m[1][0]);
    u2 = FX_MulFunc(vec->y, self->m[1][1]);
    if (s2 + (t2 + u2) > threshold) {
        return 0x7fffffff;
    }

    s3 = FX_MulFunc(vec->z, self->m[2][2]);
    t3 = FX_MulFunc(vec->x, self->m[2][0]);
    u3 = FX_MulFunc(vec->y, self->m[2][1]);
    if (s3 + (t3 + u3) > threshold) {
        return 0x7fffffff;
    }

    s4 = FX_MulFunc(vec->z, self->m[3][2]);
    t4 = FX_MulFunc(vec->x, self->m[3][0]);
    u4 = FX_MulFunc(vec->y, self->m[3][1]);
    if (s4 + (t4 + u4) > threshold) {
        return 0x7fffffff;
    }

    return -vec->z;
}
