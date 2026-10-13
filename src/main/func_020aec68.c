/* func_020aec68 @ 0x020aec68, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef74(void);
extern void func_020b0164(int *, int, int, int, int, int, int);

void func_020aec68(int *ptr, int other)
{
    func_020b0164(ptr + 1, other, 3, 0, func_020aef74(), 0x25, 0);
}
