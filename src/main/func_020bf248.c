/* func_020bf248 @ 0x020bf248, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bf2a0(int, void *);
extern void func_020be5a0(void *, int, int, void *);
extern int data_021fbb14;

void func_020bf248(int a, int b)
{
    char buffer[16];
    func_020bf2a0(a, buffer);
    func_020be5a0(&data_021fbb14, 0, b, buffer);
}
