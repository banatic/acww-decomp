/* func_0202f018 @ 0x0202f018, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02082f48(void *);
extern void func_02014898(void *);
extern void func_02019eac(void *);
extern void func_02013c28(void *);
extern void func_020f5914(void *) __attribute__((target("arm")));
extern void func_02089c70(void *);
extern void func_02032c50(void *);
extern void func_0201a790(void *);
extern void func_0201a7e8(void *);
extern void func_0201ade4(void *);
extern void func_0201b320(void *);
extern void func_02016998(void *);
extern void func_0201a3f8(void *);
extern void func_0201b390(void *);
extern void func_02054630(void *);
extern void func_0203f080(void *);

typedef struct UnkStruct_0202f018 {
    void *unk_00;       // 0x00
    char pad_04[0xe8];  // 0x04 - 0xeb
    char unk_EC;        // 0xec
    char pad_ED[0x1b3]; // 0xed - 0x29f
    char unk_2A0;       // 0x2a0
    char pad_2A1[0xb];  // 0x2a1 - 0x2ab
    char unk_2AC;       // 0x2ac
    char pad_334[0x87]; // 0x2ad - 0x333
    char unk_334;       // 0x334
    char pad_350[0x1b]; // 0x335 - 0x34f
    char unk_350;       // 0x350
    char pad_351[0x5f]; // 0x351 - 0x3af
    char unk_3B0;       // 0x3b0
    char pad_418[0x67]; // 0x3b1 - 0x417
    char unk_418;       // 0x418
    char pad_420[0x7];  // 0x419 - 0x41f
    char unk_420;       // 0x420
    char pad_421[0x7b]; // 0x421 - 0x49b
    char unk_49C;       // 0x49c
    char pad_49D[0x2f]; // 0x49d - 0x4cb
    char unk_4CC;       // 0x4cc
    char pad_514[0x47]; // 0x4cd - 0x513
    void *unk_514;      // 0x514
    char pad_558[0x40]; // 0x518 - 0x557
    char unk_558;       // 0x558
    char pad_564[0xb];  // 0x559 - 0x563
    char unk_564;       // 0x564
    char pad_618[0xb3]; // 0x565 - 0x617
    char unk_618;       // 0x618
    char pad_640[0x27]; // 0x619 - 0x63f
    char unk_640;       // 0x640
} UnkStruct_0202f018;

extern unsigned char data_020d8414[];
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];

UnkStruct_0202f018 *func_0202f018(UnkStruct_0202f018 *self)
{
    self->unk_00 = (void *) data_020da088;
    func_02082f48(&self->unk_640);
    self->unk_00 = (void *) data_020d8c64;
    func_02014898(&self->unk_618);
    func_02019eac(&self->unk_564);
    func_02013c28(&self->unk_558);
    self->unk_514 = (void *) data_020d8414;
    func_020f5914(&self->unk_514);
    func_02089c70(&self->unk_4CC);
    func_02032c50(&self->unk_49C);
    func_0201a790(&self->unk_420);
    func_0201a7e8(&self->unk_418);
    func_0201ade4(&self->unk_3B0);
    func_0201b320(&self->unk_350);
    func_02016998(&self->unk_334);
    func_0201a3f8(&self->unk_2AC);
    func_0201b390(&self->unk_2A0);
    func_02054630(&self->unk_EC);
    func_0203f080(self);
    return self;
}
