/* __sinit_020c5ba0 @ 0x020c5ba0, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e930c(void *, int);
extern void __register_global_object(void *, void *, void *);
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021cfb84;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021cfb8c;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021cfb74;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021cfb70;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021cfb78;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021cfb7c;
extern unsigned char data_021cfb80;
extern void func_0206154c(void *);
extern unsigned char data_021cfba0;

void __sinit_020c5ba0(void)
{
    data_021cfb84.f0 = 31;
    data_021cfb84.f1 = 20;
    data_021cfb84.f2 = 20;
    data_021cfb84.f3 = 31;
    data_021cfb8c.f0 = 20;
    data_021cfb8c.f1 = 20;
    data_021cfb8c.f2 = 31;
    data_021cfb8c.f3 = 31;
    data_021cfb74.f0 = 31;
    data_021cfb74.f1 = 31;
    data_021cfb74.f2 = 20;
    data_021cfb74.f3 = 31;
    data_021cfb70.f0 = 20;
    data_021cfb70.f1 = 31;
    data_021cfb70.f2 = 20;
    data_021cfb70.f3 = 31;
    data_021cfb78.f0 = 20;
    data_021cfb78.f1 = 31;
    data_021cfb78.f2 = 31;
    data_021cfb78.f3 = 31;
    data_021cfb7c.f0 = 20;
    data_021cfb7c.f1 = 24;
    data_021cfb7c.f2 = 24;
    data_021cfb7c.f3 = 31;
    func_020e930c((void *) &data_021cfb80, 1);
    __register_global_object((void *) ((void *) &data_021cfb80), (((void *) func_0206154c)),
                             (void *) ((void *) &data_021cfba0));
}
