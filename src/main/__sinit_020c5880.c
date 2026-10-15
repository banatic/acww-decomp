/* __sinit_020c5880 @ 0x020c5880, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205da78(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021c9d7c;
extern void func_0205da74(void *);
extern unsigned char data_021c9d5c;

void __sinit_020c5880(void)
{
    func_0205da78((void *) &data_021c9d7c);
    __register_global_object((void *) ((void *) &data_021c9d7c), (((void *) func_0205da74)),
                             (void *) ((void *) &data_021c9d5c));
}
