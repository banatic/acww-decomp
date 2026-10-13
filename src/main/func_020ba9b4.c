/* func_020ba9b4 @ 0x020ba9b4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f6cd8;
extern void func_020bc1bc(int *);
extern int data_021f8b48;

int func_020ba9b4(void)
{
    if (data_021f6cd8 != 0) {
        func_020bc1bc(&data_021f8b48);
    }
    return 1;
}
