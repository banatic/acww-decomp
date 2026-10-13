/* func_02056d0c @ 0x02056d0c, 0x154 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int fx32;
typedef long long fx64;
typedef unsigned long long u64;
typedef unsigned short vu16;
typedef unsigned int vu32;
typedef unsigned long long vu64;
typedef int s32;

typedef struct {
    fx32 x, y, z;
} VecFx32;

#define REG_CP_DIVCNT_ADDR 0x04000280
#define REG_DIV_NUMER_ADDR 0x04000290
#define REG_DIV_DENOM_ADDR 0x04000298
#define REG_DIV_RESULT_ADDR 0x040002a0
#define REG_CP_SQRTCNT_ADDR 0x040002b0
#define REG_SQRT_RESULT_ADDR 0x040002b4
#define REG_SQRT_PARAM_ADDR 0x040002b8

static __inline void CP_SetDiv64_64(u64 numer, u64 denom)
{
    *(volatile vu16 *) REG_CP_DIVCNT_ADDR = 2;
    *(volatile vu64 *) REG_DIV_NUMER_ADDR = numer;
    *(volatile vu64 *) REG_DIV_DENOM_ADDR = denom;
}

static __inline void CP_SetSqrt64(u64 param)
{
    *(volatile vu16 *) REG_CP_SQRTCNT_ADDR = 1;
    *(volatile vu64 *) REG_SQRT_PARAM_ADDR = param;
}

static __inline s32 CP_GetSqrtResult32(void)
{
    while (*(volatile vu16 *) REG_CP_SQRTCNT_ADDR & 0x8000) {
    }
    return *(volatile vu32 *) REG_SQRT_RESULT_ADDR;
}

static __inline fx64 CP_GetDivResult64(void)
{
    while (*(volatile vu16 *) REG_CP_DIVCNT_ADDR & 0x8000) {
    }
    return *(volatile fx64 *) REG_DIV_RESULT_ADDR;
}

void func_02056d0c(VecFx32 *v)
{
    fx64 t;
    s32 sq;

    t = (fx64) v->x * v->x;
    t += (fx64) v->y * v->y;
    t += (fx64) v->z * v->z;

    if (t != 0) {
        CP_SetDiv64_64(1LL << (12 + 12 + 32), (u64) t);
        CP_SetSqrt64((u64) (t << 2));

        sq = CP_GetSqrtResult32();
        t = CP_GetDivResult64();

        t = t * sq;
        v->x = (fx32) ((t * v->x + (1LL << (32 + 12))) >> (32 + 12 + 1));
        v->y = (fx32) ((t * v->y + (1LL << (32 + 12))) >> (32 + 12 + 1));
        v->z = (fx32) ((t * v->z + (1LL << (32 + 12))) >> (32 + 12 + 1));
    }
}
