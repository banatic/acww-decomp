/* func_020a1738 @ 0x020a1738, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050a10(int a, int b, int c, int d);
extern char data_021dc7a8[];
extern char data_021f3ba0[];
extern int data_020d1c20[];

extern unsigned char data_021c8188[];

int func_020a1738(int idx, int param1)
{
    return func_02050a10((unsigned int) data_021c8188, param1, 4, (data_021f3ba0 - data_021dc7a8) + data_020d1c20[idx]);
}
