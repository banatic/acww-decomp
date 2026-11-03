/* fox_6: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221c250 @ 0x0221c250, 0x1c bytes, Thumb
 * func_ov003_0221c22c @ 0x0221c22c, 0x24 bytes, Thumb
 * func_ov003_0221c208 @ 0x0221c208, 0x24 bytes, Thumb
 * func_ov003_0221c1dc @ 0x0221c1dc, 0x2c bytes, Thumb
 * func_ov003_0221c1b4 @ 0x0221c1b4, 0x28 bytes, Thumb
 * func_ov003_0221c1a4 @ 0x0221c1a4, 0x10 bytes, Thumb
 * func_ov003_0221c16c @ 0x0221c16c, 0x38 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221c22c;

typedef struct {
    void *unk_00;
    char pad_04[0xE8];
    void *unk_EC;
} UnkStruct_0221c208;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_0221c1dc;

typedef struct {
    int unk_00;
    int w1;
} UnkStruct_0221c16c;

typedef struct {
    char pad_00[0x2bb];
    unsigned char unk_2BB;
} UnkStruct_0221c16c_2;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *unused0);
extern char data_ov003_02238630[];
extern char data_ov003_022386f4[];
extern void *func_ov009_0226539c(void *);
extern void func_020edf54(void *self);
extern void func_0209e474(int *p);
extern void func_ov003_0221bec8(void *argument0);

UnkStruct_0221c22c *func_ov003_0221c22c(UnkStruct_0221c22c *self);

void func_ov003_0221c250(void)
{
    void *condition_value_4;
    condition_value_4 = (void *) (func_020edf70(0x2bc));
    if (condition_value_4 != 0) {
        func_ov003_0221c22c((UnkStruct_0221c22c *) condition_value_4);
    }
}

UnkStruct_0221c22c *func_ov003_0221c22c(UnkStruct_0221c22c *self)
{
    func_ov009_0226552c(self);
    self->unk_00 = data_ov003_02238630;
    self->unk_EC = data_ov003_022386f4;
    return self;
}

void *func_ov003_0221c208(UnkStruct_0221c208 *this)
{
    this->unk_00 = ((char *) data_ov003_02238630);
    this->unk_EC = ((char *) data_ov003_022386f4);
    func_ov009_0226539c(this);
    return this;
}

UnkStruct_0221c1dc *func_ov003_0221c1dc(UnkStruct_0221c1dc *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) data_ov003_02238630);
    self->unk_EC = (unsigned int) ((unsigned int *) data_ov003_022386f4);
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}

int func_ov003_0221c1b4(unsigned char *param)
{
    int local[2];

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    param[0x2bb] = ((unsigned char *) local)[2];
    return 1;
}

int func_ov003_0221c1a4(void *argument0)
{
    func_ov003_0221bec8(argument0);
    return 1;
}

int func_ov003_0221c16c(UnkStruct_0221c16c_2 *p)
{
    UnkStruct_0221c16c s;
    int r;
    s.unk_00 = 0;
    s.w1 = 0;
    func_0209e474((int *) (&s));
    if (((unsigned char *) &s)[2] >= 6) {
        if (p->unk_2BB < 6) {
            r = 0;
        } else {
            r = 1;
        }
    } else {
        r = 0;
    }
    return r;
}
