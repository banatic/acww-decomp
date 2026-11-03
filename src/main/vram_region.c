/* vram_region: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02055c74 @ 0x02055c74, 0xc bytes, Thumb
 * func_02055c68 @ 0x02055c68, 0xc bytes, Thumb
 * func_02055c54 @ 0x02055c54, 0x14 bytes, Thumb
 * func_02055c40 @ 0x02055c40, 0x14 bytes, Thumb
 * func_02055c2c @ 0x02055c2c, 0x14 bytes, Thumb
 * func_02055c18 @ 0x02055c18, 0x14 bytes, Thumb
 * func_02055bd8 @ 0x02055bd8, 0x40 bytes, Thumb
 * func_02055bac @ 0x02055bac, 0x2c bytes, Thumb
 * func_02055b50 @ 0x02055b50, 0x5c bytes, Thumb
 * func_02055b40 @ 0x02055b40, 0xe bytes, Thumb
 * func_02055b34 @ 0x02055b34, 0xc bytes, Thumb
 */

#include "types.h"

#define NNS_GFD_TEXKEY_ADDR_SHIFT 3
#define NNS_GFD_TEXKEY_SIZE_SHIFT 4
#define NNS_GFD_MASK_16BIT 0xFFFF

struct UnkStruct_02055c68 {
    int unk_00;
    int unk_04;
    void *unk_08;
};

struct UnkStruct_02055c2c {
    int unk_00;
    int unk_04;
};

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
} UnkStruct_02055c18;

typedef u32 NNSGfdTexKey;

typedef struct {
    char pad_00[0xc];
    unsigned int c;
} UnkStruct_02055bac;

typedef struct {
    int a;
    int b;
    int c;
    int d;
    char e;
    char unk_11;
} UnkStruct_02055b34;

extern int NNS_G3dTexGetRequiredSize(void *);
extern int NNS_G3dTex4x4GetRequiredSize(void *);
extern int NNS_G3dPlttGetRequiredSize(void *);
extern void NNS_G3dTexSetTexKey(void *, int, int);
extern void func_02105178(void *, int);

unsigned int func_02055c54(unsigned int unused, unsigned int a, unsigned int b);
NNSGfdTexKey func_02055bd8(void *self, u32 szByte, NNSGfdTexKey prev, NNSGfdTexKey key);

int func_02055c74(int *a, int b)
{
    return (int) func_02055c54((unsigned int) a, b, a[1]);
}

int func_02055c68(void *obj, int arg)
{
    return (int) func_02055c54((unsigned int) obj, arg, (unsigned int) (((struct UnkStruct_02055c68 *) obj)->unk_08));
}

unsigned int func_02055c54(unsigned int unused, unsigned int a, unsigned int b)
{
    return (b & 0x8000ffff) | ((a >> 4) << 16);
}

unsigned int func_02055c40(void *arg0, unsigned int arg1)
{
    unsigned int r0;
    unsigned int r1;

    r0 = *(unsigned int *) ((char *) arg0 + 0xc);
    r0 &= 0xffff;
    r1 = arg1 >> 3;
    r1 <<= 0x10;
    r0 |= r1;
    return r0;
}

int func_02055c2c(struct UnkStruct_02055c2c *a, int b, int c)
{
    return (int) func_02055bd8((void *) a, c, a->unk_04, b);
}

int func_02055c18(UnkStruct_02055c18 *a, int b, int c)
{
    return (int) func_02055bd8((void *) a, c, a->unk_08, b);
}

static inline u32 NNS_GfdGetTexKeyAddr(NNSGfdTexKey memKey)
{
    return (u32) ((memKey & NNS_GFD_MASK_16BIT) << NNS_GFD_TEXKEY_ADDR_SHIFT);
}

static inline u32 NNS_GfdGetTexKeySize(NNSGfdTexKey memKey)
{
    return (u32) (((memKey & 0x7FFF0000) >> 16) << NNS_GFD_TEXKEY_SIZE_SHIFT);
}

static inline BOOL NNS_GfdGetTexKey4x4Flag(NNSGfdTexKey memKey)
{
    return (BOOL) ((memKey & 0x80000000) >> 31);
}

static inline NNSGfdTexKey NNS_GfdMakeTexKey(u32 addr, u32 szByte, BOOL b4x4Comp)
{
    return ((szByte >> NNS_GFD_TEXKEY_SIZE_SHIFT) << 16) | (NNS_GFD_MASK_16BIT & (addr >> NNS_GFD_TEXKEY_ADDR_SHIFT)) |
           (b4x4Comp << 31);
}

// The key that follows `key` in the same VRAM run: its address is where `key` ends.
NNSGfdTexKey func_02055bd8(void *self, u32 szByte, NNSGfdTexKey prev, NNSGfdTexKey key)
{
    u32 addr = NNS_GfdGetTexKeyAddr(prev);
    addr += NNS_GfdGetTexKeySize(key);
    return NNS_GfdMakeTexKey(addr, szByte, NNS_GfdGetTexKey4x4Flag(key));
}

unsigned int func_02055bac(UnkStruct_02055bac *s, unsigned int p1, unsigned int p2)
{
    unsigned int t = (s->c & 0xffff) << 3;
    t += ((p1 & 0xffff0000) >> 16) << 3;
    return ((p2 >> 3) << 16) | ((t >> 3) & 0xffff);
}

void func_02055b50(void *arg0, void *arg1)
{
    int v1, v2, v3, v4, v5, v6;
    v1 = NNS_G3dTexGetRequiredSize(arg1);
    v2 = NNS_G3dTex4x4GetRequiredSize(arg1);
    v3 = NNS_G3dPlttGetRequiredSize(arg1);
    v4 = func_02055c74((int *) arg0, v1);
    v5 = func_02055c68(arg0, v2);
    v6 = (int) func_02055c40(arg0, v3);
    NNS_G3dTexSetTexKey(arg1, v4, v5);
    func_02105178(arg1, v6);
    ((char *) arg0)[0x10] = 1;
}

void func_02055b40(void *r0)
{
    unsigned int *p32 = (unsigned int *) r0;
    unsigned char *p8 = (unsigned char *) r0;
    p32[1] = 0;
    p32[2] = 0;
    p32[3] = 0;
    p8[0x10] = 0;
    p8[0x11] = 0;
}

void func_02055b34(UnkStruct_02055b34 *s, int v1, int v2, int v3)
{
    s->b = v1;
    s->c = v2;
    s->d = v3;
    s->unk_11 = 1;
}
