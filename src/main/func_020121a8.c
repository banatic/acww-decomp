/* func_020121a8 @ 0x020121a8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082c98(int a);
extern void func_0205eac4(unsigned char *key, int value);
extern unsigned char data_021ca16c[];

void func_020121a8(int param0, int param1)
{
    int result;

    result = func_02082c98(param0 + 4);
    if (result) {
        func_0205eac4((unsigned char *) result, param1);
    }
}
