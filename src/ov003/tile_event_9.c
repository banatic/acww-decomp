/* tile_event_9: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02221304 @ 0x02221304, 0x3c bytes, Thumb
 * func_ov003_02221294 @ 0x02221294, 0x70 bytes, Thumb
 * func_ov003_02221228 @ 0x02221228, 0x6c bytes, Thumb
 * func_ov003_022211bc @ 0x022211bc, 0x6c bytes, Thumb
 * func_ov003_02221150 @ 0x02221150, 0x6c bytes, Thumb
 * func_ov003_02221118 @ 0x02221118, 0x38 bytes, Thumb
 * func_ov003_022210d4 @ 0x022210d4, 0x44 bytes, Thumb
 * func_ov003_02221094 @ 0x02221094, 0x40 bytes, Thumb
 * func_ov003_02221054 @ 0x02221054, 0x40 bytes, Thumb
 */

#include "types.h"

struct Pair {
    int x;
    int y;
};

struct UnkStruct_02221094 {
    int a;
    int b;
};

struct UnkStruct_02221094_2 {
    int a;
    int b;
    int c;
};

typedef struct {
    unsigned int a, b;
} UnkStruct_02221054;

typedef struct {
    unsigned int a, b, c;
} UnkStruct_02221054_2;

extern int func_ov003_022213f8(u32 *data, u32 a0, u32 *a, u32 *b, u32 z1, u32 a1, u32 z2, u32 z3);
extern void func_0204f818(int *a, int *b, int c);
extern int func_ov003_0222139c(int a0, int a1, int *a2, int *a3, int a4, int a5, int a6, int a7);
extern char data_ov003_0223cfe4[];
extern int func_0204e414(void);
extern int func_0204eda8(int obj, int x, int y);
extern int func_02045cec(int *, int);
extern void *func_02045bac(int index);

int func_ov003_02221304(u32 p0, u32 p1, u32 *p2, u32 *p3)
{
    u32 a[2];
    u32 b[3];

    b[0] = p3[0];
    b[1] = p3[1];
    b[2] = p3[2];
    a[0] = p2[0];
    a[1] = p2[1];
    return func_ov003_022213f8(((u32 *) data_ov003_0223cfe4), p0, a, b, 0, p1, 0, 0);
}

int func_ov003_02221294(int arg0, int arg1, int arg2)
{
    void *ctx;
    int a, b, flag;
    int pair[2];
    int triple[3];

    ctx = (void *) func_0204e414();
    if (ctx == 0) {
        return 0;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, arg1);

    flag = (func_0204eda8((int) ctx, a, b) == 0) ? 0xFC : 0xFD;

    triple[0] = 0;
    triple[1] = 0;
    triple[2] = 0;
    pair[0] = a;
    pair[1] = b;

    return func_ov003_0222139c((int) data_ov003_0223cfe4, arg0, pair, triple, 1, flag, 0, arg2);
}

int func_ov003_02221228(int a, int b)
{
    int r6;         // returned from func_0204e414
    int x, y;       // coordinates
    int status;     // result from func_0204eda8
    int code;       // 0xFC or 0xFD
    struct Pair pr; // pair to pass
    int arr[3];     // zeroed array

    r6 = func_0204e414();
    if (r6 == 0) {
        return 0;
    }

    x = 0;
    y = 0;
    func_0204f818(&x, &y, b);

    status = func_0204eda8(r6, x, y);
    code = (status == 0) ? 0xFC : 0xFD;

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;

    pr.x = x;
    pr.y = y;

    return func_ov003_0222139c((int) (((char *) data_ov003_0223cfe4)), a, (int *) (&pr), arr, 2, code, 0, 0);
}

int func_ov003_022211bc(int p0, int p1)
{
    int r6;
    int a, b;
    int x;
    int s1[2];
    int s2[3];

    r6 = func_0204e414();
    if (r6 == 0) {
        return 0;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, p1);

    x = (func_0204eda8(r6, a, b) == 0) ? 0xfc : 0xfd;

    s2[0] = 0;
    s2[1] = 0;
    s2[2] = 0;
    s1[0] = a;
    s1[1] = b;

    return func_ov003_0222139c((int) ((void *) ((int *) data_ov003_0223cfe4)), p0, s1, s2, 3, x, 0, 0);
}

void func_ov003_02221150(int a0, int a1)
{
    int out[2];
    int copy[2];
    int pos[2];
    int extra[3];
    unsigned short flag;
    int index;

    out[0] = 0;
    out[1] = 0;
    flag = 0xfff1;
    func_0204f818(&out[0], &out[1], a1);

    copy[0] = out[0];
    copy[1] = out[1];

    if ((index = func_02045cec(copy, 0)) >= 0) {
        void *q = func_02045bac(index);
        if (q != 0) {
            flag = *(unsigned short *) ((char *) q + 0xa);
        }
    }

    extra[0] = 0;
    extra[1] = 0;
    extra[2] = 0;
    pos[0] = out[0];
    pos[1] = out[1];

    func_ov003_0222139c((int) (((char *) data_ov003_0223cfe4)), a0, pos, extra, 3, (unsigned short) flag, 0, 0);
}

int func_ov003_02221118(int a, int b, int *p)
{
    int pair[2];
    int triple[3];
    triple[0] = 0;
    triple[1] = 0;
    triple[2] = 0;
    pair[0] = p[0];
    pair[1] = p[1];
    return func_ov003_022213f8((u32 *) (((int *) data_ov003_0223cfe4)), a, (u32 *) pair, (u32 *) triple, 4, b, 0, 0);
}

void func_ov003_022210d4(int self, int arg1, int *p2, int *p3, short arg4, int arg5)
{
    int local2[2];
    int local3[3];

    local3[0] = p3[0];
    local3[1] = p3[1];
    local3[2] = p3[2];
    local2[0] = p2[0];
    local2[1] = p2[1];

    func_ov003_022213f8((u32 *) (((int *) data_ov003_0223cfe4)), self, (u32 *) local2, (u32 *) local3, 5, arg1, (short) arg4,
                        arg5);
}

void func_ov003_02221094(int a0, int a1, struct UnkStruct_02221094 *p2, struct UnkStruct_02221094_2 *p3, int a4)
{
    struct UnkStruct_02221094_2 local3;
    struct UnkStruct_02221094 local2;

    local3.a = p3->a;
    local3.b = p3->b;
    local3.c = p3->c;
    local2.a = p2->a;
    local2.b = p2->b;

    func_ov003_022213f8((u32 *) (((char *) data_ov003_0223cfe4)), a0, (u32 *) (&local2), (u32 *) (&local3), 6, a1, 0, a4);
}

void func_ov003_02221054(void *arg1, unsigned int arg2, UnkStruct_02221054 *arg3, UnkStruct_02221054_2 *arg4)
{
    UnkStruct_02221054 local2;
    UnkStruct_02221054_2 local3;
    local3.a = arg4->a;
    local3.b = arg4->b;
    local3.c = arg4->c;
    local2.a = arg3->a;
    local2.b = arg3->b;
    func_ov003_022213f8((u32 *) (((char *) data_ov003_0223cfe4)), (u32) arg1, (u32 *) (&local2), (u32 *) (&local3), 7, arg2, 0,
                        0);
}
