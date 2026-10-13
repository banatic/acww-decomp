/* func_ov004_02245c9c @ 0x02245c9c, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02230d94(void *);
extern int func_0208ffac(void);
extern void func_ov004_02245cf4(void *, int);

void func_ov004_02245c9c(void *self)
{
    if (func_ov004_02230d94(self) == 0) {
        if (func_0208ffac() != 0) {
            func_ov004_02245cf4(self, 2);
        } else {
            func_ov004_02245cf4(self, 1);
        }
    }
}
