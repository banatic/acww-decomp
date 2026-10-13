/* func_0208cd18 @ 0x0208cd18, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void *func_020a9034(int val, int n, int m);
extern char data_021c81d4;

class Callback {
  public:
    virtual int slot0();
    virtual int slot1();
    virtual int slot2();
    virtual int slot3();
};

struct Alloc {
    unsigned char pad_00[0x10];
    int unk_10;
    unsigned char pad1[0x28 - 0x14];
    void *unk_28;
    int unk_2C;
    unsigned char pad2[0x38 - 0x30];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad3[0x50 - 0x3a];
    int unk_50;
    unsigned char pad_54[0x55 - 0x54];
    unsigned char unk_55;
};

struct UnkStruct_0208cd18 {
    unsigned char pad_00[0x2c];
    void *field_obj;
    unsigned char pad1[0x6c - 0x30];
    Callback callback;
    unsigned char pad2[0xa6 - 0x70];
    unsigned char byte_flag;
    unsigned char pad3[0xa9 - 0xa7];
    unsigned char unk_A9;
};

extern "C" void func_0208cd18(UnkStruct_0208cd18 *self)
{
    int val;
    Alloc *p;

    if (self->unk_A9) {
        val = 0x174;
    } else {
        val = 0xa8;
    }

    self->field_obj = func_020a9034(val, 2, 1);

    if (self->field_obj != 0) {
        ((Alloc *) self->field_obj)->unk_2C = 4;
        ((Alloc *) self->field_obj)->unk_50 = 2;
        ((Alloc *) self->field_obj)->unk_55 = 1;
        ((Alloc *) self->field_obj)->unk_39 = 0;
        ((Alloc *) self->field_obj)->unk_38 = 0x5;
        ((Alloc *) self->field_obj)->unk_28 = (void *) &data_021c81d4;

        p = (Alloc *) self->field_obj;
        p->unk_10 = self->callback.slot3();

        self->byte_flag = 1;
    }
}
