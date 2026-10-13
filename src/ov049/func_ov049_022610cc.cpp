/* func_ov049_022610cc @ 0x022610cc, 0x50 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022610cc {
    unsigned char pad_00[0xB8];
    unsigned int table_index;
};

typedef void (UnkStruct_022610cc::*PMF)();

struct Entry {
    PMF pmf;
    unsigned char flag;
};

extern Entry data_ov049_022633b0[];
extern "C" void func_ov049_022610c4(UnkStruct_022610cc *self, int value);

extern "C" void func_ov049_022610cc(UnkStruct_022610cc *self)
{
    if (data_ov049_022633b0[self->table_index].flag == 0 && data_ov049_022633b0[self->table_index].pmf != 0) {
        (self->*data_ov049_022633b0[self->table_index].pmf)();
        func_ov049_022610c4(self, 0);
    }
}
