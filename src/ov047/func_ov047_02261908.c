/* func_ov047_02261908 @ 0x02261908, 0x50 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201612c(void *self);
struct Pair {
    int a;
    int b;
};
extern struct Pair __ptmf_null;

struct UnkStruct_02261908 {
    char pad_00[0xb8];
    struct Pair pair1;
    struct Pair pair2;
    int flag;
    char pad_CC[2];
    unsigned short shortVal;
};

void func_ov047_02261908(struct UnkStruct_02261908 *self)
{
    struct Pair p;
    func_0201612c(self);
    self->flag = -1;
    self->shortVal = 0xfff1;
    p = __ptmf_null;
    self->pair1 = p;
    self->pair2 = p;
}
