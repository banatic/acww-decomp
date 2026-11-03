/* countdown_3: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221d080 @ 0x0221d080, 0x1c bytes, Thumb
 * func_ov003_0221d064 @ 0x0221d064, 0x1c bytes, Thumb
 * func_ov003_0221d048 @ 0x0221d048, 0x1c bytes, Thumb
 * func_ov003_0221d038 @ 0x0221d038, 0x10 bytes, Thumb
 * func_ov003_0221cffc @ 0x0221cffc, 0x3c bytes, Thumb
 * func_ov003_0221cfc0 @ 0x0221cfc0, 0x3c bytes, Thumb
 * func_ov003_0221cf8c @ 0x0221cf8c, 0x34 bytes, Thumb
 * func_ov003_0221cf54 @ 0x0221cf54, 0x38 bytes, Thumb
 */

typedef struct {
    char pad_00[1];
    unsigned char unk_01;
} UnkStruct_0221d048;

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0221d048_2;

typedef struct {
    UnkStruct_0221d048 *unk_00;
    UnkStruct_0221d048_2 *unk_04;
} UnkStruct_0221d048_3;

struct func_ov003_0221d038_struct {
    char pad_00[0x1c];
    void (*fp)(void *);
    char pad_20[0x70];
    unsigned char unk_90;
};

typedef struct {
    char pad_00[0x2d4];
    signed char flag;
    unsigned char value;
} UnkStruct_0221cffc;

typedef struct {
    unsigned int pad_00[3];
    unsigned int unk_0C;
} UnkStruct_0221cffc_2;

typedef struct {
    char pad_00[0xb0];
    UnkStruct_0221cffc_2 *ptr;
} UnkStruct_0221cffc_3;

typedef struct {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
    char pad_F0[0x1c4];
    char unk_2B4;
} UnkStruct_0221cf8c;

extern int func_020edf70(int);
extern int func_ov003_0221ca9c(int);
extern void *func_ov003_0221cb30(void *object);
extern void *func_ov009_0226552c(void *);
extern void func_020565c8(void *);
extern unsigned char data_ov003_02238c54[];
extern unsigned char data_ov003_02238d18[];
extern void *func_020565b0(void *ptr);
extern void *func_ov009_0226539c(void *self);
extern void func_020edf54(void *p);

void func_ov003_0221cffc(UnkStruct_0221cffc *s, int comp, UnkStruct_0221cffc_3 *t);
void *func_ov003_0221cfc0(void *this);

void func_ov003_0221d080(void)
{
    void *condition_value_8;
    condition_value_8 = (void *) (func_020edf70(0x2f0));
    if (condition_value_8 != 0) {
        func_ov003_0221cfc0(condition_value_8);
    }
}

void func_ov003_0221d064(void)
{
    void *condition_value_7;
    condition_value_7 = (void *) (func_ov003_0221ca9c(0x2dc));
    if (condition_value_7 != 0) {
        func_ov003_0221cb30(condition_value_7);
    }
}

void func_ov003_0221d048(UnkStruct_0221d048_3 *s)
{
    void *t = s->unk_04->unk_2C;
    if (t != 0) {
        func_ov003_0221cffc((UnkStruct_0221cffc *) t, (unsigned char) s->unk_00->unk_01, (UnkStruct_0221cffc_3 *) s);
    }
}

void func_ov003_0221d038(struct func_ov003_0221d038_struct *obj)
{
    obj->fp = (void (*)(void *)) func_ov003_0221d048;
    obj->unk_90 = 2;
}

void func_ov003_0221cffc(UnkStruct_0221cffc *s, int comp, UnkStruct_0221cffc_3 *t)
{
    if (comp == s->flag) {
        t->ptr->unk_0C &= 0xffe0ffff;
        t->ptr->unk_0C |= ((unsigned int) s->value << 16);
    }
}

void *func_ov003_0221cfc0(void *this)
{
    func_ov009_0226552c(this);
    *(unsigned int *) this = (unsigned int) data_ov003_02238c54;
    *(unsigned int *) ((char *) this + 0xec) = (unsigned int) data_ov003_02238d18;
    func_020565c8((char *) this + 0x2b4);
    *((signed char *) ((char *) this + 0x2d4)) = -1;
    return this;
}

void *func_ov003_0221cf8c(void *self)
{
    UnkStruct_0221cf8c *s = self;
    s->unk_00 = (void *) data_ov003_02238c54;
    s->unk_EC = (void *) data_ov003_02238d18;
    func_020565b0(&s->unk_2B4);
    func_ov009_0226539c(s);
    return s;
}

void *func_ov003_0221cf54(void *arg)
{
    char *p = (char *) arg;
    *(unsigned int *) p = (unsigned int) (unsigned int) data_ov003_02238c54;
    p += 0xEC;
    *(unsigned int *) p = (unsigned int) (unsigned int) data_ov003_02238d18;
    func_020565b0((char *) arg + 0x2B4);
    func_ov009_0226539c(arg);
    func_020edf54(arg);
    return arg;
}
