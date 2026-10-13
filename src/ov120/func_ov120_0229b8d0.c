/* func_ov120_0229b8d0 @ 0x0229b8d0, 0x30 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov120_0229b64c(void *);
extern void func_ov120_0229aa80(void *);
extern void func_0208e95c(void *, int);
extern unsigned char data_021fbdd8;

void func_ov120_0229b8d0(void *p)
{
    if (!data_021fbdd8) {
        func_0208e95c((char *) p + 0x674, 3);
        func_ov120_0229b64c(p);
    }
    func_ov120_0229aa80(p);
}
