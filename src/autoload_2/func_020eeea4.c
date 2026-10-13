/* func_020eeea4 @ 0x020eeea4, 0xcc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndInit(void);
extern void OS_Terminate(void);
extern void *NNS_SndHeapCreate(void *heapMem, unsigned int heapSize);
extern void func_020eee08(void);
extern void NNS_SndArcInit(void *arc, const void *data, void *heap, int flags);
extern void NNS_SndArcInitOnMemory(void *arc, const void *data);
extern int NNS_SndArcPlayerSetup(void *heap);
extern void func_0210b7e0(void *player);

extern void *data_021fd048;
extern unsigned char data_021fd10c[];
extern unsigned char data_021fd07c[];
extern unsigned char data_021fd04c[];

void func_020eeea4(void *heapMem, unsigned int heapSize, const void *arcData, const void *onMemData)
{
    NNS_SndInit();
    if (data_021fd048 != 0) {
        OS_Terminate();
    }
    data_021fd048 = NNS_SndHeapCreate(heapMem, heapSize);
    if (data_021fd048 == 0) {
        OS_Terminate();
    }
    func_020eee08();
    if (arcData != 0) {
        NNS_SndArcInit(data_021fd10c, arcData, data_021fd048, 0);
    } else {
        if (onMemData == 0) {
            OS_Terminate();
        }
        NNS_SndArcInitOnMemory(data_021fd07c, onMemData);
    }
    if (NNS_SndArcPlayerSetup(data_021fd048) == 0) {
        OS_Terminate();
    }
    func_0210b7e0(data_021fd04c);
}
