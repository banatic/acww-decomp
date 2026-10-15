/* func_020f4080 @ 0x020f4080, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern int NNS_SndPlayerCreateHeap(int, int, int);

void func_020f4080(void *receiver)
{
    int x;
    x = func_020eef70();
    NNS_SndPlayerCreateHeap(0xd, x, 0x1f4c);
}
