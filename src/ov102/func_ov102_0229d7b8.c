/* func_ov102_0229d7b8 @ 0x0229d7b8, 0x40 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d7b8;
extern unsigned char *func_ov002_022080a0(struct UnkStruct_0229d7b8 *self, unsigned char value);
extern int func_ov002_02207d24(char *ptr, int a);
extern void func_ov102_0229cb50(struct UnkStruct_0229d7b8 *self);

void func_ov102_0229d7b8(struct UnkStruct_0229d7b8 *self)
{
    unsigned char *timer;

    timer = (unsigned char *) self;
    timer += 0x25a9;
    if (*timer != 0) {
        *timer = *timer - 1;
        return;
    }
    *((unsigned char *) self + 0x8c) = 4;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((char *) self + 0x218c, 1);
    func_ov102_0229cb50(self);
}
