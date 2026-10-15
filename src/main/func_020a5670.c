/* func_020a5670 @ 0x020a5670, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02053f20(void);
extern void G3X_Init(void);
extern void GX_SetBankForBG(int arg);
extern void GX_SetBankForOBJ(int arg);
extern void GX_SetBankForBGExtPltt(int arg);
extern void GX_SetBankForTex(int arg);
extern void GX_SetBankForTexPltt(int arg);
extern void func_02002f68(void);

void func_020a5670(void)
{
    func_02053f20();
    G3X_Init();
    GX_SetBankForBG(0x20);
    GX_SetBankForOBJ(0x1);
    GX_SetBankForBGExtPltt(0x40);
    GX_SetBankForTex(0x6);
    GX_SetBankForTexPltt(0x10);
    *(volatile unsigned int *) 0x040004c8 = 0x20000000;
    *(volatile unsigned int *) 0x040004cc = 0x00007fff;
    *(volatile unsigned int *) 0x040004c0 = 0x00007fff;
    *(volatile unsigned int *) 0x040004c4 = 0x0;
    func_02002f68();
}
