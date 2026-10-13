/* func_ov096_022a06d8 @ 0x022a06d8, 0x54 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov096_0229d0e4(void *);
extern void func_ov002_02209114(void *, int, int);
extern void func_ov002_02208098(void *, int);

void func_ov096_022a06d8(unsigned char *arg)
{
    int t;
    unsigned char *p;

    if (func_0208e484(arg + 0x2500) == 0) {
        return;
    }

    p = arg + arg[0xbc];
    arg[0xbb] = p[0x2951];

    t = func_ov096_0229d0e4(arg);
    func_ov002_02209114(arg + 0x2564, arg[0xbc], t);
    func_ov002_02208098(arg, 30);
}
