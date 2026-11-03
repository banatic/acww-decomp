/* event_schedule_4: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02041298 @ 0x02041298, 0x8 bytes, Thumb
 * func_02041294 @ 0x02041294, 0x2 bytes, Thumb
 * func_020411fc @ 0x020411fc, 0x96 bytes, Thumb
 * func_020411f4 @ 0x020411f4, 0x8 bytes, Thumb
 * func_02041194 @ 0x02041194, 0x60 bytes, Thumb
 * func_02041140 @ 0x02041140, 0x52 bytes, Thumb
 * func_02041110 @ 0x02041110, 0x30 bytes, Thumb
 * func_020410ec @ 0x020410ec, 0x24 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 b[16];        // 0x00-0x0f
    u8 unk_10;       // 0x10
    u8 unk_11;       // 0x11
    u8 pad_12[0x22]; // 0x12-0x33
    u32 unk_34;      // 0x34
    u32 unk_38;      // 0x38
} UnkStruct_020411fc;

typedef struct {
    u8 v[4];
} Blk;

extern void func_0209df64(u8 *dst);
extern int func_020644cc(int arg);
extern void func_0204101c(UnkStruct_020411fc *p);
extern void func_02040c90(UnkStruct_020411fc *p, int arg);
extern int func_0209dcdc(void *, void *);
extern void func_0203fe58(int);
extern void func_02041788(void);
extern void func_0209e29c(int, int);
extern int func_0203fbb0(void *, int, void *);
extern void MI_CpuCopy8(int, void *, int);

void func_02041298(int *p0)
{
    p0[13] = 0;
    p0[14] = 0;
}

void func_02041294(void *object) {}

void func_020411fc(UnkStruct_020411fc *out)
{
    u8 buf[16];

    func_0209df64(buf);

    *(Blk *) (buf + 4) = *(Blk *) buf;

    out->b[0] = buf[4];
    out->b[1] = buf[5];
    out->b[2] = buf[6];
    out->b[3] = buf[7];

    *(Blk *) (buf + 8) = *(Blk *) buf;

    out->b[4] = buf[8];
    out->b[5] = buf[9];
    out->b[6] = buf[10];
    out->b[7] = buf[11];

    out->b[8] = 1;
    out->b[9] = 1;
    out->b[10] = 0;
    out->b[11] = 0;
    out->b[12] = 1;
    out->b[13] = 1;
    out->b[14] = 0;
    out->b[15] = 0;

    out->unk_10 = (u8) (func_020644cc(5) + 1);
    out->unk_11 = 0x63;

    out->unk_34 = 0;
    out->unk_38 = 0;

    func_0204101c(out);
    func_02040c90(out, 1);
}

void func_020411f4(void *argument0)
{
    func_020411fc((UnkStruct_020411fc *) ((void *) argument0));
}

void func_02041194(void *self)
{
    unsigned char local1[4], local2[4];

    func_0209df64((u8 *) local1);
    if (func_0209dcdc(local1, (unsigned char *) self + 8) >= 7) {
        ((unsigned char *) self)[8] = 1;
        ((unsigned char *) self)[9] = 1;
        ((unsigned char *) self)[10] = 0;
        ((unsigned char *) self)[11] = 0;
    }

    func_0209df64((u8 *) local2);
    if (func_0209dcdc(local2, (unsigned char *) self + 12) >= 7) {
        ((unsigned char *) self)[12] = 1;
        ((unsigned char *) self)[13] = 1;
        ((unsigned char *) self)[14] = 0;
        ((unsigned char *) self)[15] = 0;
    }

    func_02040c90((UnkStruct_020411fc *) self, 0);
    func_0203fe58(1);
    func_02041788();
}

int func_02041140(int unused, int *out, int param)
{
    unsigned char buf1[8];
    unsigned char buf2[88];
    int i;
    int result;
    int count = 0;

    func_0209e29c(param, 1);
    for (i = 0; i < 5; i++) {
        MI_CpuCopy8(param, buf1, 8);
        result = func_0203fbb0(buf2, 7, buf1);
        if (result <= 0) {
            *out = 1;
            count++;
        } else {
            *out = 0;
        }
        func_0209e29c(param, 1);
        out++;
    }
    return count;
}

int func_02041110(int a, int *array, int b)
{
    int i;
    int result;
    int *p = array;
    int count = (unsigned int) func_020644cc(b);
    i = 0;
    result = -1;
    while (i < 5) {
        if (*p == 1) {
            count--;
            if (count < 0) {
                result = i;
                break;
            }
        }
        p++;
        i++;
    }
    return result;
}

int func_020410ec(int arg0, const unsigned char *str, unsigned char ch)
{
    int result = 0;
    int i = 0;
    const unsigned char *p = str;
    while (i <= 5) {
        if (*p != 'c' && *p == ch) {
            result = 1;
            break;
        }
        p++;
        i++;
    }
    return result;
}
