/* func_ov087_022790ac @ 0x022790ac, 0x44 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022790ac {
  public:
    char pad_00[0x654];
    int unk_654;
    int someMethod();
};

typedef int (UnkStruct_022790ac::*PMF)();

struct Entry {
    PMF pmf;
    int pad_08;
    int pad_0C;
};

extern Entry data_ov087_022795c0[];

extern "C" void func_ov087_022790ac(UnkStruct_022790ac *obj, int idx)
{
    int result = 1;
    if (data_ov087_022795c0[idx].pmf != 0) {
        result = (obj->*data_ov087_022795c0[idx].pmf)();
    }
    if (result != 0) {
        obj->unk_654 = idx;
    }
}
