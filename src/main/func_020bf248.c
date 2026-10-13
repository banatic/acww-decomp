/* func_020bf248 @ 0x020bf248, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bf2a0(int, void *, int, int);
extern int func_020be5a0(void *, int, int, void *);
extern int data_021fbb14;

int func_020bf248(int a, int b, int c, int d)
{
    char buffer[16];
    func_020bf2a0(a, buffer, c, d);
    return func_020be5a0(&data_021fbb14, 0, b, buffer);
}
