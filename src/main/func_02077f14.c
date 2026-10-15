/* func_02077f14 @ 0x02077f14, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *);
extern void *func_02077f3c(int, int, unsigned char, unsigned char, unsigned char);

void *func_02077f14(int a, int b)
{
    unsigned char buffer[3];
    func_0209df64(buffer);
    return func_02077f3c(a, b, buffer[2], buffer[1], buffer[0]);
}
