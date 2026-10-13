/* func_ov100_0229ce24 @ 0x0229ce24, 0x34 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);

struct big_struct {
    char pad_00[0x2274];
    char sub[1];
    char pad_2275[0x65f];
    int unk_28D4;
    int unk_28D8;
};

void func_ov100_0229ce24(struct big_struct *this)
{
    this->unk_28D4 = func_ov002_02209f3c(&this->sub) - 2;
    this->unk_28D8 = func_ov002_02209f14(&this->sub) - 4;
}
