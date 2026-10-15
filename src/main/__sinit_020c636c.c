/* __sinit_020c636c @ 0x020c636c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020962f8(void *);
extern void __register_global_object(void *, void *, void *);
extern unsigned char data_021d5684;
extern void *func_020962dc(void *);
extern unsigned char data_021d5678;

void __sinit_020c636c(void)
{
    func_020962f8((void *) &data_021d5684);
    __register_global_object((void *) ((void *) &data_021d5684), (((void *) func_020962dc)),
                             (void *) ((void *) &data_021d5678));
}
