/* func_ov111_0229ff60 @ 0x0229ff60, 0x26 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov111_0229fdf0(void *);
extern void func_ov095_0229c05c(void *);
extern int func_ov111_0229efd8(void *, int);
extern void func_0209539c(void);

void func_ov111_0229ff60(void *param)
{
    void *r4 = param;
    func_ov111_0229fdf0(r4);
    func_ov095_0229c05c((char *) r4 + 0xac);
    if (func_ov111_0229efd8(r4, 0x10) == 0) {
        func_0209539c();
    }
}
