/* func_02064af4 @ 0x02064af4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064cd8(void *dst, const void *src);
extern int func_020649ac(void *dst, const void *src, int size);

int func_02064af4(const void *a, const void *b, int c)
{
    unsigned char buf[0x4c];
    func_02064cd8(buf, a);
    return func_020649ac(buf, b, c);
}
