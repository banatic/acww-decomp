/* __sinit_020c6e38 @ 0x020c6e38, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203a970(void *);
extern void __register_global_object(void *, void *, void *);
extern void *func_020b7e3c(void *);
extern void func_020b64a0(void *);
extern int func_020b6580(void *);
extern struct {
    long f0;
} data_021f693c;
extern unsigned char data_020e550c;
extern unsigned char data_021f6a6c;
extern void func_0203a9a8(void *);
extern unsigned char data_021f6964;
extern unsigned char data_021f6a14;
extern void *func_020b7e5c(void *);
extern unsigned char data_021f6970;
extern unsigned char data_021f69d0;
extern void func_020b649c(void *);
extern unsigned char data_021f697c;
extern unsigned char data_021f69a0;
extern void func_020b657c(void *);
extern unsigned char data_021f694c;
extern unsigned char data_021f69b8;
extern unsigned char data_021f6958;

void __sinit_020c6e38(void)
{
    data_021f693c.f0 = (long) &data_020e550c;
    func_0203a970((void *) &data_021f6a6c);
    __register_global_object((void *) ((void *) &data_021f6a6c), (((void *) func_0203a9a8)),
                             (void *) ((void *) &data_021f6964));
    func_020b7e3c((void *) &data_021f6a14);
    __register_global_object((void *) ((void *) &data_021f6a14), (((void *) func_020b7e5c)),
                             (void *) ((void *) &data_021f6970));
    func_020b64a0((void *) &data_021f69d0);
    __register_global_object((void *) ((void *) &data_021f69d0), (((void *) func_020b649c)),
                             (void *) ((void *) &data_021f697c));
    func_020b6580((void *) &data_021f69a0);
    __register_global_object((void *) ((void *) &data_021f69a0), (((void *) func_020b657c)),
                             (void *) ((void *) &data_021f694c));
    func_020b6580((void *) &data_021f69b8);
    __register_global_object((void *) ((void *) &data_021f69b8), (((void *) func_020b657c)),
                             (void *) ((void *) &data_021f6958));
}
