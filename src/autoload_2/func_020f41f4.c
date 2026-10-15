/* func_020f41f4 @ 0x020f41f4, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eef70(void);
extern int NNS_SndPlayerCreateHeap(int, int, int);

void func_020f41f4(void *receiver)
{
    NNS_SndPlayerCreateHeap(4, func_020eef70(), 0x206c);
}
