/* text_walker_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a92b0 @ 0x020a92b0, 0x28 bytes, Thumb
 * func_020a9298 @ 0x020a9298, 0x18 bytes, Thumb
 * func_020a9278 @ 0x020a9278, 0x20 bytes, Thumb
 * func_020a9260 @ 0x020a9260, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0x20];
    int unk_24;
    unsigned char unk_28;
} UnkStruct_020a92b0;

typedef struct UnkStruct_020a9298 {
    void *unk_00;
} UnkStruct_020a9298;

extern void *func_020a9484(UnkStruct_020a92b0 *self);
extern unsigned char data_020e3de4[];
extern void *func_020a941c(void *obj);
extern void func_020edb3c(void *obj);

UnkStruct_020a92b0 *func_020a92b0(UnkStruct_020a92b0 *self, char value)
{
    func_020a9484(self);
    self->unk_00 = (unsigned int) data_020e3de4;
    self->unk_24 = 0;
    self->unk_28 = value;
    return self;
}

UnkStruct_020a9298 *func_020a9298(UnkStruct_020a9298 *param)
{
    param->unk_00 = ((char *) data_020e3de4);
    func_020a941c((void *) param);
    return param;
}

void *func_020a9278(void *obj)
{
    ((void **) obj)[0] = ((char *) data_020e3de4);
    func_020a941c(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_020a9260(void *arg)
{
    *(void **) arg = (void *) data_020e3de4;
    func_020a941c(arg);
    return arg;
}
