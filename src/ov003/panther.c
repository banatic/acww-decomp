/* panther: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221d254 @ 0x0221d254, 0x1c bytes, Thumb
 * func_ov003_0221d230 @ 0x0221d230, 0x24 bytes, Thumb
 * func_ov003_0221d20c @ 0x0221d20c, 0x24 bytes, Thumb
 * func_ov003_0221d1e0 @ 0x0221d1e0, 0x2c bytes, Thumb
 * func_ov003_0221d1b8 @ 0x0221d1b8, 0x28 bytes, Thumb
 * func_ov003_0221d1b4 @ 0x0221d1b4, 0x4 bytes, Thumb
 * func_ov003_0221d17c @ 0x0221d17c, 0x38 bytes, Thumb
 */

struct UnkStruct_0221d20c {
    void *unk_00;
    char pad_04[0xE8];
    void *unk_EC;
};

typedef struct {
    int unk_00;
    int w1;
} UnkStruct_0221d17c;

typedef struct {
    char pad_00[0x2b4];
    unsigned char unk_2B4;
} UnkStruct_0221d17c_2;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *self);
extern void *func_ov009_0226539c(void *self);
extern void func_020edf54(void *self) __attribute__((arm));
extern unsigned char data_ov003_02238dbc[];
extern unsigned char data_ov003_02238e80[];
extern void func_0209e474(void *);

void *func_ov003_0221d230(void *self);

void func_ov003_0221d254(void)
{
    void *condition_value_9;
    condition_value_9 = (void *) (func_020edf70(0x2b8));
    if (condition_value_9 != 0) {
        func_ov003_0221d230(condition_value_9);
    }
}

void *func_ov003_0221d230(void *self)
{
    func_ov009_0226552c(self);
    *(void **) self = ((char *) data_ov003_02238dbc);
    *(void **) ((char *) self + 0xec) = ((char *) data_ov003_02238e80);
    return self;
}

void *func_ov003_0221d20c(void *self)
{
    struct UnkStruct_0221d20c *obj = (struct UnkStruct_0221d20c *) self;
    obj->unk_00 = ((char *) data_ov003_02238dbc);
    obj->unk_EC = ((char *) data_ov003_02238e80);
    func_ov009_0226539c(self);
    return self;
}

void *func_ov003_0221d1e0(void *self)
{
    *(unsigned int *) self = (unsigned int) data_ov003_02238dbc;
    *(unsigned int *) ((char *) self + 0xec) = (unsigned int) data_ov003_02238e80;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}

int func_ov003_0221d1b8(unsigned char *param0)
{
    unsigned int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    param0[0x2b4] = ((unsigned char *) local)[2];
    return 1;
}

int func_ov003_0221d1b4(void)
{
    return 1;
}

int func_ov003_0221d17c(UnkStruct_0221d17c_2 *p)
{
    UnkStruct_0221d17c s;
    int r;
    s.unk_00 = 0;
    s.w1 = 0;
    func_0209e474(&s);
    if (((unsigned char *) &s)[2] >= 6) {
        if (p->unk_2B4 < 6) {
            r = 0;
        } else {
            r = 1;
        }
    } else {
        r = 0;
    }
    return r;
}
