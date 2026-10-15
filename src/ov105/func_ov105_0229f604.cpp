/* func_ov105_0229f604 @ 0x0229f604, 0x120 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_ov105_0229c340(void *self, int flag);
void func_ov105_0229d1f0(void *self);
void func_ov105_0229c55c(void *self);
int func_0206fe54(void);
void func_ov002_02209eb8(void *addr);
void func_ov002_0220ad18(void *a, int b);
void func_ov094_0229a850(void *a, int b, int c);
void func_ov094_0229a804(void *a, int b, int c, int d);
void func_ov094_0229b738(void *a, int b, int c);
void func_ov094_02299d84(void *receiver, int value);
void func_ov094_0229b700(void *a, int b, int c);
int func_ov002_02207f60(void *self);
void func_0208f210(void *a, int b, int c);
}

class EmbeddedClass {
  public:
    virtual int func1();
    virtual int func2();
    virtual int func3();
};

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
    int unk_9C;
    int unk_A0;
    unsigned char pad_A4[0x258];
    int unk_2FC;
    unsigned char pad_300[0xa5c];
    int unk_D5C;
    unsigned char pad_D60[0x24];
    int unk_D84;
    unsigned char pad_D88[0x1634];
    EmbeddedClass unk_23BC;
    unsigned char pad_23C0[0xe4];
    int unk_24A4;
    unsigned char pad_24A8[0x898];
    EmbeddedClass unk_2D40;
    unsigned char pad_2D44[0x3274];
    int unk_5FB8;
} UnkStruct_0229f604;

extern "C" int func_ov105_0229f604(UnkStruct_0229f604 *self)
{
    if (func_ov105_0229c340(self, 1) == 0) {
        return 1;
    }

    self->unk_23BC.func3();
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(&self->unk_24A4);
    }

    func_ov105_0229d1f0(self);

    if (func_ov105_0229c340(self, 2) != 0) {
        func_ov002_0220ad18(&self->unk_5FB8, self->unk_9C);

        if (func_ov105_0229c340(self, 0x200) == 0) {
            func_ov094_0229a850(&self->unk_2FC, 0, self->unk_98 - 0x10);
        } else {
            if (self->unk_A0 != 0) {
                func_ov094_0229a804(&self->unk_2FC, 0, self->unk_98 - 0x10, self->unk_A0 + 0xc0);
            }
        }

        func_ov094_0229b738(&self->unk_D5C, 0, self->unk_98 - 0x10);
        func_ov094_02299d84(&self->unk_D84, self->unk_98 - 0x10);
    }

    if (func_ov105_0229c340(self, 0x200) != 0) {
        func_ov094_0229b700(&self->unk_D5C, self->unk_A0, -16);
        func_ov105_0229c55c(self);
    }

    if (func_ov105_0229c340(self, 0x80) != 0) {
        int tmp = func_ov002_02207f60(self);
        func_0208f210(&self->unk_2D40, 0, tmp);
        self->unk_2D40.func3();
    }

    return 1;
}
