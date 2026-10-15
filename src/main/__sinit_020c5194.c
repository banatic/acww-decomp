/* __sinit_020c5194 @ 0x020c5194, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __register_global_object(void *, void *, void *);
extern struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char _p2[2];
    unsigned char f4;
} data_021c75a0;
extern void func_020413f4(void *);
extern unsigned char data_021c7594;

void __sinit_020c5194(void)
{
    data_021c75a0.f0 = 0;
    data_021c75a0.f4 = 0;
    data_021c75a0.f1 = 0;
    __register_global_object((void *) ((void *) &data_021c75a0), (((void *) func_020413f4)),
                             (void *) ((void *) &data_021c7594));
}
