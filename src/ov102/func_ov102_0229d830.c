/* func_ov102_0229d830 @ 0x0229d830, 0x5c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(void *);
extern int func_ov102_0229c2a8(void *, int);
extern void func_ov102_0229c288(void *, int);
extern void func_ov102_0229cd08(void *);
extern void func_ov102_0229cc60(void *, int);
extern void func_ov102_0229d740(void *);
extern void func_ov094_022999d8(void);

void func_ov102_0229d830(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x225c)) {
        if (func_ov102_0229c2a8(self, 0x200)) {
            func_ov102_0229c288(self, 0x200);
            func_ov102_0229cd08(self);
        } else {
            func_ov102_0229cc60(self, *((unsigned char *) ((char *) self + 0x25a2)));
            func_ov102_0229d740(self);
            func_ov094_022999d8();
        }
    } else {
        func_ov102_0229cd08(self);
    }
}
