/* func_02002a88 @ 0x02002a88, 0xb6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void DC_FlushRange(void *startAddr, u32 nBytes);
extern void func_02112b40(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112ba8(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112c10(const void *pSrc, u32 offset, u32 szByte);
extern void GX_LoadBG2Char(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112ce0(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112d48(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112db0(const void *pSrc, u32 offset, u32 szByte);
extern void GX_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);
extern void GXS_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);

int func_02002a88(u32 base, int type, u32 col0, u32 col1, u32 col2)
{
    u32 addr = base + ((col1 - col0) << 5);
    u32 size = ((col2 - col1) + 1) << 5;
    u32 offset = col1 << 5;

    DC_FlushRange((void *) addr, size);

    switch (type) {
        case 0:
            func_02112d48((const void *) addr, offset, size);
            break;
        case 1:
            GX_LoadBG2Char((const void *) addr, offset, size);
            break;
        case 2:
            func_02112ba8((const void *) addr, offset, size);
            break;
        case 3:
            func_02112db0((const void *) addr, offset, size);
            break;
        case 4:
            func_02112ce0((const void *) addr, offset, size);
            break;
        case 5:
            func_02112c10((const void *) addr, offset, size);
            break;
        case 6:
            func_02112b40((const void *) addr, offset, size);
            break;
        case 7:
            GX_LoadOBJ((const void *) addr, offset, size);
            break;
        case 8:
            GXS_LoadOBJ((const void *) addr, offset, size);
            break;
        default:
            break;
    }
    return 1;
}
