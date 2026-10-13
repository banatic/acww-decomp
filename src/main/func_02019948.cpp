/* func_02019948 @ 0x02019948, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02019948;
typedef void (UnkStruct_02019948::*PMF)(int);
struct UnkStruct_02019948_2 {
    unsigned char pad_00[0x10];
    PMF pmf;
};
class UnkStruct_02019948 {
  public:
    unsigned char pad_00[0x14];
    int unk_14;
    unsigned char pad_18[8];
    UnkStruct_02019948_2 *unk_20;
};
extern "C" int func_02019de8(UnkStruct_02019948 *p);
extern "C" void func_02019948(UnkStruct_02019948 *p, int a);
void func_02019948(UnkStruct_02019948 *p, int a)
{
    if (p->unk_20 != 0 && p->unk_20->pmf != 0) {
        (p->*(p->unk_20->pmf))(a);
    }
    if (func_02019de8(p) != 0) {
        p->unk_14 = 0;
    }
}
