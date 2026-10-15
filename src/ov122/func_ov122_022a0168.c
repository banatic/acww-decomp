/* func_ov122_022a0168 @ 0x022a0168, 0x9c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

struct SomeUnk;

extern struct {
    unsigned short pad;
    unsigned short flag;
} data_021fbe40;

int func_ov122_0229efe8(struct SomeUnk *, int);
void func_ov122_0229efc8(struct SomeUnk *, int);
void func_ov122_0229efd8(struct SomeUnk *, int);
void func_ov122_0229f394(struct SomeUnk *);
int func_ov095_0229cda4(void *, int);
void func_ov002_0220a2b4(void *);
void func_ov002_0220a314(void *);
unsigned char *func_ov002_02208098(void *object, unsigned char value);
void func_ov122_0229f250(struct SomeUnk *);

int func_ov122_022a0168(struct SomeUnk *self)
{
    if ((data_021fbe40.flag & 0x800) == 0) {
        return 0;
    }

    if (func_ov122_0229efe8(self, 0x100) != 0) {
        func_ov122_0229efc8(self, 0x100);
    } else {
        func_ov122_0229efd8(self, 0x100);
        func_ov122_0229f394(self);
    }

    if (func_ov095_0229cda4((char *) self + 0xc0, -1) != 0) {
        if (func_ov122_0229efe8(self, 0x100) != 0) {
            func_ov002_0220a2b4((char *) self + 0x4058);
            func_ov002_02208098((void *) (self), 0xc);
        } else {
            func_ov002_0220a314((char *) self + 0x4058);
            func_ov002_02208098((void *) (self), 6);
        }
        func_ov122_0229f250(self);
    } else {
        func_ov122_0229f250(self);
    }
    return 1;
}
