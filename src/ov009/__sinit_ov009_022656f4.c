/* __sinit_ov009_022656f4 @ 0x022656f4, 0x94 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void __register_global_object(void *object, void *destructor, void *node);
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_ov009_02265b3c;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_ov009_02265b20;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_ov009_02265b34;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_ov009_02265b30;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_ov009_02265b40;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_ov009_02265b38;
extern unsigned char data_ov009_02265cb4;
extern void func_ov009_02265634(void *element);
extern void func_ov009_02265630(void *element);
extern void func_ov009_0226569c(void);
extern unsigned char data_ov009_02265b48;

#define DestroyGlobal_ov009_0226569c ((void *) &func_ov009_0226569c)

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov009_022656f4(void)
{
    data_ov009_02265b3c.f0 = 31;
    data_ov009_02265b3c.f1 = 20;
    data_ov009_02265b3c.f2 = 20;
    data_ov009_02265b3c.f3 = 31;
    data_ov009_02265b20.f0 = 20;
    data_ov009_02265b20.f1 = 20;
    data_ov009_02265b20.f2 = 31;
    data_ov009_02265b20.f3 = 31;
    data_ov009_02265b34.f0 = 31;
    data_ov009_02265b34.f1 = 31;
    data_ov009_02265b34.f2 = 20;
    data_ov009_02265b34.f3 = 31;
    data_ov009_02265b30.f0 = 20;
    data_ov009_02265b30.f1 = 31;
    data_ov009_02265b30.f2 = 20;
    data_ov009_02265b30.f3 = 31;
    data_ov009_02265b40.f0 = 20;
    data_ov009_02265b40.f1 = 31;
    data_ov009_02265b40.f2 = 31;
    data_ov009_02265b40.f3 = 31;
    data_ov009_02265b38.f0 = 20;
    data_ov009_02265b38.f1 = 24;
    data_ov009_02265b38.f2 = 24;
    data_ov009_02265b38.f3 = 31;
    __cxa_vec_ctor((void *) &data_ov009_02265cb4, 34, 80, (void *) &func_ov009_02265634, (void *) &func_ov009_02265630);
    __register_global_object(0, DestroyGlobal_ov009_0226569c, (void *) &data_ov009_02265b48);
}

#undef DestroyGlobal_ov009_0226569c

#pragma section INIT end
