/* func_02076518 @ 0x02076518, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *data_020ccf94;
extern void func_020736bc(int *ptr, unsigned char *out, int flag);
extern void func_020a6f74(int value, unsigned char byte);

void func_02076518(void)
{
    unsigned char flag;
    int *ptr = data_020ccf94;
    func_020736bc(ptr, &flag, 1);
    func_020a6f74(ptr[25], flag);
}
