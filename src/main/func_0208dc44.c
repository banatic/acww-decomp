/* func_0208dc44 @ 0x0208dc44, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208db3c(void);
extern void func_0208dc00(int);

void func_0208dc44(int r0)
{
    int r4 = r0;
    if (func_0208db3c() == 0) {
        func_0208dc00(r4);
    }
}
