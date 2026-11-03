/* player_pick_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02245cc8 @ 0x02245cc8, 0x2c bytes, Thumb
 * func_ov004_02245c9c @ 0x02245c9c, 0x2c bytes, Thumb
 * func_ov004_02245c70 @ 0x02245c70, 0x2c bytes, Thumb
 */

extern void func_0208e508(void *p, int k);
extern void *func_0208e260(void *p);
extern int func_ov004_02230d94(void);
extern int func_0208ffac(void);
extern void func_ov004_02245cf4(void *, int);
extern int func_0208e278(void *p);

void func_ov004_02245cc8(char *self)
{
    unsigned char i;
    func_0208e508(self + 0x50, 0);
    for (i = 0; i < 5; i++) {
        func_0208e260(self + 0x9c + (i << 7));
    }
}

void func_ov004_02245c9c(void *self)
{
    if (func_ov004_02230d94() == 0) {
        if (func_0208ffac() != 0) {
            func_ov004_02245cf4(self, 2);
        } else {
            func_ov004_02245cf4(self, 1);
        }
    }
}

void func_ov004_02245c70(char *self)
{
    unsigned char i;
    func_0208e508(self + 0x50, 0);
    for (i = 0; i < 5; i++) {
        func_0208e278(self + 0x9c + (i << 7));
    }
}
