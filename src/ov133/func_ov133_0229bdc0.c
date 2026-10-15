/* func_ov133_0229bdc0 @ 0x0229bdc0, 0x28 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(unsigned int p);
extern void func_ov133_0229b938(unsigned int p);
extern unsigned char *func_ov002_02208098(unsigned int p, unsigned char value);

void func_ov133_0229bdc0(unsigned int param1)
{
    if (func_0208e484(param1 + 0x11c) != 0) {
        func_ov133_0229b938(param1);
        func_ov002_02208098(param1, 3);
    }
}
