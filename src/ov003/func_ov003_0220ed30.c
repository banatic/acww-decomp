/* func_ov003_0220ed30 @ 0x0220ed30, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200fbe0(void *self);
extern void func_0205eae0(void *ptr, int a, int b, int c);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f27c(void *self, int a);
extern void func_0200f328(void *self, int a);

typedef struct UnkStruct_0220ed30_2 {
    int unk_00;
    char unk_04;
} UnkStruct_0220ed30_2;

typedef struct {
    char pad_00[0x5a0];
    char other[0x7d4 - 0x5a0];
    UnkStruct_0220ed30_2 sub;
} UnkStruct_0220ed30;

void func_ov003_0220ed30(UnkStruct_0220ed30 *self)
{
    UnkStruct_0220ed30_2 *p = &self->sub;
    int ret = func_0200fbe0(self);

    self->sub.unk_00 = ret;

    switch (ret) {
        case 4:
            func_0205eae0(&self->other, 7, 2, 1);
            func_020109a0(self, 0x8d, 2, 0);
            break;
        case 3:
            func_0205eae0(&self->other, 0x1d, 2, 1);
            func_020109a0(self, 0x8d, 2, 0);
            break;
        case 10:
            func_020109a0(self, 0x8d, 2, 0);
            break;
        default:
            func_020109a0(self, 0x8b, 2, 0);
            break;
    }

    p->unk_04 = 0;
    func_0200f27c(self, 9);
    func_0200f328(self, 0x7db);
}
