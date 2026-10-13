/* func_020b68f8 @ 0x020b68f8, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020540c0(void);
extern void func_020b98dc(void);
extern void func_020b9990(void);
extern void func_02053fdc(void);
extern void func_02001bf0(int);
extern void func_02001bdc(int);
extern void func_020b947c(void);
extern void func_02001b44(int);
extern void func_02001b0c(int);
extern void func_02056318(void);
extern void func_02038a20(void);
extern void GX_SetBankForTex(int);
extern void GX_SetBankForTexPltt(int);
extern void GX_SetBankForBG(int);
extern void GX_SetBankForOBJ(int);
extern void GX_SetBankForSubBG(int);
extern void GX_SetBankForSubOBJ(int);
void func_020b68f8(void)
{
    func_020540c0();
    func_020b98dc();
    func_020b9990();
    func_02053fdc();
    GX_SetBankForTex(7);
    GX_SetBankForTexPltt(0x10);
    GX_SetBankForBG(0x20);
    GX_SetBankForOBJ(0x40);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    *((volatile unsigned int *) 0x04000000) = (*((volatile unsigned int *) 0x04000000)) & 0xffcfffef;
    *((volatile unsigned int *) 0x04001000) = (*((volatile unsigned int *) 0x04001000)) & 0xffcfffef;
    func_02001bf0(0);
    func_02001bdc(1);
    *((volatile unsigned int *) 0x04000000) = (*((volatile unsigned int *) 0x04000000)) & 0xc7ffffff;
    func_020b947c();
    func_02001b44(0x11);
    func_02001b0c(0x10);
    func_02056318();
    func_02038a20();
}
