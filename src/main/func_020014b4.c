/* func_020014b4 @ 0x020014b4, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02053f20(void);
extern void GX_SetBankForBG(unsigned int);
extern void GX_SetBankForSubBG(unsigned int);
extern void func_02112d48(void *, unsigned int, unsigned int);
extern void func_02112ce0(void *, unsigned int, unsigned int);
extern void GX_LoadBGPltt(void *, unsigned int, unsigned int);
extern void GXS_LoadBGPltt(void *, unsigned int, unsigned int);
extern unsigned int G2_GetBG1ScrPtr(void);
extern unsigned int G2S_GetBG1ScrPtr(void);
extern void func_020015c8(void);
extern void GX_DispOn(void);

#define REG16(addr) (*(volatile unsigned short *) (addr))
#define REG32(addr) (*(volatile unsigned int *) (addr))

extern unsigned char data_020df71c[];
extern unsigned char data_020e171c[];
extern unsigned int data_0213fdd0;
extern unsigned int data_0213fddc;

void func_020014b4(void)
{
    func_02053f20();
    REG16(0x04000304) |= 0x0001;
    REG16(0x04000050) = 0;
    REG16(0x04001050) = 0;
    GX_SetBankForBG(0x40);
    GX_SetBankForSubBG(0x80);
    REG32(0x04000000) = (REG32(0x04000000) & 0xffffe0ff) | 0x00000200;
    REG32(0x04001000) = (REG32(0x04001000) & 0xffffe0ff) | 0x00000200;
    REG16(0x0400000a) = (REG16(0x0400000a) & 0x43) | 0x0400;
    REG16(0x0400100a) = (REG16(0x0400100a) & 0x43) | 0x0400;
    func_02112d48((void *) data_020df71c, 0, 0x1000);
    func_02112ce0((void *) data_020df71c, 0, 0x1000);
    GX_LoadBGPltt((void *) data_020e171c, 0x1a0, 0x60);
    GXS_LoadBGPltt((void *) data_020e171c, 0x1a0, 0x60);
    REG16(0x05000000) = 0x7c00;
    REG16(0x05000018) = 0x7c00;
    REG16(0x05000400) = 0x7c00;
    REG16(0x05000418) = 0x7c00;
    data_0213fdd0 = G2_GetBG1ScrPtr();
    data_0213fddc = G2S_GetBG1ScrPtr();
    func_020015c8();
    GX_DispOn();
    REG32(0x04001000) |= 0x00010000;
}
