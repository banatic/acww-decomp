/* turtle4_talk_2: 3 functions, module ov084
 * mwccarm 1.2/base -O4,s
 * func_ov084_02278fbc @ 0x02278fbc, 0x24 bytes, Thumb
 * func_ov084_02278fa4 @ 0x02278fa4, 0x18 bytes, Thumb
 * func_ov084_02278f84 @ 0x02278f84, 0x20 bytes, Thumb
 */

struct UnkStruct_02278fbc {
    int *unk_00;
    char pad_04[0xb4];
    unsigned short unk_B8;
};

extern int data_ov084_0227941c;
extern void *func_0202eb70(void *);
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *p);

struct UnkStruct_02278fbc *func_ov084_02278fbc(struct UnkStruct_02278fbc *param)
{
    func_0202eb70(param);
    param->unk_00 = &data_ov084_0227941c;
    param->unk_B8 = 0xfff1;
    return param;
}

void *func_ov084_02278fa4(void *obj)
{
    *(void **) obj = (void *) ((char *) &data_ov084_0227941c);
    func_0202eb20(obj);
    return obj;
}

void *func_ov084_02278f84(void *self)
{
    *(void **) self = &data_ov084_0227941c;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
