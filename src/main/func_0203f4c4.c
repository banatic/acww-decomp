/* func_0203f4c4 @ 0x0203f4c4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OSiHeapInfo[4];
extern int data_021c72d4;
extern char data_020dab94;

void func_0203f4c4(void)
{
    int value = 0;
    int i;
    for (i = 0; i < 4; i++) {
        OSiHeapInfo[i] = value;
    }
    data_021c72d4 = value;
    data_020dab94 = 6;
}
