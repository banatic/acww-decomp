/* __sinit_020c6de0 @ 0x020c6de0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02031ec0(void *);
extern void __register_global_object(void *, void *, void *);
extern struct {
    long f0;
} data_021f4b3c;
extern unsigned char data_ov003_0223a248;
extern void *func_020b3fe4(void *);
extern unsigned char data_021f4b70;

void __sinit_020c6de0(void)
{
    func_02031ec0((void *) &data_021f4b3c);
    data_021f4b3c.f0 = (long) &data_ov003_0223a248;
    __register_global_object((void *) ((void *) &data_021f4b3c), (((void *) func_020b3fe4)),
                             (void *) ((void *) &data_021f4b70));
}
