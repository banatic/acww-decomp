/* func_020f41a4 @ 0x020f41a4, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eef70(int a);
extern void NNS_SndPlayerCreateHeap(int a, int b, int c);

void func_020f41a4(int a, int count)
{
    int value = func_020eef70(a);
    int i = 0;
    if (count <= 0) {
        return;
    }
    do {
        NNS_SndPlayerCreateHeap(0xb, value, 0x650c);
        i++;
    } while (i < count);
}
