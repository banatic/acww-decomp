/* warp_object: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221c3dc @ 0x0221c3dc, 0x1c bytes, Thumb
 * func_ov003_0221c3b8 @ 0x0221c3b8, 0x24 bytes, Thumb
 * func_ov003_0221c394 @ 0x0221c394, 0x24 bytes, Thumb
 * func_ov003_0221c368 @ 0x0221c368, 0x2c bytes, Thumb
 * func_ov003_0221c314 @ 0x0221c314, 0x54 bytes, Thumb
 */

struct UnkStruct_0221c394;

struct UnkStruct_0221c394 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
};

struct UnkStruct_0221c368 {
    char *unk_00;
    char pad_04[0xE8];
    char *unk_EC;
};

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *ptr);
extern char data_ov003_022387a8[];
extern char data_ov003_0223886c[];
extern void *func_ov009_0226539c(struct UnkStruct_0221c394 *self);
extern void func_020edf54(void *p);
extern void func_0209e474(unsigned int *a);
extern void MI_CpuCopy8(unsigned int *src, unsigned int *dst, unsigned int size);
extern int func_0203fc78(int a, unsigned int *b, int c);
extern void *func_020b65c4(void);
extern int func_02084cd0(const void *a, void *b, void *c);
extern char data_ov003_02238784[];

void *func_ov003_0221c3b8(void *self);

void func_ov003_0221c3dc(void)
{
    void *condition_value_5;
    condition_value_5 = (void *) (func_020edf70(0x2b4));
    if (condition_value_5 != 0) {
        func_ov003_0221c3b8(condition_value_5);
    }
}

void *func_ov003_0221c3b8(void *self)
{
    func_ov009_0226552c(self);
    *(void **) self = data_ov003_022387a8;
    *(void **) ((char *) self + 0xec) = data_ov003_0223886c;
    return self;
}

struct UnkStruct_0221c394 *func_ov003_0221c394(struct UnkStruct_0221c394 *self)
{
    self->unk_00 = ((char *) data_ov003_022387a8);
    self->unk_EC = ((char *) data_ov003_0223886c);
    func_ov009_0226539c(self);
    return self;
}

struct UnkStruct_0221c368 *func_ov003_0221c368(struct UnkStruct_0221c368 *p)
{
    p->unk_00 = ((char *) data_ov003_022387a8);
    p->unk_EC = ((char *) data_ov003_0223886c);
    func_ov009_0226539c((struct UnkStruct_0221c394 *) p);
    func_020edf54(p);
    return p;
}

int func_ov003_0221c314(void *param)
{
    unsigned int a[2];
    unsigned int b[2];
    int flag;

    a[0] = 0;
    a[1] = 0;
    func_0209e474(a);
    MI_CpuCopy8(a, b, 8);
    flag = func_0203fc78(0x40, b, 0) != 0;
    if (flag) {
        func_02084cd0(data_ov003_02238784, func_020b65c4(), (char *) param + 0x5c);
    }
    return 1;
}
