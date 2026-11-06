/* sound_9: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eef70 @ 0x020eef70, 0x10 bytes, ARM
 * func_020eeea4 @ 0x020eeea4, 0xcc bytes, ARM
 * func_020eeea0 @ 0x020eeea0, 0x4 bytes, ARM
 * func_020eee5c @ 0x020eee5c, 0x44 bytes, ARM
 */

extern unsigned int data_021fd048;
extern void NNS_SndInit(void);
extern void OS_Terminate(void);
extern void *NNS_SndHeapCreate(void *heapMem, unsigned int heapSize);
extern void func_020eee08(void);
extern void NNS_SndArcInit(void *arc, const void *data, void *heap, int flags);
extern void NNS_SndArcInitOnMemory(void *arc, const void *data);
extern int NNS_SndArcPlayerSetup(void *heap);
extern void func_0210b7e0(void *player);
extern unsigned char data_021fd10c[];
extern unsigned char data_021fd07c[];
extern unsigned char data_021fd04c[];
extern int data_021fd050;
extern void NNS_SndCaptureStartOutputEffect(int, int, int);

unsigned int func_020eef70(void)
{
    return data_021fd048;
}

void func_020eeea4(void *heapMem, unsigned int heapSize, const void *arcData, const void *onMemData)
{
    NNS_SndInit();
    if ((*(void **) &data_021fd048) != 0) {
        OS_Terminate();
    }
    (*(void **) &data_021fd048) = NNS_SndHeapCreate(heapMem, heapSize);
    if ((*(void **) &data_021fd048) == 0) {
        OS_Terminate();
    }
    func_020eee08();
    if (arcData != 0) {
        NNS_SndArcInit(data_021fd10c, arcData, (*(void **) &data_021fd048), 0);
    } else {
        if (onMemData == 0) {
            OS_Terminate();
        }
        NNS_SndArcInitOnMemory(data_021fd07c, onMemData);
    }
    if (NNS_SndArcPlayerSetup((*(void **) &data_021fd048)) == 0) {
        OS_Terminate();
    }
    func_0210b7e0(data_021fd04c);
}

void func_020eeea0(void *memory, unsigned int size, unsigned int data1, unsigned int data2) {}

void func_020eee5c(int arg)
{
    if (data_021fd050 == 0) {
        OS_Terminate();
    }
    NNS_SndCaptureStartOutputEffect((data_021fd050 + 0x1f) & ~0x1f, 0x1000, arg);
}
