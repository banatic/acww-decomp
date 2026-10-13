/* func_ov003_0222be40 @ 0x0222be40, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222be40;
typedef void (UnkStruct_0222be40::*PMF)(void);

struct Entry {
    PMF a;
    PMF b;
};

struct UnkStruct_0222be40 {
    unsigned char pad_00[0x23c];
    unsigned char unk_23C;
};

extern Entry data_ov003_0225f118[];

extern "C" void func_ov003_0222be40(UnkStruct_0222be40 *self)
{
    (self->*data_ov003_0225f118[self->unk_23C].a)();
}
