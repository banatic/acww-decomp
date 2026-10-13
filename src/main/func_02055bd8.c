/* func_02055bd8 @ 0x02055bd8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef u32 NNSGfdTexKey;

#define NNS_GFD_TEXKEY_ADDR_SHIFT 3
#define NNS_GFD_TEXKEY_SIZE_SHIFT 4
#define NNS_GFD_MASK_16BIT 0xFFFF

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
