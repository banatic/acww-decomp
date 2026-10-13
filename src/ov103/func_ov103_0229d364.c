/* func_ov103_0229d364 @ 0x0229d364, 0x50 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(const char *p);
extern void func_ov002_02209114(char *p, int b, int n);
extern void func_ov002_02208098(void *p, int n);

struct UnkStruct_0229d364 {
    char pad_00[0x26c5];
    unsigned char array[0x6e3];
    unsigned char b0;
    unsigned char b1;
};

void func_ov103_0229d364(struct UnkStruct_0229d364 *self)
{
    if (func_0208e484((char *) self + 0x2274) == 0) {
        return;
    }
    func_ov002_02209114((char *) self + 0x22d8, self->b1, 1);
    self->b0 = self->array[self->b1];
    func_ov002_02208098(self, 0x15);
}
