/* func_02053f20 @ 0x02053f20, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned int GXi_DmaId;
extern void func_02053fdc(void);
extern void MI_DmaFill32(unsigned int, void *, int, int);

void func_02053f20(void)
{
    unsigned int base = 0x04000000;

    *(volatile unsigned short *) (base + 0x304) |= 0x820e;
    func_02053fdc();
    *(volatile unsigned int *) (base + 0) &= 0x000f000f;
    MI_DmaFill32(GXi_DmaId, (void *) (base + 0x8), 0, 0x48);
    MI_DmaFill32(GXi_DmaId, (void *) (base + 0x60), 0, 8);
    *(volatile unsigned short *) (base + 0x6c) = 0;
    *(volatile unsigned int *) (base + 0x1000) &= 0x00010000;
    MI_DmaFill32(GXi_DmaId, (void *) (base + 0x1008), 0, 0x48);
    *(volatile unsigned short *) (base + 0x106c) = 0;
    *(volatile unsigned short *) (base + 0x20) = 0x100;
    *(volatile unsigned short *) (base + 0x26) = 0x100;
    *(volatile unsigned short *) (base + 0x30) = 0x100;
    *(volatile unsigned short *) (base + 0x36) = 0x100;
    *(volatile unsigned short *) (base + 0x1020) = 0x100;
    *(volatile unsigned short *) (base + 0x1026) = 0x100;
    *(volatile unsigned short *) (base + 0x1030) = 0x100;
    *(volatile unsigned short *) (base + 0x1036) = 0x100;
}
