/* startup: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b1c78 @ 0x020b1c78, 0x38 bytes, Thumb
 * func_020b1c74 @ 0x020b1c74, 0x2 bytes, Thumb
 * func_020b1b84 @ 0x020b1b84, 0xf0 bytes, Thumb
 * func_020b1b68 @ 0x020b1b68, 0x1c bytes, Thumb
 * func_020b1b48 @ 0x020b1b48, 0x20 bytes, Thumb
 * func_020b1b0c @ 0x020b1b0c, 0x3c bytes, Thumb
 */

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

extern void OS_SetIrqFunction(int, void (*)(void));
extern void func_01ffcc60(void);
extern int data_021cfb90[];
extern int data_021cfb98[];
extern unsigned char data_021cfb68;
extern void func_01ffcb28(void);
extern void func_020eace4(void);
extern void func_0205c0d4(void);
extern void func_01ffcc30(void);
extern int OS_EnableIrqMask(int);
extern int OS_EnableInterrupts(void);
extern int GX_VBlankIntr(int);
extern int GX_HBlankIntr(int);
extern void func_02050b78(void);
extern void func_02037f74(void);
extern int func_02077b70(void *, int);
extern void func_02077b9c(void *);
extern char data_021d11c4[];
extern char data_020e3134[];
extern void func_020b93e8(void);
extern void func_020edb98(void);
extern void func_020e9918(int size, void *heap);
extern void func_020540e4(void);
extern void func_02004b70(void);
extern void func_020e906c(void);
extern void func_0209dfc0(void);
extern void func_02046620(void);
extern int func_02038998(void);
extern void func_0209a200(void);
extern void func_02061530(void);
extern void func_0206e6c0(void);
extern void func_0209dae8(void);
extern char SDK_OVERLAY_ov069_ID;
extern char SDK_OVERLAY_ov068_ID;
extern void *data_021fd044;
extern void OS_Terminate(void);
extern unsigned char data_021f4b10;
extern void OS_SetProtectionRegion2(unsigned int);
extern void OS_SetArenaHi(int, unsigned int);
extern unsigned char SDK_OVERLAY_ov000_ID;
extern void func_0204fa5c(unsigned int *buf, unsigned int val);
extern void MIi_CpuClearFast(unsigned int val, unsigned int *ptr, unsigned int size);
extern void DC_FlushRange(unsigned int *ptr, unsigned int size);

void func_020b1c78(void)
{
    int *p0;
    int *p1;
    int i;

    p0 = data_021cfb90;
    p1 = data_021cfb98;

    p0[1] = 0;
    p0[0] = 0;
    p1[1] = 0;
    p1[0] = 0;

    OS_SetIrqFunction(1, func_01ffcc60);

    data_021cfb68 = 1;
}

void func_020b1c74(void) {}

void func_020b1b84(void)
{
    ((((func_020b1c74(), func_01ffcb28()), func_020eace4()), func_0205c0d4()), func_020b1c78());

    OS_SetIrqFunction(2, func_01ffcc30);
    OS_EnableIrqMask(3);

    (void) *(volatile unsigned short *) 0x04000208;
    *(volatile unsigned short *) 0x04000208 = 1;
    OS_EnableInterrupts();

    GX_VBlankIntr(1);
    ((GX_HBlankIntr(1), func_02050b78()), func_02037f74());

    func_02077b70(data_021d11c4, (int) &SDK_OVERLAY_ov069_ID);
    func_02077b9c(data_021d11c4);

    (func_020b93e8(), func_020edb98());

    (((func_020e9918(0x13fc8, 0), func_020540e4()), func_02004b70()), func_020e906c());

    ((func_0209dfc0(), func_02046620()), func_02038998());

    data_021fd044 = data_020e3134;

    func_0209a200();
    func_02061530();

    *(volatile unsigned int *) 0x040004c8 = 0x296a5800;
    *(volatile unsigned int *) 0x040004cc = 0x7fff;
    *(volatile unsigned int *) 0x040004c0 = 0x7fff;
    *(volatile unsigned int *) 0x040004c4 = 0;

    func_0206e6c0();
    func_0209dae8();

    func_02077b70(data_021d11c4, (int) &SDK_OVERLAY_ov068_ID);
}

void func_020b1b68(void *argument, WVRResult result)
{
    if (result != WVR_RESULT_SUCCESS) {
        OS_Terminate();
    }
    data_021f4b10 = 1;
}

void func_020b1b48(void)
{
    OS_SetProtectionRegion2(0x023ff017);
    OS_SetArenaHi(0, 0x023ff000);
}

void func_020b1b0c(void)
{
    volatile struct {
        unsigned int x;
        unsigned int buf[12];
    } t;
    unsigned int *p;
    unsigned int size;

    func_0204fa5c((unsigned int *) t.buf, (unsigned int) &SDK_OVERLAY_ov000_ID);
    p = (unsigned int *) t.buf[1];
    t.x = 0xe7fee7fe;
    size = 0x022a3300 - (unsigned int) p;
    MIi_CpuClearFast(t.x, p, size);
    DC_FlushRange(p, size);
}
