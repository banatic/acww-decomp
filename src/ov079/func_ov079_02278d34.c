/* func_ov079_02278d34 @ 0x02278d34, 0x24 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
    char pad_04[0xC0];
    unsigned short flag;
} UnkStruct_02278d34;

extern void func_0202eb70(void *);

extern unsigned char data_ov079_0227a074[];

void *func_ov079_02278d34(UnkStruct_02278d34 *self)
{
    func_0202eb70(self);
    self->vtable = (void *) data_ov079_0227a074;
    self->flag = 0xfff1;
    return self;
}
