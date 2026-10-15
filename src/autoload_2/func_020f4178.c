/* func_020f4178 @ 0x020f4178, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern int NNS_SndPlayerCreateHeap(int, int, int);

void func_020f4178(void)
{
    int r0;
    r0 = func_020eef70();
    NNS_SndPlayerCreateHeap(5, r0, 0x31ac);
}
