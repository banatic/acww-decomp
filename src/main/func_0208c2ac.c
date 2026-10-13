/* func_0208c2ac @ 0x0208c2ac, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208c260(void *p);
extern int func_0208c5bc(void *p, int b);
extern int func_020a7e50(void);
extern int func_020a7e44(void);
extern int func_0208c56c(void *p);
extern int func_0208c490(void *p);
extern void func_0208c42c(void *p);

void func_0208c2ac(unsigned char *self)
{
    unsigned char b = self[0xd4];
    if (b == 0) {
        func_0208c260(self);
        return;
    }
    if (func_0208c5bc(self, b) == 0) {
        int flag = 0;
        if (func_020a7e50() != 0) {
            if (func_0208c56c(self) != 0) {
                flag = 1;
            }
        } else {
            if (func_020a7e44() != 0) {
                if (func_0208c490(self) != 0) {
                    flag = 1;
                }
            }
        }
        if (flag != 0) {
            func_0208c42c(self);
        }
    }
}
