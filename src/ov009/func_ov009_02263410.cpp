/* func_ov009_02263410 @ 0x02263410, 0xd4 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02263410 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int f50();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
    virtual int v27();
    virtual int v28();
    virtual int v29();
    virtual int v30();
    virtual int v31();
    virtual int v32();
    virtual int v33();
    virtual int v34();
    virtual int f8c();
    unsigned char pad_04[0x8a];
    short unk_8E;
    unsigned char pad_90[0x1a5];
    unsigned char unk_235;
    unsigned char pad_236[0x4a];
    unsigned char unk_280;
};

extern "C" int func_020e8b4c(int, int);
extern "C" int func_020ea990(int, int);
extern "C" void func_0203edd0(UnkStruct_02263410 *);
extern "C" int func_ov009_02264c90(UnkStruct_02263410 *);

extern "C" int func_ov009_02263410(UnkStruct_02263410 *self, UnkStruct_02263410 *other)
{
    if (other == 0) {
        return 0;
    }
    if (func_020e8b4c((short) (self->unk_8E + 0x8000), other->unk_8E) > 0x1000) {
        goto fail;
    }
    if (func_ov009_02264c90(self) != 0) {
        if ((self->unk_235 & 8) == 0) {
            goto fail;
        }
        if (func_ov009_02264c90(self) != 2) {
            goto fail;
        }
        if (self->f8c() == 0) {
            func_0203edd0(self);
            self->unk_280 = 1;
            return 1;
        } else {
            func_0203edd0(self);
            self->unk_280 = 0;
            return 1;
        }
    } else {
        if (self->f8c() != 0) {
            goto fail;
        }
        int v1 = other->f50();
        int v2 = self->f50();
        int v3 = func_020ea990(v1, v2);
        func_0203edd0(self);
        self->unk_280 = 1;
        if (v3 < 0x3000) {
            return 1;
        } else {
            return 0;
        }
    }
fail:
    return 0;
}
