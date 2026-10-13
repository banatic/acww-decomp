/* func_020a4ecc @ 0x020a4ecc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a4ecc {
    char _pad[0x50];
    int index;
};

struct Entry {
    int flag;
    int _pad;
    void (UnkStruct_020a4ecc::*pmf)();
};

extern Entry data_021f3eac[];
extern Entry data_021f3ea4[];

extern "C" int func_020a4ecc(UnkStruct_020a4ecc *self)
{
    if (data_021f3eac[self->index].flag != 0) {
        (self->*data_021f3ea4[self->index].pmf)();
    }
    return 1;
}
