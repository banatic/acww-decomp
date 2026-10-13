/* func_ov004_02245d60 @ 0x02245d60, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// Table of pointers to member functions, 16-byte entries with the pointer at +8.
struct UnkStruct_02245d60;
typedef void (UnkStruct_02245d60::*PMF)(void);
struct Entry {
    int a;
    int b;
    PMF fn;
};
struct UnkStruct_02245d60 {
    unsigned char pad_00[0x320];
    int idx;
};
extern Entry data_ov004_0225fe94[];
extern "C" {
extern void func_ov004_0224564c(UnkStruct_02245d60 *);
extern void func_ov004_02245744(UnkStruct_02245d60 *);
int func_ov004_02245d60(UnkStruct_02245d60 *self)
{
    func_ov004_0224564c(self);
    func_ov004_02245744(self);
    if (data_ov004_0225fe94[self->idx].fn != 0) {
        (self->*(data_ov004_0225fe94[self->idx].fn))();
    }
    return 1;
}
}
