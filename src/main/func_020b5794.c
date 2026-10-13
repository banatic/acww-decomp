/* func_020b5794 @ 0x020b5794, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020540c0(void);
extern void func_020b98dc(void);
extern void func_020b9990(void);
extern void func_02053fdc(void);
extern void GX_SetBankForBG(int);
extern void GX_SetBankForSubBG(int);
extern void func_02001bf0(int);
extern void func_02001bdc(int);
extern void func_020028bc(int, int, int, int);
extern void func_02002c6c(const void *, void *, int, int, int, int);
extern void func_02002d14(const void *, void *, int, int, int, int);
extern void func_02002ca4(const void *, void *, int);
extern void func_02002708(int);

extern void *data_021fbe94;
extern const u8 data_020e5368[], data_020e537c[], data_020e5390[], data_020e53a4[], data_020e53b8[], data_020e53cc[];

void func_020b5794(void)
{
    volatile u32 *p;
    void *v;

    func_020540c0();
    func_020b98dc();
    func_020b9990();
    func_02053fdc();
    GX_SetBankForBG(0x20);
    GX_SetBankForSubBG(0x80);
    p = (volatile u32 *) 0x04000000;
    *p = *p & 0xffcfffef;
    p = (volatile u32 *) 0x04001000;
    *p = *p & 0xffcfffef;
    func_02001bf0(0);
    func_02001bdc(0);
    p = (volatile u32 *) 0x04000000;
    *p = *p & 0xc7ffffff;
    func_020028bc(6, 0, 0, 0);
    func_020028bc(2, 0, 0, 0);
    v = data_021fbe94;
    func_02002c6c(data_020e5368, v, 6, 0, 0, 0x2ff);
    func_02002d14(data_020e537c, v, 6, 0, 0, 0);
    func_02002ca4(data_020e5390, v, 6);
    func_02002c6c(data_020e53a4, v, 2, 0, 0, 0x13f);
    func_02002d14(data_020e53b8, v, 2, 0, 0, 0);
    func_02002ca4(data_020e53cc, v, 2);
    func_02002708(6);
    func_02002708(2);
}
