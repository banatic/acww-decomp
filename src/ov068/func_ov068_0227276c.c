/* func_ov068_0227276c @ 0x0227276c, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern void func_02095ec4(void);
extern void *func_ov068_02272cd4(void *);
extern void func_02095a8c(void *, int);
extern void func_ov068_02272a7c(void *, int);
extern void func_02055124(void *);

void func_ov068_0227276c(unsigned char *self)
{
    if (func_02056f94(self + 0x1d8)) {
        unsigned char b = self[0x2dd];
        switch (b) {
            case 0x12:
                func_02095ec4();
                func_02095a8c(func_ov068_02272cd4(self), 4);
                break;
            case 0x1c:
                func_ov068_02272a7c(self, 4);
                // fall through
        }
        if (self[0x2dd] < 200) {
            self[0x2dd]++;
        }
    } else {
        func_02055124(self + 0x13c);
    }
}
