/* func_02054630 @ 0x02054630, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd07c;
extern char data_020dd08c;
extern char data_020dd09c;
extern void func_02056ed4(void *p);
extern void func_02057078(void *p);
extern void *func_02054ad0(void *p);

struct SubA {
    void *ptr;
};
struct SubB {
    void *ptr;
};
struct SubC {
    int pad_00;
};
struct SubD {
    int pad_00;
};

struct UnkStruct_02054630 {
    void *unk_00;
    char pad_04[0x9c - 4];
    struct SubA subA;
    char pad_A0[0xb8 - (0x9c + 4)];
    struct SubB subB;
    char pad_BC[0x158 - (0xb8 + 4)];
    struct SubC subC;
    char pad_15C[0x170 - (0x158 + 4)];
    struct SubD subD;
};

struct UnkStruct_02054630 *func_02054630(struct UnkStruct_02054630 *self)
{
    self->unk_00 = &data_020dd07c;
    self->subA.ptr = &data_020dd08c;
    self->subB.ptr = &data_020dd09c;
    func_02056ed4(&self->subD);
    func_02057078(&self->subC);
    func_02054ad0(self);
    return self;
}
