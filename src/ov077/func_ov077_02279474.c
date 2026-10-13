/* func_ov077_02279474 @ 0x02279474, 0x64 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov077_02278ca0(void *a, void *b);
extern void func_0201b38c(void *a, int b);
extern void func_0201b388(void *a, int b);

int func_ov077_02279474(unsigned char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    self[0x718] = 0xff;
    func_0201c280(self, self + 0x658);
    func_ov077_02278ca0(self + 0x658, self);
    func_0201b38c(self + 0x2a0, 0xfc);
    func_0201b388(self + 0x2a0, 0xfc);
    self[0x511] = 0;
    self[0x510] = 0;
    return 1;
}
