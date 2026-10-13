/* func_ov096_022a04a4 @ 0x022a04a4, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(unsigned char *p);
extern void func_ov002_02208098(unsigned char *p, unsigned char b);
extern int func_ov002_02209f9c(unsigned char *p);
extern int func_ov096_0229c2fc(unsigned char *p, int b);
extern void func_ov096_0229c2dc(unsigned char *p, int b);
extern void func_ov094_022999c0(void);
extern void func_ov096_0229ea5c(unsigned char *p);

void func_ov096_022a04a4(unsigned char *p)
{
    if (func_0208e484(p + 0x2500)) {
        func_ov002_02208098(p, p[0xBA]);
    }
    if (func_ov002_02209f9c(p + 0x2500)) {
        if (func_ov096_0229c2fc(p, 0x40)) {
            func_ov096_0229c2dc(p, 0x40);
            func_ov094_022999c0();
        }
        func_ov096_0229ea5c(p);
    }
}
