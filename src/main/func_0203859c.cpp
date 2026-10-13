/* func_0203859c @ 0x0203859c, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void *func_020e98d4(int);
void *func_020a8fe8(void *, int, int);
void func_02051648(void *);
void func_02051694(void *);
void func_020a8fb8(void *);
void func_020384f8(void *, void *, void *);
void func_020024f0(void *, void *, int, int);
void func_020e9898(void *);
}

class CVir {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

typedef struct {
    char pad_00[0x10];
    int unk_10;
    char pad_14[0x28 - 0x14];
    int unk_28;
    int unk_2C;
    void *unk_30;
    char pad_34[0x38 - 0x34];
    char unk_38;
    char unk_39;
    char pad_3A[0x50 - 0x3a];
    int unk_50;
    char pad_54[0x55 - 0x54];
    char unk_55;
    char pad_56[0x58 - 0x56];
    int unk_58;
} UnkStruct_0203859c;

typedef struct {
    char pad_00[0xe0];
    int unk_E0;
    int unk_E4;
    char pad_E8[0x250 - 0xe8];
    CVir vir;
    char pad2e4[0x2e4 - 0x250 - sizeof(CVir)];
    char unk_2E4[0x20];
} UnkStruct_0203859c_2;

extern unsigned char data_021c8230[];

extern "C" void func_0203859c(UnkStruct_0203859c_2 *self)
{
    void *r6 = func_020e98d4(0x800);
    if (r6 != 0) {
        UnkStruct_0203859c *r4 = (UnkStruct_0203859c *) func_020a8fe8(r6, 0x20, 2);
        if (r4 != 0) {
            r4->unk_2C = 5;
            r4->unk_10 = self->vir.v3();
            r4->unk_58 = 2;
            r4->unk_50 = 0;
            r4->unk_28 = (int) (unsigned int) data_021c8230;
            r4->unk_55 = 0;
            func_02051648(r4);
            r4->unk_39 = 1;
            r4->unk_38 = 0;
            func_02051694(r4);
            void *r7 = r4->unk_30;
            func_020a8fb8(r4);
            if (self->unk_E4 >= 0 && self->unk_E0 != 0) {
                func_020384f8(self, r6, r7);
            }
            func_020024f0(r6, self->unk_2E4, 0x20, 2);
        }
        func_020e9898(r6);
    }
}
