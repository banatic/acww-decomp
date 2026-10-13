/* func_ov054_02262528 @ 0x02262528, 0x44 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262528 {
  public:
    virtual int method();
};

typedef int (UnkStruct_02262528::*PMF)();

union PMFUnion {
    PMF pmf;
    struct {
        int low;
        int high;
    } words;
};

struct UnkStruct_02262528_2 {
    PMFUnion u;
    int pad_08[2];
};

extern UnkStruct_02262528_2 data_ov054_022632dc[];

extern "C" void func_ov054_02262528(UnkStruct_02262528 *self, int idx)
{
    int result = 1;
    if (data_ov054_022632dc[idx].u.words.low != 0) {
        result = (self->*data_ov054_022632dc[idx].u.pmf)();
    }
    if (result != 0) {
        *(int *) ((char *) self + 0x654) = idx;
    }
}
