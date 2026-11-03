/* sequence4_8: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02272f5c @ 0x02272f5c, 0x1c bytes, Thumb
 * func_ov068_02272f38 @ 0x02272f38, 0x24 bytes, Thumb
 * func_ov068_02272f14 @ 0x02272f14, 0x24 bytes, Thumb
 * func_ov068_02272ee8 @ 0x02272ee8, 0x2c bytes, Thumb
 */

struct UnkStruct_02272f38 {
    unsigned char *unk_00;
    unsigned char pad_04[0xe8];
    unsigned char *unk_EC;
};

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02272f14;

typedef struct {
    unsigned int a;
    unsigned char pad_04[0xe8];
    unsigned int b;
} UnkStruct_02272ee8;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *p);
extern unsigned char data_ov068_02277750[];
extern unsigned char data_ov068_02277814[];
extern void *func_ov009_0226539c(void *);
extern void func_020edf54(void *);

struct UnkStruct_02272f38 *func_ov068_02272f38(struct UnkStruct_02272f38 *this);

void func_ov068_02272f5c(void)
{
    void *condition_value_21;
    condition_value_21 = (void *) (func_020edf70(0x2e8));
    if (condition_value_21 != 0) {
        func_ov068_02272f38((struct UnkStruct_02272f38 *) condition_value_21);
    }
}

struct UnkStruct_02272f38 *func_ov068_02272f38(struct UnkStruct_02272f38 *this)
{
    func_ov009_0226552c(this);
    this->unk_00 = data_ov068_02277750;
    this->unk_EC = data_ov068_02277814;
    return this;
}

void *func_ov068_02272f14(UnkStruct_02272f14 *obj)
{
    obj->unk_00 = ((int *) data_ov068_02277750);
    obj->unk_EC = ((int *) data_ov068_02277814);
    func_ov009_0226539c(obj);
    return obj;
}

void *func_ov068_02272ee8(void *arg)
{
    UnkStruct_02272ee8 *obj = (UnkStruct_02272ee8 *) arg;
    obj->a = (unsigned int) ((char *) data_ov068_02277750);
    {
        char *q = (char *) obj;
        q += 0xec;
        *(unsigned int *) q = (unsigned int) ((char *) data_ov068_02277814);
    }
    func_ov009_0226539c(arg);
    func_020edf54(arg);
    return arg;
}
