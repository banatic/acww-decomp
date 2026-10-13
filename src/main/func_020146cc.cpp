/* func_020146cc @ 0x020146cc, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020146cc {
    unsigned char pad_04[4];
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char pad_0B[3];
    unsigned char unk_0E;
    virtual void v0();
};
typedef void (UnkStruct_020146cc::*PMF)(int);
struct UnkStruct_020146cc_2 {
    PMF pmf;
    int pad_08[2];
};
extern UnkStruct_020146cc_2 data_021c17c4[];

extern "C" void func_020146cc(UnkStruct_020146cc *self, int arg)
{
    if (self->unk_09 < 5 && self->unk_08 == 5) {
        self->unk_08 = self->unk_09;
        self->unk_0A = 0;
        self->unk_0E = 0;
        (self->*data_021c17c4[self->unk_08].pmf)(arg);
        self->unk_09 = 5;
    }
}
