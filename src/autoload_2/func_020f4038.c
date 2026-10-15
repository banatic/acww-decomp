/* func_020f4038 @ 0x020f4038, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern int NNS_SndPlayerCreateHeap(int, int, int);

int func_020f4038(void)
{
    int x;
    int i;
    int result;
    x = func_020eef70();
    for (i = 0; i < 2; i++) {
        result = NNS_SndPlayerCreateHeap(0xc, x, 0x8cc);
    }
    return result;
}
