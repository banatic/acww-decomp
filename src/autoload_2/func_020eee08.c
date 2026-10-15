/* func_020eee08 @ 0x020eee08, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void *func_020eef70(void);
extern void *NNS_SndHeapAlloc(void *heap, unsigned int size, void (*dispose)(void *, unsigned int, unsigned int, unsigned int),
                              unsigned int data1, unsigned int data2);
extern void func_020eeea0(void *memory, unsigned int size, unsigned int data1, unsigned int data2);
extern void OS_Terminate(void);
extern int data_021fd050;

void func_020eee08(void)
{
    void *result = NNS_SndHeapAlloc(func_020eef70(), 0x1020, func_020eeea0, 0, 0);
    data_021fd050 = (int) result;
    if (result != 0) {
        return;
    }
    OS_Terminate();
}
