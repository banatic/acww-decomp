/* func_020f40e8 @ 0x020f40e8, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern int NNS_SndPlayerCreateHeap(int, int, int);

void func_020f40e8(void)
{
    int result = func_020eef70();
    int i;
    for (i = 0; i < 4; i++) {
        NNS_SndPlayerCreateHeap(0x11, result, 0x356c);
    }
}
