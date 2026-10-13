/* func_020f4130 @ 0x020f4130, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern void NNS_SndPlayerCreateHeap(int, int, int);

void func_020f4130(void)
{
    int x = func_020eef70();
    int i;
    for (i = 0; i < 2; i++) {
        NNS_SndPlayerCreateHeap(6, x, 0x7a4c);
    }
}
