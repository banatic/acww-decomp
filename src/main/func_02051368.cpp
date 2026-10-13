/* func_02051368 @ 0x02051368, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// The vtable is loaded through the register holding this.

struct UnkStruct_02051368_2 {
    void *p;
};

struct UnkStruct_02051368 {
    virtual void v0();
    virtual void v1();
    virtual void func8();

    char pad_04[0x14];    // 0x04
    int unk_18;           // 0x18
    int unk_1C;           // 0x1c
    char pad_20[0x04];    // 0x20
    int unk_24;           // 0x24
    void *unk_28;         // 0x28
    char pad_2C[0x0C];    // 0x2c
    unsigned char unk_38; // 0x38
    char pad_39[0x1C];    // 0x39
    unsigned char unk_55; // 0x55
    char pad_56[0x0A];    // 0x56
    int unk_60;           // 0x60
    char pad_64[0x08];    // 0x64
    int unk_6C;           // 0x6c
    int unk_70;           // 0x70
    unsigned char unk_74; // 0x74
    unsigned char unk_75; // 0x75
};

extern "C" void func_02051368(UnkStruct_02051368 *self)
{
    unsigned int r4, r6, ip8;

    r4 = *(unsigned short *) ((char *) ((UnkStruct_02051368_2 *) self->unk_28)->p + 6);
    r6 = (unsigned int) self->unk_24 << 3;

    self->unk_74 = self->unk_38;

    if (self->unk_18 != -1) {
        self->unk_70 = self->unk_18 << 5;
    } else if (self->unk_1C != 0) {
        self->unk_70 = 0;
    }

    self->unk_75 = 0;
    self->unk_6C = 0;

    while ((unsigned int) self->unk_6C < r4 && (unsigned int) self->unk_6C < r6) {
        ip8 = (unsigned int) self->unk_6C + 8;
        self->unk_75 = (ip8 >= r4 || ip8 >= r6) ? 1 : 0;

        self->func8();

        if (self->unk_55 != 0) {
            self->unk_70 += 0x400;
        } else {
            self->unk_70 += self->unk_60;
        }

        self->unk_6C += 8;
    }
}
