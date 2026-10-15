/* func_ov110_0229da00 @ 0x0229da00, 0x50 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02209f9c(void *);
extern int func_ov110_0229c2c8(void *, int);
extern void func_ov110_0229c2a8(void *, int);
extern void func_ov094_022999c0(void);
extern void func_ov110_0229cdb4(void *);

void func_ov110_0229da00(void *arg)
{
    char *self = (char *) arg;

    if (func_0208e484(self + 0x22e0)) {
        func_ov002_02208098((void *) (self), *(unsigned char *) (self + 0xf8));
    }

    if (func_ov002_02209f9c(self + 0x22e0)) {
        if (func_ov110_0229c2c8(self, 0x40)) {
            ((void) (func_ov110_0229c2a8(self, 0x40)), func_ov094_022999c0());
        }
        func_ov110_0229cdb4(self);
    }
}
