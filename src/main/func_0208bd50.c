/* func_0208bd50 @ 0x0208bd50, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e1f8(void);
extern void func_0206f5b0(void);
extern void func_0208bd18(void *);
extern int func_0208bf48(void *);
extern void func_0208bc30(void *);
extern int func_0208be84(void *, int);
extern int func_0203e204(void);

void func_0208bd50(void *param)
{
    if (func_0203e1f8()) {
        func_0206f5b0();
        func_0208bd18(param);
    } else if (func_0208bf48(param) == 0) {
        func_0208bc30(param);
    } else if (func_0208be84(param, 0) != 0) {
        func_0203e204();
    }
}
