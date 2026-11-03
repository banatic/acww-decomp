/* villager_house_3: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221da10 @ 0x0221da10, 0x1c bytes, Thumb
 * func_ov003_0221d9c0 @ 0x0221d9c0, 0x50 bytes, Thumb
 * func_ov003_0221d980 @ 0x0221d980, 0x40 bytes, Thumb
 * func_ov003_0221d93c @ 0x0221d93c, 0x44 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[0xec - 4];
    void *unk_EC;
    char pad_F0[0x2b4 - (0xec + 4)];
    char unk_2B4;
    char pad_2B5[0x36c - (0x2b4 + 1)];
    char unk_36C;
} UnkStruct_0221d93c;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *p);
extern void *func_02055210(void *p);
extern void func_020565c8(void *p);
extern unsigned int data_ov003_0223c928[8];
extern void *func_020565b0(void *);
extern void *func_020551e0(void *);
extern void *func_ov009_0226539c(void *);
extern unsigned char data_ov003_02238f28[];
extern unsigned char data_ov003_02238fec[];
extern void func_020edf54(void *p);

void *func_ov003_0221d9c0(void *param);

void func_ov003_0221da10(void)
{
    void *condition_value_10;
    condition_value_10 = (void *) (func_020edf70(0x38c));
    if (condition_value_10 != 0) {
        func_ov003_0221d9c0(condition_value_10);
    }
}

void *func_ov003_0221d9c0(void *param)
{
    unsigned int i;
    unsigned int v;
    func_ov009_0226552c(param);
    *(void **) param = ((char *) data_ov003_02238f28);
    *(void **) ((char *) param + 0xEC) = ((char *) data_ov003_02238fec);
    func_02055210((char *) param + 0x2B4);
    func_020565c8((char *) param + 0x36C);
    i = 0;
    v = i;
    for (; i < 8; i++) {
        data_ov003_0223c928[i] = v;
    }
    return param;
}

void *func_ov003_0221d980(void *self)
{
    *(int *) self = (unsigned int) data_ov003_02238f28;
    *(int *) ((char *) self + 0xec) = (unsigned int) data_ov003_02238fec;
    func_020565b0((char *) self + 0x36c);
    func_020551e0((char *) self + 0x2b4);
    func_ov009_0226539c(self);
    return self;
}

UnkStruct_0221d93c *func_ov003_0221d93c(UnkStruct_0221d93c *p)
{
    p->unk_00 = ((char *) data_ov003_02238f28);
    p->unk_EC = ((char *) data_ov003_02238fec);
    func_020565b0(&p->unk_36C);
    func_020551e0(&p->unk_2B4);
    func_ov009_0226539c(p);
    func_020edf54(p);
    return p;
}
