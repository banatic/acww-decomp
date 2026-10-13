/* __sinit_020c62a4 @ 0x020c62a4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208b5ec(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021d3258;
extern int func_0208b5b0;
extern int data_021d3164;

void __sinit_020c62a4(void)
{
    func_0208b5ec((void *) &data_021d3258);
    __register_global_object((void *) &data_021d3258, (void *) &func_0208b5b0, (void *) &data_021d3164);
}
