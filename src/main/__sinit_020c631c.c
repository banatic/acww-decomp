/* __sinit_020c631c @ 0x020c631c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208fe80(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021d369c;
extern int func_0208fe5c;
extern int data_021d3690;

void __sinit_020c631c(void)
{
    func_0208fe80((void *) &data_021d369c);
    __register_global_object((void *) &data_021d369c, (void *) &func_0208fe5c, (void *) &data_021d3690);
}
