/* func_ov096_0229cdec @ 0x0229cdec, 0x60 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e158(void *receiver);
extern int func_ov002_02208d4c(unsigned char *, int, int);

void func_ov096_0229cdec(unsigned char *arg)
{
    int n = func_ov096_0229e158(arg);
    if (n >= 100) {
        func_ov002_02208d4c(arg + 0x294c, 0x6e, 0x0b);
        func_ov002_02208d4c(arg + 0x294c, 0x6f, 0x0c);
    }
    if (n >= 1000) {
        func_ov002_02208d4c(arg + 0x294c, 0x70, 0x0d);
    }
    if (n >= 10000) {
        func_ov002_02208d4c(arg + 0x294c, 0x71, 0x0e);
    }
}
