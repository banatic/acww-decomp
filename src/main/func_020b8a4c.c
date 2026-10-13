/* func_020b8a4c @ 0x020b8a4c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208aa60(void *dest, int fill, int mask);

void func_020b8a4c(void *arg)
{
    func_0208aa60((char *) arg + 8, 0, ~0x2f);
}
