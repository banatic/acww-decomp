/* func_0201ef3c @ 0x0201ef3c, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02081d20(int);
extern "C" int func_020644cc(int);
extern "C" void func_0202da88(void *, void *);
extern "C" void func_0206844c(void *, void *, int);

extern char data_021c25d4[];
extern char data_021f43e8[];
extern int data_020c8ba0;

struct MemberArg {
    int word;
    unsigned char byte;
};

class UnkStruct_0201ef3c {
  public:
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    void (UnkStruct_0201ef3c::*pmf)(MemberArg *);
    char pad_B8[0x12c - 0xb8];
    int unk_12C;
};

extern "C" void func_0201ef3c(UnkStruct_0201ef3c *obj)
{
    int r4;
    if (obj->unk_12C != 0) {
        r4 = func_02081d20(obj->unk_12C);
    } else {
        r4 = 0;
    }

    if (r4 + 0x100 > func_020644cc(0x200)) {
        func_0202da88(obj, data_021c25d4);

        struct {
            unsigned char first;
            MemberArg arg;
        } local;

        if (obj->pmf) {
            (obj->*obj->pmf)(&local.arg);
        }
        local.first = local.arg.byte;
        func_0206844c(obj->unk_40, &local, local.arg.word);
    } else {
        func_0206844c(obj->unk_40, data_021f43e8, data_020c8ba0);
    }
}
