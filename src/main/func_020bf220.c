/* func_020bf220 @ 0x020bf220, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bf290(int a, int *buf, int c, int d);
extern int func_020be5d0(int *ptr, int b, int c, int *buf);
extern int data_021fbb14;

void func_020bf220(int a, int b, int c, int d)
{
    int buffer[3];
    func_020bf290(a, buffer, c, d);
    func_020be5d0(&data_021fbb14, b, c, buffer);
}
