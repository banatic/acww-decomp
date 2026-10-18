/* __sinit_020c648c @ 0x020c648c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d8a0(void *);
extern void __register_global_object(void *, void *, void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_0209d8fc(void *);
extern unsigned char data_021dc6e8;
extern void func_0209d89c(void *);
extern unsigned char data_021dc6dc;
extern unsigned char data_021dc70c;
extern void *func_0209d9c4(void *);
extern void func_0209d934(void *);
extern void *func_0209d9a8(void *);
extern unsigned char data_021dc6d0;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c648c(void)
{
    func_0209d8a0((void *) &data_021dc6e8);
    __register_global_object((void *) ((void *) &data_021dc6e8), (((void *) func_0209d89c)),
                             (void *) ((void *) &data_021dc6dc));
    __cxa_vec_ctor((void *) ((void *) &data_021dc70c), 51, 1, (((void (*)(void *)) func_0209d9c4)),
                   (void (*)(void *)) func_0209d934);
    func_0209d8fc((void *) &data_021dc70c);
    __register_global_object((void *) ((void *) &data_021dc70c), (((void *) func_0209d9a8)),
                             (void *) ((void *) &data_021dc6d0));
}

#pragma section INIT end
