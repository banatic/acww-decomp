/* spawn_spot: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221eee8 @ 0x0221eee8, 0x1c bytes, Thumb
 * func_ov003_0221eec4 @ 0x0221eec4, 0x24 bytes, Thumb
 * func_ov003_0221eea0 @ 0x0221eea0, 0x24 bytes, Thumb
 * func_ov003_0221ee74 @ 0x0221ee74, 0x2c bytes, Thumb
 * func_ov003_0221ee54 @ 0x0221ee54, 0x20 bytes, Thumb
 * func_ov003_0221ee50 @ 0x0221ee50, 0x4 bytes, Thumb
 * func_ov003_0221ee4c @ 0x0221ee4c, 0x4 bytes, Thumb
 * func_ov003_0221ee48 @ 0x0221ee48, 0x4 bytes, Thumb
 */

struct UnkStruct_0221eea0 {
    unsigned int unk_00;
    unsigned char pad_04[0xE8];
    unsigned int unk_EC;
};

struct UnkStruct_0221ee74 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
};

extern void *func_020edf70(unsigned int);
extern void *func_ov009_0226552c(void *);
extern unsigned char data_ov003_022398e8[];
extern unsigned char data_ov003_022399ac[];
extern void *func_ov009_0226539c(struct UnkStruct_0221eea0 *obj);
extern void func_020edf54(struct UnkStruct_0221ee74 *);
extern char data_ov003_022398c4;
extern int func_020b65c4(void);
extern int func_02084cd0(void *a, int b, void *c);

void *func_ov003_0221eec4(void *this);

void func_ov003_0221eee8(void)
{
    void *p;
    p = func_020edf70(0x2b4);
    if (p) {
        func_ov003_0221eec4(p);
    }
}

void *func_ov003_0221eec4(void *this)
{
    void *p;
    func_ov009_0226552c(this);
    *(void **) this = (void *) data_ov003_022398e8;
    p = (char *) this + 0xec;
    *(void **) p = (void *) data_ov003_022399ac;
    return this;
}

void *func_ov003_0221eea0(struct UnkStruct_0221eea0 *obj)
{
    struct UnkStruct_0221eea0 *self = obj;
    self->unk_00 = (unsigned int) data_ov003_022398e8;
    self->unk_EC = (unsigned int) data_ov003_022399ac;
    func_ov009_0226539c(self);
    return self;
}

struct UnkStruct_0221ee74 *func_ov003_0221ee74(struct UnkStruct_0221ee74 *this)
{
    this->unk_00 = ((char *) data_ov003_022398e8);
    this->unk_EC = ((char *) data_ov003_022399ac);
    func_ov009_0226539c((struct UnkStruct_0221eea0 *) this);
    func_020edf54(this);
    return this;
}

int func_ov003_0221ee54(void *arg)
{
    int ret;
    ret = func_020b65c4();
    func_02084cd0(&data_ov003_022398c4, ret, (char *) arg + 0x5c);
    return 1;
}

int func_ov003_0221ee50(void)
{
    return 1;
}

int func_ov003_0221ee4c(void)
{
    return 1;
}

int func_ov003_0221ee48(void)
{
    return 1;
}
