/* xct_exchange_talk_3: 3 functions, module ov055
 * mwccarm 1.2/base -O4,s
 * func_ov055_02260a58 @ 0x02260a58, 0x18 bytes, Thumb
 * func_ov055_02260a40 @ 0x02260a40, 0x18 bytes, Thumb
 * func_ov055_02260a20 @ 0x02260a20, 0x20 bytes, Thumb
 */

struct UnkStruct_02260a58 {
    void *vtable;
};

extern void *func_0202eb70(void *obj);
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *self);
extern unsigned char data_ov055_02260f44[];

struct UnkStruct_02260a58 *func_ov055_02260a58(struct UnkStruct_02260a58 *self)
{
    func_0202eb70(self);
    self->vtable = ((char *) data_ov055_02260f44);
    return self;
}

void *func_ov055_02260a40(void *arg)
{
    void *p = ((char *) data_ov055_02260f44);
    *(void **) arg = p;
    func_0202eb20(arg);
    return arg;
}

void *func_ov055_02260a20(void *self)
{
    *(void **) self = (void *) data_ov055_02260f44;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
