/* func_ov110_0229ea10 @ 0x0229ea10, 0xa4 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

struct Main;

extern "C" {
int func_ov110_0229c2c8(struct Main *self, int mode);
void func_ov110_0229ce0c(struct Main *self);
int func_0206fe54(void);
void func_ov002_02209eb8(void *ptr);
void func_ov094_0229a7cc(void *ptr, int a, unsigned int b);
void func_ov094_0229a850(void *ptr, int a, unsigned int b);
void func_ov094_0229b738(void *ptr, int a, unsigned int b);
void func_ov094_02299d84(void *ptr, unsigned int b);
}

struct Main {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned int unk_9C;
};

struct UnkStruct_0229ea10 {
    virtual int v0();
    virtual int v1();
    virtual int v2();
};

extern "C" int func_ov110_0229ea10(struct Main *self)
{
    if (func_ov110_0229c2c8(self, 1) == 0) {
        return 1;
    }
    if (((void) (((UnkStruct_0229ea10 *) ((char *) self + 0x21f8))->v2()), func_0206fe54()) != 0) {
        func_ov002_02209eb8((void *) ((char *) self + 0x22e0));
    }
    func_ov110_0229ce0c(self);
    if (func_ov110_0229c2c8(self, 0x80) != 0) {
        func_ov094_0229a7cc((void *) ((char *) self + 0x138), 0, self->unk_9C);
    }
    if (func_ov110_0229c2c8(self, 2) != 0) {
        func_ov094_0229a850((void *) ((char *) self + 0x138), 0, self->unk_98);
        func_ov094_0229b738((void *) ((char *) self + 0xb98), 0, self->unk_98);
        func_ov094_02299d84((void *) ((char *) self + 0xbc0), self->unk_98);
    }
    return 1;
}
