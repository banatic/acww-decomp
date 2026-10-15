/* func_0203dc28 @ 0x0203dc28, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void func_020a8764(int *, int);
int func_020a835c(int *);
}

class UnkStruct_0203dc28 {
  public:
    char pad_00[0x28];
    int sub;
    char pad_2C[0x44 - 0x28 - 4];
    char flag44;
    void method();
};

union PMFUnion {
    void (UnkStruct_0203dc28::*method)();
    struct {
        int word0;
        int word1;
    } raw;
};

extern PMFUnion __ptmf_null;
extern PMFUnion data_020da924;
extern PMFUnion data_020da934;
extern PMFUnion data_020da92c;

extern "C" void func_0203dc28(UnkStruct_0203dc28 *self, int argument1)
{
    func_020a8764(&self->sub, (int) argument1);
    int type = self->sub;
    PMFUnion pmf = __ptmf_null;
    if (type == 4 && func_020a835c(&self->sub) != 0) {
        pmf = data_020da924;
    } else if (type == 0) {
        pmf = data_020da934;
    } else if (type == 0xb) {
        pmf = data_020da92c;
    }
    if (pmf.raw.word0 != 0) {
        (self->*pmf.method)();
    } else {
        self->flag44 = 0;
    }
}
