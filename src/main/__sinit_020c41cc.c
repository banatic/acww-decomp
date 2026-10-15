/* __sinit_020c41cc @ 0x020c41cc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003164(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_0213ff20;
extern void *func_0200314c(void *);
extern unsigned char data_0213ff14;

void __sinit_020c41cc(void)
{
    func_02003164((void *) &data_0213ff20);
    __register_global_object((void *) ((void *) &data_0213ff20), (((void *) func_0200314c)),
                             (void *) ((void *) &data_0213ff14));
}
