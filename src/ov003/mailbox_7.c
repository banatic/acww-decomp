/* mailbox_7: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221e984 @ 0x0221e984, 0x1c bytes, Thumb
 * func_ov003_0221e948 @ 0x0221e948, 0x3c bytes, Thumb
 * func_ov003_0221e908 @ 0x0221e908, 0x40 bytes, Thumb
 * func_ov003_0221e8c4 @ 0x0221e8c4, 0x44 bytes, Thumb
 */

typedef struct {
    int *unk_00;        // offset 0x00
    char pad_04[0xE8];  // offset 0x04 to 0xEC
    int *unk_EC;        // offset 0xEC
    char pad_F0[0x1C8]; // offset 0xF0 to 0x2B8
    char unk_2B8[0x20]; // offset 0x2B8
    char unk_2D8[0x20]; // offset 0x2D8
} UnkStruct_0221e948;

typedef struct UnkStruct_0221e908 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
    char pad_F0[0x1c8];
    char area_2b8;
    char pad_2B9[0x1f];
    char area_2d8;
} UnkStruct_0221e908;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221e8c4;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *p);
extern void func_020565c8(void *p);
extern void *func_020b7f70(void *p);
extern int data_ov003_0223948c;
extern int data_ov003_02239550;
extern int func_020b7f60(void *);
extern void *func_020565b0(void *);
extern void *func_ov009_0226539c(UnkStruct_0221e908 *);
extern void func_020edf54(void *);

void *func_ov003_0221e948(UnkStruct_0221e948 *p);

void func_ov003_0221e984(void)
{
    void *condition_value_14;
    condition_value_14 = (void *) (func_020edf70(0x2f8));
    if (condition_value_14 != 0) {
        func_ov003_0221e948((UnkStruct_0221e948 *) condition_value_14);
    }
}

void *func_ov003_0221e948(UnkStruct_0221e948 *p)
{
    func_ov009_0226552c(p);
    p->unk_00 = &data_ov003_0223948c;
    p->unk_EC = &data_ov003_02239550;
    func_020565c8(&p->unk_2B8);
    func_020b7f70(&p->unk_2D8);
    return p;
}

UnkStruct_0221e908 *func_ov003_0221e908(UnkStruct_0221e908 *self)
{
    self->unk_00 = ((char *) &data_ov003_0223948c);
    self->unk_EC = ((char *) &data_ov003_02239550);
    func_020b7f60(&self->area_2d8);
    func_020565b0(&self->area_2b8);
    func_ov009_0226539c(self);
    return self;
}

UnkStruct_0221e8c4 *func_ov003_0221e8c4(UnkStruct_0221e8c4 *p)
{
    p->unk_00 = &data_ov003_0223948c;
    p->unk_EC = &data_ov003_02239550;
    func_020b7f60((char *) p + 0x2d8);
    func_020565b0((char *) p + 0x2b8);
    func_ov009_0226539c((UnkStruct_0221e908 *) p);
    func_020edf54(p);
    return p;
}
