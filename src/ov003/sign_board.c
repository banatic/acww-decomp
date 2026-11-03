/* sign_board: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221eaf0 @ 0x0221eaf0, 0x1c bytes, Thumb
 * func_ov003_0221eacc @ 0x0221eacc, 0x24 bytes, Thumb
 * func_ov003_0221eaa8 @ 0x0221eaa8, 0x24 bytes, Thumb
 * func_ov003_0221ea7c @ 0x0221ea7c, 0x2c bytes, Thumb
 * func_ov003_0221ea64 @ 0x0221ea64, 0x18 bytes, Thumb
 * func_ov003_0221ea50 @ 0x0221ea50, 0x12 bytes, Thumb
 * func_ov003_0221e9dc @ 0x0221e9dc, 0x74 bytes, Thumb
 * func_ov003_0221e9d8 @ 0x0221e9d8, 0x4 bytes, Thumb
 */

typedef struct UnkStruct_0221eacc {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221eacc;

typedef struct {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221eaa8;

struct UnkStruct_0221ea50 {
    char pad_00[0x5c];
    char member;
};

typedef struct {
    unsigned char pad0[0x10a];
    unsigned char unk_10A;
    unsigned char pad_10B[0x12c - 0x10b];
    int unk_12C;
    unsigned char pad_130[0x2b4 - 0x130];
    unsigned short unk_2B4;
} UnkStruct_0221e9dc;

typedef struct {
    unsigned char pad0[0x58];
    unsigned int unk_58;
} UnkStruct_0221e9dc_2;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *obj);
extern void *func_ov009_0226539c(UnkStruct_0221eaa8 *s);
extern char data_ov003_022395e8[];
extern char data_ov003_022396ac[];
extern void func_020edf54(void *);
extern int func_ov003_022203d0(void);
extern void func_020ad1f4(void *p);
extern void func_020a8164(void *p, void *d);
extern void *func_02062f90(void *dst, void *arg);
extern void func_02068404(int, int, void *);
extern void *func_02062f4c(void *dst);
extern char data_ov003_02239724;
extern UnkStruct_0221e9dc_2 data_021f39a8;

void *func_ov003_0221eacc(void *arg);

void func_ov003_0221eaf0(void)
{
    void *condition_value_15;
    condition_value_15 = (void *) (func_020edf70(0x2b8));
    if (condition_value_15 != 0) {
        func_ov003_0221eacc(condition_value_15);
    }
}

void *func_ov003_0221eacc(void *arg)
{
    UnkStruct_0221eacc *p = arg;
    func_ov009_0226552c(arg);
    p->unk_00 = ((char *) data_ov003_022395e8);
    p->unk_EC = ((char *) data_ov003_022396ac);
    return arg;
}

UnkStruct_0221eaa8 *func_ov003_0221eaa8(UnkStruct_0221eaa8 *s)
{
    s->unk_00 = data_ov003_022395e8;
    s->unk_EC = data_ov003_022396ac;
    func_ov009_0226539c(s);
    return s;
}

void *func_ov003_0221ea7c(void *arg)
{
    *(void **) arg = ((unsigned char *) data_ov003_022395e8);
    *((void **) ((char *) arg + 0xec)) = ((unsigned char *) data_ov003_022396ac);
    func_ov009_0226539c((UnkStruct_0221eaa8 *) arg);
    func_020edf54(arg);
    return arg;
}

int func_ov003_0221ea64(void *param)
{
    int result;
    result = func_ov003_022203d0();
    *(unsigned short *) ((char *) param + 0x2b4) = (unsigned short) result;
    return 1;
}

int func_ov003_0221ea50(struct UnkStruct_0221ea50 *self)
{
    func_020ad1f4(&self->member);
    return 1;
}

void func_ov003_0221e9dc(UnkStruct_0221e9dc *self)
{
    struct {
        short pad0;
        unsigned short val;
    } local1;
    unsigned char buffer[0x2c];
    unsigned short computed;

    func_020a8164((unsigned char *) self + 0xec, &data_ov003_02239724);

    self->unk_10A = (unsigned char) ((self->unk_2B4 % 0xe) + 1);

    if (data_021f39a8.unk_58 < 5) {
        computed = (unsigned short) (data_021f39a8.unk_58 + 0x1518);
    } else {
        computed = 0x1518;
    }
    local1.val = computed;

    func_02062f90(buffer, &local1.val);
    func_02068404(self->unk_12C, 1, buffer);
    func_02062f4c(buffer);
}

int func_ov003_0221e9d8(void)
{
    return 0;
}
