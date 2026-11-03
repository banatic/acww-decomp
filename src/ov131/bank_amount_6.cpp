/* bank_amount_6: 3 functions, module ov131
 * mwccarm 1.2/base -O4,s
 * func_ov131_0229b700 @ 0x0229b700, 0x94 bytes, Thumb
 * func_ov131_0229b644 @ 0x0229b644, 0xbc bytes, Thumb, emits _ZN18Obj_ov131_0229b8f019func_ov131_0229b644Ev
 * func_ov131_0229b628 @ 0x0229b628, 0x1c bytes, Thumb, emits _ZN18Obj_ov131_0229b8f019func_ov131_0229b628Ev
 */

#include "cpp/ov131/Obj_ov131_0229b8f0.h"

class UnkStruct_0229b700;

typedef void (UnkStruct_0229b700::*PMF)();

class UnkStruct_0229b700 {
  public:
    char pad_00[0x8c];
    unsigned char selector;
};

extern "C" {
void func_ov131_0229b474(UnkStruct_0229b700 *);
void func_ov131_0229b43c(UnkStruct_0229b700 *);
}

extern const PMF data_ov131_0229b880;
extern const PMF data_ov131_0229b8a8;
extern const PMF data_ov131_0229b8d8;
extern const PMF data_ov131_0229b8d0;
extern "C" void func_ov131_0229b498(int x);
extern "C" void func_ov131_0229b490(int x);

extern "C" int func_ov131_0229b700(UnkStruct_0229b700 *this_ptr)
{
    static PMF pmf_table[4];
    static unsigned int initialized = 0;
    if (!(initialized & 1)) {
        pmf_table[0] = data_ov131_0229b880;
        pmf_table[1] = data_ov131_0229b8a8;
        pmf_table[2] = data_ov131_0229b8d8;
        pmf_table[3] = data_ov131_0229b8d0;
        initialized |= 1;
    }
    func_ov131_0229b474(this_ptr);
    (this_ptr->*pmf_table[this_ptr->selector])();
    func_ov131_0229b43c(this_ptr);
    return 1;
}

void Obj_ov131_0229b8f0::func_ov131_0229b644()
{
    static void (Obj_ov131_0229b8f0::*tbl[8])() = {
        &Obj_ov131_0229b8f0::func_ov131_0229b338, &Obj_ov131_0229b8f0::func_ov131_0229b304,
        &Obj_ov131_0229b8f0::func_ov131_0229b274, &Obj_ov131_0229b8f0::func_ov131_0229b24c,
        &Obj_ov131_0229b8f0::func_ov131_0229b1f0, &Obj_ov131_0229b8f0::func_ov131_0229b1c8,
        &Obj_ov131_0229b8f0::func_ov131_0229b188, &Obj_ov131_0229b8f0::func_ov131_0229b124};
    int idx = subState;
    (this->*tbl[idx])();
}

int Obj_ov131_0229b8f0::func_ov131_0229b628()
{
    int arg = (int) this;
    func_ov131_0229b498(arg);
    ((Obj_ov131_0229b8f0 *) arg)->func_ov131_0229b644();
    func_ov131_0229b490(arg);
    return 1;
}
