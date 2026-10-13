/* __sinit_020c6464 @ 0x020c6464, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d084(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021dc5b0;
extern void func_0209d080(void);
extern unsigned char data_021dc5b4;

void __sinit_020c6464(void)
{
    func_0209d084((void *) &data_021dc5b0);
    __register_global_object((void *) &data_021dc5b0, (void *) &func_0209d080, (void *) &data_021dc5b4);
}
