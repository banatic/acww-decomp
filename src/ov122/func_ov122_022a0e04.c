/* func_ov122_022a0e04 @ 0x022a0e04, 0x46 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022080a0(void *p, int a);
extern void func_ov122_0229f454(void *p, int a);
extern void func_ov122_0229efc8(void *p, int a);
extern void func_ov122_0229f940(void *p);
extern void func_ov095_0229b3ec(void *p);
extern void func_ov122_022a15b8(void *p, int a, int b);
extern void func_ov122_0229f2d0(void *p);

typedef struct Work Work;
struct Work {
    char pad_00[0x8c];
    char byte;
    char pad_8D[0xc0 - 0x8c - 1];
    char arr[1];
};

void func_ov122_022a0e04(Work *self)
{
    self->byte = 4;
    func_ov002_022080a0(self, 1);
    func_ov122_0229f454(self, 0);
    func_ov122_0229efc8(self, 4);
    func_ov122_0229f940(self);
    func_ov095_0229b3ec(self->arr);
    func_ov122_022a15b8(self, 1, 0);
    func_ov122_0229f2d0(self);
}
