/* mabel_talk_6: 3 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_022620e8 @ 0x022620e8, 0x18 bytes, Thumb
 * func_ov049_022620d0 @ 0x022620d0, 0x18 bytes, Thumb
 * func_ov049_022620b0 @ 0x022620b0, 0x20 bytes, Thumb
 */

typedef struct {
    void *vtable;
} UnkStruct_022620d0;

struct UnkStruct_022620b0 {
    void *unk_00;
};

extern void *func_0202eb70(void *);
extern unsigned char data_ov049_022634b4[];
extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *);

void *func_ov049_022620e8(void *self)
{
    func_0202eb70(self);
    *(void **) self = (void *) data_ov049_022634b4;
    return self;
}

UnkStruct_022620d0 *func_ov049_022620d0(UnkStruct_022620d0 *self)
{
    self->vtable = ((char *) data_ov049_022634b4);
    func_0202eb20(self);
    return self;
}

void *func_ov049_022620b0(struct UnkStruct_022620b0 *self)
{
    self->unk_00 = (void *) data_ov049_022634b4;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
