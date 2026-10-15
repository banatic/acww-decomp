/* func_0206923c @ 0x0206923c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    union {
        void *ptr1;
        void *ptr2;
    } u;
    char pad_04[0x20];
    int unk_24;
    int unk_28;
    char sub;
} UnkStruct_0206923c;

extern void *func_020a9484(void *p);
extern void func_020a8754(void *p);

extern unsigned char data_020defc0[];
extern unsigned char data_020e3e68[];

void *func_0206923c(UnkStruct_0206923c *self, int arg)
{
    func_020a9484(self);
    self->u.ptr1 = (void *) data_020e3e68;
    self->u.ptr2 = (void *) data_020defc0;
    self->unk_24 = arg;
    self->unk_28 = 0;
    func_020a8754((void *) &self->sub);
    return self;
}
