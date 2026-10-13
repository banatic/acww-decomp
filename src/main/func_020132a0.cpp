/* func_020132a0 @ 0x020132a0, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020132a0;
typedef int (UnkStruct_020132a0::*Pmf)(void *);
struct Row {
    Pmf e[3];
};
struct Tbl {
    char pad_00[0x10];
    Row rows[2];
};
class UnkStruct_020132a0 {
  public:
    unsigned int unk_00;
    unsigned int unk_04;
    char pad_08[0x20];
    Tbl *unk_28;
};
extern "C" void func_02013934(UnkStruct_020132a0 *, void *);
extern "C" int func_020132a0(UnkStruct_020132a0 *self, void *arg)
{
    Tbl *t = self->unk_28;
    if (t) {
        unsigned int a = self->unk_00;
        if (a < 2) {
            unsigned int b = self->unk_04;
            if (b < 3) {
                if (t->rows[a].e[b]) {
                    int r = (self->*(t->rows[a].e[b]))(arg);
                    if (self->unk_00 == 1) {
                        func_02013934(self, arg);
                    }
                    return r;
                }
            }
        }
    }
    return 0;
}
