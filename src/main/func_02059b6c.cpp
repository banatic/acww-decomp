/* func_02059b6c @ 0x02059b6c, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02059b6c {
    unsigned char pad_04[0x5c - 4];
    int unk_5C;
    int unk_60;
    int unk_64;
    int unk_68;
    unsigned char pad_6C[0xc8 - 0x6c];
    unsigned char c8;
    unsigned char pad_C9[0xd5 - 0xc9];
    unsigned char d5;
    short d6;
    unsigned char pad_D8[2];
    unsigned char da;
    unsigned char pad_DB[1];
    unsigned char dc[4];

    virtual void m0();

    typedef void (UnkStruct_02059b6c::*PMF)();
};

extern UnkStruct_02059b6c::PMF data_021c9460[12][2][2];

extern "C" {
extern void func_02059920(UnkStruct_02059b6c *self);
extern int func_0205989c(UnkStruct_02059b6c *self);
extern void func_020044d0(void *p, int *args);
extern void func_020e8858(void *p);

int func_02059b6c(UnkStruct_02059b6c *self)
{
    if (self->unk_5C >= 0 && self->unk_5C < 2) {
        unsigned char k = self->da;
        if (k < 12) {
            self->c8 = k;
            self->d6 = 0;
            if (data_021c9460[self->c8][self->unk_5C][0] != 0) {
                (self->*data_021c9460[self->c8][self->unk_5C][0])();
            }
            func_02059920(self);
        }
        if (self->c8 < 12) {
            if (data_021c9460[self->c8][self->unk_5C][1] != 0) {
                int args[3];
                (self->*data_021c9460[self->c8][self->unk_5C][1])();
                args[0] = self->unk_60;
                args[1] = self->unk_64;
                args[2] = self->unk_68;
                func_020044d0(self->dc, args);
            }
        }
        if (func_0205989c(self) != 0) {
            func_020e8858(&self->d5);
        }
    }
    return 1;
}
}
