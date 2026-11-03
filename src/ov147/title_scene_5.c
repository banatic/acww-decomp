/* title_scene_5: 4 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_0229a238 @ 0x0229a238, 0x18 bytes, Thumb
 * func_ov147_0229a200 @ 0x0229a200, 0x38 bytes, Thumb
 * func_ov147_0229a1cc @ 0x0229a1cc, 0x34 bytes, Thumb
 * func_ov147_0229a194 @ 0x0229a194, 0x38 bytes, Thumb
 */

typedef struct {
    void *vtable;
    char pad_04[0x50];
    char sub_54[0x5C];
    char sub_B0[1];
} my_struct;

extern int func_020edf70(int);
extern void *func_020ee660(void *);
extern void *func_ov147_02299ae8(void *);
extern void func_ov147_0229a6f0(void *);
extern void *func_020b9cfc(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_ov147_0229aa28[];
extern void func_ov147_0229a6e4(void *);
extern void *func_ov147_02299ad0(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

void *func_ov147_0229a200(void *this);

void func_ov147_0229a238(void)
{
    void *condition_value_30;
    condition_value_30 = (void *) (func_020edf70(0xf8));
    if (condition_value_30 != 0) {
        func_ov147_0229a200(condition_value_30);
    }
}

void *func_ov147_0229a200(void *this)
{
    func_020ee660(this);
    *(unsigned int *) this = (unsigned int) data_020da13c;
    *(unsigned int *) this = (unsigned int) data_ov147_0229aa28;
    func_ov147_02299ae8((char *) this + 0x54);
    func_ov147_0229a6f0((char *) this + 0xb0);
    func_020b9cfc((char *) this + 0xd0);
    return this;
}

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

void *func_ov147_0229a194(void *p)
{
    *(void **) p = (void *) data_ov147_0229aa28;
    func_ov147_0229a6e4((char *) p + 0xb0);
    func_ov147_02299ad0((char *) p + 0x54);
    *(void **) p = (void *) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
