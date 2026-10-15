/* __sinit_020c4bdc @ 0x020c4bdc, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020348c8(void *);
extern void __register_global_object(void *, void *, void *);
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021c513c;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021c5134;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021c5138;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021c5150;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021c514c;
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char f2;
    unsigned char f3;
} data_021c5148;
extern unsigned char data_021c5160;
extern void func_020348c4(void *);
extern unsigned char data_021c5154;

void __sinit_020c4bdc(void)
{
    data_021c513c.f0 = 31;
    data_021c513c.f1 = 20;
    data_021c513c.f2 = 20;
    data_021c513c.f3 = 31;
    data_021c5134.f0 = 20;
    data_021c5134.f1 = 20;
    data_021c5134.f2 = 31;
    data_021c5134.f3 = 31;
    data_021c5138.f0 = 31;
    data_021c5138.f1 = 31;
    data_021c5138.f2 = 20;
    data_021c5138.f3 = 31;
    data_021c5150.f0 = 20;
    data_021c5150.f1 = 31;
    data_021c5150.f2 = 20;
    data_021c5150.f3 = 31;
    data_021c514c.f0 = 20;
    data_021c514c.f1 = 31;
    data_021c514c.f2 = 31;
    data_021c514c.f3 = 31;
    data_021c5148.f0 = 20;
    data_021c5148.f1 = 24;
    data_021c5148.f2 = 24;
    data_021c5148.f3 = 31;
    func_020348c8((void *) &data_021c5160);
    __register_global_object((void *) ((void *) &data_021c5160), (((void *) func_020348c4)),
                             (void *) ((void *) &data_021c5154));
}
