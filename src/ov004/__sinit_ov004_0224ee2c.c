/* __sinit_ov004_0224ee2c @ 0x0224ee2c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void __register_global_object(void *, void *destructor, void *);
extern unsigned char data_ov004_02258af4;
extern void *func_ov004_02234008(char *arg0);
extern void *func_ov004_02233ff4(char *arg0);
extern void *func_ov004_02233fd8(char *arg0);
extern unsigned char data_ov004_02258ae8;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov004_0224ee2c(void)
{
    __cxa_vec_ctor((void *) &data_ov004_02258af4, 15, 148, ((void (*)(void *)) func_ov004_02234008),
                   ((void (*)(void *)) func_ov004_02233ff4));
    __register_global_object((void *) &data_ov004_02258af4, ((void *) &func_ov004_02233fd8), (void *) &data_ov004_02258ae8);
}

#pragma section INIT end
