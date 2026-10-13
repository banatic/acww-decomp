/* func_ov119_0229c730 @ 0x0229c730, 0x2a bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229c648(void);
extern int func_ov119_0229c2e4(int);
extern int func_ov119_0229c75c(int);
extern int func_ov119_0229c2dc(int);

int func_ov119_0229c730(int r0)
{
    int r4 = r0;
    if (func_ov119_0229c648() != 0) {
        return 1;
    }
    func_ov119_0229c2e4(r4);
    func_ov119_0229c75c(r4);
    func_ov119_0229c2dc(r4);
    return 1;
}
