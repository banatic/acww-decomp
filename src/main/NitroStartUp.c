/* NitroStartUp @ 0x020b1a74, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;

typedef enum { GX_VRAM_ARM7_128_C = 4, GX_VRAM_ARM7_128_D = 8, GX_VRAM_ARM7_256_CD = 0xc } GXVRamARM7;

extern void func_020012bc(void);
extern void OS_InitTick(void);
extern void func_02110794(void);
extern void GX_SetBankForLCDC(int);
extern void MIi_CpuClearFast(u32, u32, u32);
extern void func_02110aa0(void);
extern u32 OS_EnableInterrupts(void);
extern WVRResult WVR_StartUpAsync(GXVRamARM7, void (*)(void *, WVRResult), void *);
extern unsigned int OS_RestoreInterrupts(u32);
extern void FS_Init(int);
extern void func_020ea48c(void);
extern void func_020b1b68(void *argument, WVRResult result);

extern volatile u8 data_021f4b10;
extern volatile u16 data_0213e5a4;

extern void func_020b1b48(void);
extern void func_02098404(void);
extern void func_020b1b0c(void);
extern void func_0204f8bc(void);

void NitroStartUp(void)
{
    volatile u32 tmp;
    u32 dmaResult;
    u16 old_hw;

    func_020012bc();
    OS_InitTick();
    func_02110794();
    GX_SetBankForLCDC(8);

    tmp = 0;
    MIi_CpuClearFast(tmp, 0x06800000, 0x00020000);
    func_02110aa0();

    old_hw = *(volatile u16 *) 0x04000208;
    *(volatile u16 *) 0x04000208 = 1;
    dmaResult = OS_EnableInterrupts();

    data_021f4b10 = 0;
    WVR_StartUpAsync(8, func_020b1b68, 0);
    while (data_021f4b10 == 0)
        ;

    OS_RestoreInterrupts(dmaResult);

    (void) *(volatile u16 *) 0x04000208;
    *(volatile u16 *) 0x04000208 = old_hw;

    func_020b1b48();
    func_02098404();
    FS_Init(2);
    func_020b1b0c();
    func_0204f8bc();

    data_0213e5a4 = 1;
    func_020ea48c();
}
