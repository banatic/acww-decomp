/* event_calendar_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203feec @ 0x0203feec, 0xac bytes, Thumb
 * func_0203fec4 @ 0x0203fec4, 0x26 bytes, Thumb
 * func_0203fea0 @ 0x0203fea0, 0x24 bytes, Thumb
 * func_0203fe58 @ 0x0203fe58, 0x48 bytes, Thumb
 * func_0203fe1c @ 0x0203fe1c, 0x3c bytes, Thumb
 * func_0203fdc4 @ 0x0203fdc4, 0x58 bytes, Thumb
 */

#include "types.h"

typedef union {
    u32 w;
    struct {
        u8 a, b, c, d;
    } s;
} UnkStruct_0203feec;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u32 unk_08;
} Dst;

typedef struct {
    u8 pad_00[2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
} Src;

typedef struct {
    u8 pad_00[0x1c];
} UnkStruct_0203feec_2;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u32 unk_08;
} UnkStruct_0203feec_3;

typedef struct {
    unsigned char zero;
    unsigned char a;
    unsigned char b;
} UnkStruct_0203fe1c;

typedef union {
    struct {
        unsigned int word0;
        unsigned int word1;
        unsigned int word2;
    } words;
    struct {
        unsigned char pad0[3];
        unsigned char a;
        unsigned char b;
        unsigned char c;
        unsigned char pad1[6];
    } bytes;
} LocalUnion;

extern UnkStruct_0203feec_2 data_020dac08[];
extern int func_0209de88(int a, int b, int c);
extern void func_02040164(void *a, int n);
extern int func_0203ff98(Dst *d, UnkStruct_0203feec_2 *e, int t, UnkStruct_0203feec p);
extern int func_02040034(UnkStruct_0203feec_2 *e, UnkStruct_0203feec p, Dst *d, void *a, int n, void *c, void *dd);
extern void func_02040010(Dst *d, UnkStruct_0203feec p);
extern void MI_CpuCopy8(void *src, void *dst, unsigned int len);
extern void func_0209e474(void *p);
extern unsigned char data_021c74d4[];
extern unsigned char data_021c74d0[];
extern unsigned char *func_0203fda0(int, unsigned int *);
extern int func_0209e380(void *, void *);

int func_0203feec(UnkStruct_0203feec_3 *arr, Src *src, void *c, void *dd)
{
    UnkStruct_0203feec pp;
    Dst d;
    UnkStruct_0203feec_2 *e;
    UnkStruct_0203feec_3 *o;
    int n;
    int i;
    int t;
    int d4;
    int d3;

    n = 0;
    t = src->unk_05;
    d4 = src->unk_04;
    pp.s.d = (u8) d4;
    d3 = src->unk_03;
    pp.s.c = (u8) d3;
    pp.s.b = src->unk_02;
    pp.s.a = func_0209de88(t, d4, d3);
    func_02040164(arr, 7);
    e = data_020dac08;
    for (i = 0; i < 0x63; e++, i++) {
        if (func_0203ff98(&d, e, t, pp) == 0) {
            continue;
        }
        if (func_02040034(e, pp, &d, arr, n, c, dd) != 0) {
            continue;
        }
        func_02040010(&d, pp);
        o = &arr[n];
        arr[n].unk_00 = d.unk_00;
        o->unk_02 = d.unk_02;
        o->unk_04 = d.unk_04;
        o->unk_08 = d.unk_08;
        n++;
        if (n == 7) {
            break;
        }
    }
    return n;
}

int func_0203fec4(void *a, void *b, void *c)
{
    unsigned char buf[8];
    MI_CpuCopy8(b, (void *) buf, 8);
    return func_0203feec((UnkStruct_0203feec_3 *) a, (Src *) buf, 0, c);
}

int func_0203fea0(int param1, void *param2)
{
    char buf[8];
    MI_CpuCopy8(param2, buf, 8);
    return func_0203feec((UnkStruct_0203feec_3 *) param1, (Src *) buf, (void *) 1, 0);
}

void func_0203fe58(int param)
{
    unsigned int local0[2];
    unsigned char local1[8];

    local0[0] = 0;
    local0[1] = 0;

    func_0209e474(local0);
    MI_CpuCopy8(local0, local1, 8);
    func_0203fec4(data_021c74d4, local1, (void *) param);

    data_021c74d0[2] = ((unsigned char *) local0)[5];
    data_021c74d0[1] = ((unsigned char *) local0)[4];
    data_021c74d0[0] = ((unsigned char *) local0)[3];
}

void func_0203fe1c(int arg)
{
    LocalUnion local;
    int ok;
    local.words.word0 = 0;
    local.words.word1 = 0;
    func_0209e474(&local);
    ok = local.bytes.c == (*(UnkStruct_0203fe1c *) data_021c74d0).b && local.bytes.b == (*(UnkStruct_0203fe1c *) data_021c74d0).a && local.bytes.a == (*(UnkStruct_0203fe1c *) data_021c74d0).zero;
    if (ok) {
        return;
    }
    func_0203fe58(0);
}

int func_0203fdc4(int arg)
{
    unsigned int local[4];
    unsigned char *p;
    unsigned char *q;
    int result = -1;

    p = func_0203fda0(arg, ((unsigned int *) data_021c74d4));
    if (p != 0) {
        local[0] = 0;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        func_0209e474(local);

        ((unsigned char *) local)[2] = 0;
        ((unsigned char *) local)[1] = 0;
        ((unsigned char *) local)[0] = 0;

        q = p + 4;
        local[2] = 0;
        local[3] = 0;

        ((unsigned char *) local)[13] = ((unsigned char *) local)[5];
        ((unsigned char *) local)[12] = q[3];
        ((unsigned char *) local)[11] = q[2];

        result = func_0209e380(&local[2], local);
    }
    return result;
}
