/* func_02013518 @ 0x02013518, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// The call goes through a pointer to member function stored in self.

class UnkStruct_02013518;
typedef void *(UnkStruct_02013518::*PMF)(int);

struct UnkStruct_02013518_2 {
    PMF pmf;
};

class UnkStruct_02013518 {
  public:
    char pad_00[0x28];
    UnkStruct_02013518_2 *unk_28;
};

extern "C" void *func_02013518(UnkStruct_02013518 *self, int a)
{
    if (self->unk_28 != 0 && self->unk_28->pmf != 0) {
        return (self->*(self->unk_28->pmf))(a);
    }
    return 0;
}
