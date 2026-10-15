/* func_ov122_022a0098 @ 0x022a0098, 0x64 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern int func_ov095_0229cf64(void *a, int b);
extern int func_ov122_022a0be4(void *a, int b);
extern void func_ov095_0229c8e4(void *a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

int func_ov122_022a0098(unsigned char *self)
{
    if ((data_021fbe40[1] & 0x200) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(self + 0xc0, 0xb) != 0) {
        return 0;
    }
    func_ov122_022a0be4(self, 0x118);
    func_ov095_0229c8e4(self + 0xc0, 0x109);
    self[0xb4] = self[0x8d];
    func_ov002_02208098((void *) (self), 0xe);
    return 1;
}
