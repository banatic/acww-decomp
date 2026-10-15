/* func_ov129_0229cc9c @ 0x0229cc9c, 0xb8 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov129_0229c874(void *self);
extern void func_ov129_0229c328(void *self);
extern void func_ov129_0229b7dc(void *self, int arg);
extern void func_ov129_0229c1f8(void *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov129_0229c39c(void *self);
extern int func_ov002_0220a620(void *sub, int arg);
extern void func_ov129_0229c3f4(void *self);
extern void func_ov129_0229c79c(void *self);
extern void func_ov129_0229c758(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov129_0229c574(void *self, int arg);
extern unsigned short data_021fbe40[];

void func_ov129_0229cc9c(void *self)
{
    unsigned short flags;

    if (func_ov002_02208014(self) != 0) {
        func_ov129_0229c874(self);
        return;
    }

    flags = data_021fbe40[1];

    if (flags & 1) {
        func_ov129_0229c328(self);
        return;
    } else if (flags & 0x800) {
        func_ov129_0229b7dc(self, 2);
        func_ov129_0229c1f8(self);
        func_ov002_02208098((void *) (self), 3);
        func_ov129_0229c39c(self);
        return;
    } else if (flags & 8) {
        if (func_ov002_0220a620((char *) self + 0x1d4, 6) == 0) {
            func_ov129_0229c3f4(self);
            func_ov129_0229c79c(self);
        }
        return;
    } else if (flags & 2) {
        func_ov129_0229c3f4(self);
        func_ov129_0229c758(self);
        return;
    } else {
        if (func_ov129_0229c574(self, func_ov002_02208008(self)) != 0) {
            func_ov129_0229c39c(self);
        }
        return;
    }
}
