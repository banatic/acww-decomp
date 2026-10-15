/* __sinit_ov004_0224f164 @ 0x0224f164, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void __register_global_object(int, void *destructor, void *);
extern unsigned char data_ov004_02259a34;
extern void *func_ov004_0223ed30(char *arg0);
extern void *func_ov004_0223ecc8(char *arg0);
extern int func_ov004_0224519c(char *arg0);
extern unsigned char data_ov004_02259a28;

void __sinit_ov004_0224f164(void)
{
    __cxa_vec_ctor((void *) &data_ov004_02259a34, 32, 728, ((void (*)(void *)) func_ov004_0223ed30),
                   ((void (*)(void *)) func_ov004_0223ecc8));
    __register_global_object(0, ((void *) &func_ov004_0224519c), (void *) &data_ov004_02259a28);
}
