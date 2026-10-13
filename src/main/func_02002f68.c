/* func_02002f68 @ 0x02002f68, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void G3X_Init(void);
extern void G3X_InitTable(void);
extern void G3X_InitMtxStack(void);
extern void G3i_PerspectiveW_(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
                              unsigned int);
extern void NNS_G3dInit(void);
extern void func_02002e54(void);
extern void G3X_SetClearColor(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

extern volatile unsigned int data_0213feb0;
extern volatile unsigned short data_0213feac;

void func_02002f68(void)
{
    G3X_Init();
    G3X_InitTable();
    G3X_InitMtxStack();

    *(volatile unsigned short *) 0x04000060 = *(volatile unsigned short *) 0x04000060 & 0xffffcffd;
    *(volatile unsigned short *) 0x04000060 = (*(volatile unsigned short *) 0x04000060 & 0xffffcfff) | 0x10;
    *(volatile unsigned short *) 0x04000060 = (*(volatile unsigned short *) 0x04000060 & 0xffffcfff) | 0x08;
    *(volatile unsigned short *) 0x04000060 = *(volatile unsigned short *) 0x04000060 & 0x0000cfdf;

    *(volatile unsigned int *) 0x04000580 = 0xbfff0000;

    G3i_PerspectiveW_(0x579, 0x0f09, 0x1555, 0x1000, 0x003e8000, 0x1000, 1, 0);

    *(volatile unsigned int *) 0x0400044c = 0;
    *(volatile unsigned int *) 0x04000540 = 3;

    NNS_G3dInit();
    func_02002e54();

    G3X_SetClearColor(0, 0, 0x7fff, 0x3f, 1);

    data_0213feac = 0;
    data_0213feb0 = 0x7fff;
}
