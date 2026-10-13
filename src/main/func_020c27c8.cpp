/* func_020c27c8 @ 0x020c27c8, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_020b65c4(void);
void func_0208602c(void);
int func_020860c4(void);
void func_02087f4c(int, void *);
void func_020984e8(void);
void func_02099688(void);
int func_0208829c(void);
}

class UnkStruct_020c27c8 {
  public:
    virtual void vfunc_00() {}
    char pad1[0x58];
    char unk_5C;
    char pad_5D[0x5f7];
    int idx;
};

typedef int (UnkStruct_020c27c8::*Pmf)();

struct Entry {
    int unk_00;
    int unk_04;
    Pmf pmf;
};

extern Entry data_021fbbfc[];

extern "C" int func_020c27c8(UnkStruct_020c27c8 *self)
{
    int result = 0;
    int index = self->idx;

    if (data_021fbbfc[index].pmf != 0) {
        result = (self->*data_021fbbfc[index].pmf)();
    }

    if (func_020b65c4() == 0) {
        func_0208602c();
        func_02087f4c(func_020860c4(), &self->unk_5C);
    }

    if (func_020b65c4() == 0xb) {
        func_020984e8();
        func_02099688();
        if (func_0208829c() != 0) {
            func_0208602c();
            func_02087f4c(func_020860c4(), &self->unk_5C);
        }
    }

    return result;
}
