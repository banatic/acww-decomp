/* NitroStartUp @ 0x020b1a74, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020012bc(void);
extern void OS_InitTick(void);
extern void func_02110794(void);
extern void GX_SetBankForLCDC(int);
extern void MIi_CpuClearFast(u32, u32, u32);
extern void func_02110aa0(void);
extern u32 OS_EnableInterrupts(int);
extern void WVR_StartUpAsync(int, void (*)(void), int);
extern void OS_RestoreInterrupts(u32);
extern void FS_Init(int);
extern void func_020ea48c(void);
extern void func_020b1b68(void);

extern volatile u8 data_021f4b10;
extern volatile u16 data_0213e5a4;

static void func_020b1b48(void) {}
static void func_02098404(void) {}
static void func_020b1b0c(void) {}
static void func_0204f8bc(void) {}

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
    dmaResult = OS_EnableInterrupts(1);

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
