/* screen_object_5: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221ba58 @ 0x0221ba58, 0x1c bytes, Thumb
 * func_ov003_0221ba34 @ 0x0221ba34, 0x24 bytes, Thumb
 * func_ov003_0221ba10 @ 0x0221ba10, 0x24 bytes, Thumb
 * func_ov003_0221b9e4 @ 0x0221b9e4, 0x2c bytes, Thumb
 */

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221ba10;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *);
extern void *func_ov009_0226539c(void *);
extern void func_020edf54(void *self) __attribute__((arm));
extern unsigned char data_ov003_02238434[];
extern unsigned char data_ov003_022384f8[];

void *func_ov003_0221ba34(void *this);

void func_ov003_0221ba58(void)
{
    void *condition_value_3;
    condition_value_3 = (void *) (func_020edf70(0x2b8));
    if (condition_value_3 != 0) {
        func_ov003_0221ba34(condition_value_3);
    }
}

void *func_ov003_0221ba34(void *this)
{
    func_ov009_0226552c(this);
    *(void **) this = ((char *) data_ov003_02238434);
    *(void **) ((char *) this + 0xec) = ((char *) data_ov003_022384f8);
    return this;
}

void *func_ov003_0221ba10(UnkStruct_0221ba10 *obj)
{
    obj->unk_00 = ((int *) data_ov003_02238434);
    obj->unk_EC = ((int *) data_ov003_022384f8);
    func_ov009_0226539c(obj);
    return obj;
}

void *func_ov003_0221b9e4(void *self)
{
    *(unsigned int *) self = (unsigned int) data_ov003_02238434;
    *(unsigned int *) ((char *) self + 0xec) = (unsigned int) data_ov003_022384f8;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}
