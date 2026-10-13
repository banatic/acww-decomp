/* func_ov110_0229d8b0 @ 0x0229d8b0, 0x44 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022080a0(void *self, int flag);
extern void func_ov002_02207d24(char *ptr, int flag);
extern void func_ov110_0229cbe0(void *self);

void func_ov110_0229d8b0(volatile unsigned char *self)
{
    if (self[0xFC] != 0) {
        self[0xFC] = self[0xFC] - 1;
    } else {
        self[0x8C] = 4;
        func_ov002_022080a0((void *) self, 1);
        func_ov002_02207d24((char *) (self + 0x21F8), 0);
        func_ov110_0229cbe0((void *) self);
    }
}
