/* func_0208b1dc @ 0x0208b1dc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208bfc0(unsigned char *p);
extern int func_0208bfa0(unsigned char *p);
extern void func_0208b1a0(unsigned char *p);
extern void func_0208bfc8(unsigned char *p);
extern void func_0208b0d8(unsigned char *p);

void func_0208b1dc(unsigned char *p)
{
    if (p[0x348] != 0 || p[0x349] != 0) {
        func_0208bfc0(p + 0x1c4);
        if (func_0208bfa0(p + 0x1c4) != 0) {
            func_0208b1a0(p);
        }
    } else {
        func_0208bfc8(p + 0x1c4);
    }
    func_0208b0d8(p);
}
