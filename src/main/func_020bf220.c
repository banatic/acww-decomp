/* func_020bf220 @ 0x020bf220, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bf290(int a, int *buf);
extern void func_020be5d0(int *ptr, int b, int c, int *buf);
extern int data_021fbb14;

void func_020bf220(int a, int b, int c)
{
    int buffer[3];
    func_020bf290(a, buffer);
    func_020be5d0(&data_021fbb14, b, c, buffer);
}
