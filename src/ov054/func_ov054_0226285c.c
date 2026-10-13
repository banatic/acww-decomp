/* func_ov054_0226285c @ 0x0226285c, 0x118 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int);
extern void func_0203f130(void);
extern void func_0205467c(void *);
extern void func_0201b394(void *);
extern void func_0201a430(void *);
extern void func_020169a8(void *);
extern void func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void func_02032c64(void *);
extern void func_02089c88(void *);
extern void func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void func_02019eb0(void *);
extern void func_0201489c(void *);
extern void func_02082f60(void *);
extern void func_ov054_02261fb0(void *);

typedef struct UnkStruct_0226285c {
    void *vtable;
    char pad_04[0xe6];
    unsigned short version;
    unsigned char sub_ec[0x1b4];
    unsigned char unk_2A0[0xc];
    unsigned char unk_2AC[0x88];
    unsigned char unk_334[0x1c];
    unsigned char unk_350[0x58];
    unsigned char unk_3A8[0x2];
    unsigned char unk_3AA[0x6];
    unsigned char unk_3B0[0x68];
    unsigned char unk_418[0x8];
    unsigned char unk_420[0x7c];
    unsigned char unk_49C[0x30];
    unsigned char unk_4CC[0x48];
    unsigned char unk_514[0x44];
    unsigned char unk_558[0xc];
    unsigned char unk_564[0xb4];
    unsigned char unk_618[0x28];
    unsigned char unk_640[0x18];
    unsigned char unk_658[0x1];
} UnkStruct_0226285c;

extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov054_02263094[];

UnkStruct_0226285c *func_ov054_0226285c(void)
{
    UnkStruct_0226285c *obj = (UnkStruct_0226285c *) func_020edf70(0x818);
    if (obj == (UnkStruct_0226285c *) 0) {
        goto done;
    }

    func_0203f130();
    obj->vtable = (void *) data_020d8c64;
    obj->version = 0xfff1;

    func_0205467c(&obj->sub_ec);
    func_0201b394(&obj->unk_2A0);
    func_0201a430(&obj->unk_2AC);
    func_020169a8(&obj->unk_334);
    func_0201b324(&obj->unk_350);
    func_0201af14(&obj->unk_3A8);
    func_0201b370(&obj->unk_3AA);
    func_0201adec(&obj->unk_3B0);
    func_0201a7ec(&obj->unk_418);
    func_0201a794(&obj->unk_420);
    func_02032c64(&obj->unk_49C);
    func_02089c88(&obj->unk_4CC);
    func_020f55cc(&obj->unk_514);
    func_02013c2c(&obj->unk_558);
    func_02019eb0(&obj->unk_564);
    func_0201489c(&obj->unk_618);

    obj->vtable = (void *) data_020da088;
    func_02082f60(&obj->unk_640);

    obj->vtable = (void *) data_ov054_02263094;
    func_ov054_02261fb0(&obj->unk_658);

done:
    return obj;
}
