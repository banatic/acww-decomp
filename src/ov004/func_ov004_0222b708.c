/* func_ov004_0222b708 @ 0x0222b708, 0xdc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short low : 7, middle : 4, high : 5;
} Packed;
extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern void func_0200c3b0(void *, int, int, int);
extern unsigned short *func_02096274(void);
extern void *func_02011368(void *);
extern short func_020997a8(void *);
extern unsigned short *func_0209627c(void);
extern int func_0200f86c(void *);
extern unsigned short *func_0209d358(unsigned short, unsigned short);
extern int func_020112bc(void *);
extern unsigned char *func_0209626c(void);
extern void func_0200d4e8(void *, int, int, int);
void func_ov004_0222b708(unsigned char *self)
{
    if (func_02056f94(self + 0x2d0)) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        if (self[0x7de]) {
            // Preserve the observed halfword store/reload before the copy.
            struct {
                volatile unsigned short value;
                unsigned short copy;
            } item;
            int mode, base;
            unsigned short *output, *first, *second;
            func_0200c3b0(self, 0, 5, -1);
            *func_02096274() = 0x4650;
            item.value = func_020997a8(func_02011368(self));
            item.copy = item.value;
            *func_0209627c() = item.copy;
            mode = func_0200f86c(self);
            output = func_0209d358(0, 80);
            base = func_020112bc(self);
            first = func_0209627c();
            second = func_0209627c();
            *output = base + 1000 * ((Packed *) first)->middle + 10 * ((Packed *) second)->high;
            if (!mode) {
                *func_0209626c() = 17;
            } else {
                *func_0209626c() = 0;
            }
        } else {
            func_0200d4e8(self, 0, 1, -1);
        }
    }
}
