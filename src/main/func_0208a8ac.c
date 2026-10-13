/* func_0208a8ac @ 0x0208a8ac, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a890(unsigned char *p);

void func_0208a8ac(unsigned char *p)
{
    if (p[0x55]) {
        p[0x55] = 0;
        func_0208a890(p);
    }
}
