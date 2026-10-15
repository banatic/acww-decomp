/* func_020f40ac @ 0x020f40ac, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern int NNS_SndPlayerCreateHeap(int, int, int);

void func_020f40ac(void *receiver)
{
    int x = func_020eef70();
    NNS_SndPlayerCreateHeap(18, x, 0x5ecc);
    NNS_SndPlayerCreateHeap(19, x, 0x46bc);
}
