/* func_0203f454 @ 0x0203f454, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OSiHeapInfo[];
extern int data_021c72d4;

int func_0203f454(int a, int b)
{
    int i;
    if (OSiHeapInfo[a] != 0) {
        return 0;
    }
    if (data_021c72d4 == b) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (b == OSiHeapInfo[i]) {
            return 0;
        }
    }
    return 1;
}
