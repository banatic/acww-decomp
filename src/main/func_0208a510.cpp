/* func_0208a510 @ 0x0208a510, 0x154 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208a510_3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

struct UnkStruct_0208a510_2 {
    char pad_00[0x10];
    int unk_10;
    char pad1[0x14];
    const void *unk_28;
    int field_2c_;
    char pad3[8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad_3A[0x16];
    int unk_50;
    unsigned char unk_54;
    unsigned char unk_55;
    char pad_56[2];
    int unk_58;
};

struct UnkStruct_0208a510 {
    char pad_00[0x56];
    unsigned char unk_56;
    char pad1[9];
    UnkStruct_0208a510_3 sub60;
    char pad_64[0x2c];
    UnkStruct_0208a510_3 sub90;
    char pad3[0x2c];
    UnkStruct_0208a510_2 *unk_C0;
    UnkStruct_0208a510_2 *unk_C4;
    int unk_C8;
};

extern "C" {
extern UnkStruct_0208a510_2 *func_020a9034(int, int, int);
extern void func_02051694(UnkStruct_0208a510_2 *);
extern const char data_021c828c[];
extern const char data_021c8230[];
}

extern "C" void func_0208a510(UnkStruct_0208a510 *s)
{
    int f;

    if (s->unk_C8 == 2) {
        f = 1;
    } else {
        f = 0;
    }
    if (s->unk_C0 == 0) {
        s->unk_C0 = func_020a9034(0x41, 0x14, 2);
        if (s->unk_C0 != 0) {
            s->unk_C0->field_2c_ = 4;
            {
                UnkStruct_0208a510_2 *w = s->unk_C0;
                w->unk_10 = s->sub60.v3();
            }
            s->unk_C0->unk_58 = 1;
            if (s->unk_56 != 0) {
                s->unk_C0->unk_50 = 2;
            }
            if (f != 0) {
                s->unk_C0->unk_28 = data_021c828c;
            } else {
                s->unk_C0->unk_28 = data_021c8230;
            }
            s->unk_C0->unk_55 = 1;
            s->unk_C0->unk_39 = 0;
            s->unk_C0->unk_38 = 3;
            func_02051694(s->unk_C0);
        }
    }
    if (s->unk_C4 == 0 && f != 0) {
        s->unk_C4 = func_020a9034(0x61, 0x14, 2);
        if (s->unk_C4 != 0) {
            s->unk_C4->field_2c_ = 4;
            {
                UnkStruct_0208a510_2 *w = s->unk_C4;
                w->unk_10 = s->sub90.v3();
            }
            s->unk_C4->unk_58 = 1;
            if (s->unk_56 != 0) {
                s->unk_C4->unk_50 = 2;
            }
            s->unk_C4->unk_28 = data_021c828c;
            s->unk_C4->unk_55 = 1;
            s->unk_C4->unk_39 = 0;
            s->unk_C4->unk_38 = 3;
            func_02051694(s->unk_C4);
        }
    }
}
