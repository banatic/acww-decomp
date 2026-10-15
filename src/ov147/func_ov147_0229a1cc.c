/* func_ov147_0229a1cc @ 0x0229a1cc, 0x34 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov147_0229a6e4(void *);
extern void *func_ov147_02299ad0(void *);
extern void func_020ee62c(void *);

typedef struct {
    void *vtable;
    char pad_04[0x50];
    char sub_54[0x5C];
    char sub_B0[1];
} my_struct;

extern unsigned char data_020da13c[];
extern unsigned char data_ov147_0229aa28[];

void *func_ov147_0229a1cc(void *arg)
{
    my_struct *self = (my_struct *) arg;

    self->vtable = (void *) data_ov147_0229aa28;
    func_ov147_0229a6e4(&self->sub_B0);
    func_ov147_02299ad0(&self->sub_54);
    self->vtable = (void *) data_020da13c;
    func_020ee62c(self);
    return self;
}
