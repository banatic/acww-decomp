/* func_ov088_02278ba4 @ 0x02278ba4, 0x94 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278ba4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void func(int);

    char pad_04[0x1e - 0x04];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    void **unk_40;
    char pad_44[0xb8 - 0x44];
    void **unk_B8;
    unsigned char unk_BC;
};

extern "C" void func_ov088_02278f0c(UnkStruct_02278ba4 *, int);
extern "C" int func_0203fa4c(void);
extern "C" void func_ov088_02278a54(void *, int, int);

extern "C" void func_ov088_02278ba4(UnkStruct_02278ba4 *self)
{
    int id;

    id = self->unk_1E;
    if ((id >= 29) && (id <= 57)) {
        *((int *) (((char *) self->unk_40) + 0x14)) = 0;
        func_ov088_02278f0c(self, 3);
    }
    switch (self->unk_1E) {
        case 11:
            *((int *) (((char *) self->unk_40) + 0x14)) = 0;
            func_ov088_02278f0c(self, 1);
            break;

        case 23:
        case 24:
            self->unk_BC = self->unk_1E;
            func_ov088_02278f0c(self, 2);
            break;

        case 25: {
            int ret = func_0203fa4c();
            if (ret != (-1)) {
                func_ov088_02278a54(self->unk_B8, ret, self->unk_BC);
            }
        } break;

        case 26:
            self->func(2);
            break;

        default:
            break;
    }
}
