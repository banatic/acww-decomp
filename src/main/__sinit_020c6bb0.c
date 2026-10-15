/* __sinit_020c6bb0 @ 0x020c6bb0, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __register_global_object(void *, void *, void *);
extern void *func_020a91f0(void *);
extern void *func_020a8d90(void *);
extern void *func_020a7d68(void *);
extern struct {
    unsigned char f0;
} data_021f43ec;
extern struct {
    unsigned char f0;
} data_021f43f8;
extern struct {
    unsigned char f0;
} data_021f43e8;
extern void func_020088f8(void *);
extern unsigned char data_021f4410;
extern unsigned char data_021f4434;
extern unsigned char data_021f441c;
extern unsigned char data_021f44dc;
extern void *func_020a91d8(void *);
extern unsigned char data_021f4440;
extern unsigned char data_021f450c;
extern void *func_020a8d78(void *);
extern unsigned char data_021f444c;
extern unsigned char data_021f4548;
extern void *func_020a7d48(void *);
extern unsigned char data_021f4404;

void __sinit_020c6bb0(void)
{
    data_021f43ec.f0 = 255;
    __register_global_object((void *) ((void *) &data_021f43ec), (((void *) func_020088f8)),
                             (void *) ((void *) &data_021f4410));
    data_021f43f8.f0 = 255;
    __register_global_object((void *) ((void *) &data_021f43f8), (((void *) func_020088f8)),
                             (void *) ((void *) &data_021f4434));
    data_021f43e8.f0 = 254;
    __register_global_object((void *) ((void *) &data_021f43e8), (((void *) func_020088f8)),
                             (void *) ((void *) &data_021f441c));
    func_020a91f0((void *) &data_021f44dc);
    __register_global_object((void *) ((void *) &data_021f44dc), (((void *) func_020a91d8)),
                             (void *) ((void *) &data_021f4440));
    func_020a8d90((void *) &data_021f450c);
    __register_global_object((void *) ((void *) &data_021f450c), (((void *) func_020a8d78)),
                             (void *) ((void *) &data_021f444c));
    func_020a7d68((void *) &data_021f4548);
    __register_global_object((void *) ((void *) &data_021f4548), (((void *) func_020a7d48)),
                             (void *) ((void *) &data_021f4404));
}
