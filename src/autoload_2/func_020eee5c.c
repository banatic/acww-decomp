/* func_020eee5c @ 0x020eee5c, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fd050;
extern void OS_Terminate(void);
extern void NNS_SndCaptureStartOutputEffect(int, int, int);

void func_020eee5c(int arg)
{
    if (data_021fd050 == 0) {
        OS_Terminate();
    }
    NNS_SndCaptureStartOutputEffect((data_021fd050 + 0x1f) & ~0x1f, 0x1000, arg);
}
