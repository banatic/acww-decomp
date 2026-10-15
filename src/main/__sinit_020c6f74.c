/* __sinit_020c6f74 @ 0x020c6f74, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020bb99c(void *);
extern void __register_global_object(void *, void *, void *);
extern void *func_020b18ac(void *);
extern void *func_020be400(void *);

extern int data_021f75b0;
extern void func_020bb998(void *);
extern int data_021f6d20;
extern int data_021f7280;
extern void func_020b18a8(void *);
extern int data_021f6d14;
extern int data_021f8b48;
extern void *func_020c1574(void *);
extern int data_021f6d08;
extern int data_020ca0ec;
extern int data_021f6cdc;

void __sinit_020c6f74(void)
{
    func_020bb99c((void *) &data_021f75b0);
    __register_global_object((void *) ((void *) &data_021f75b0), (((void *) func_020bb998)),
                             (void *) ((void *) &data_021f6d20));
    func_020b18ac((void *) &data_021f7280);
    __register_global_object((void *) ((void *) &data_021f7280), (((void *) func_020b18a8)),
                             (void *) ((void *) &data_021f6d14));
    func_020be400((void *) &data_021f8b48);
    __register_global_object((void *) ((void *) &data_021f8b48), (((void *) func_020c1574)),
                             (void *) ((void *) &data_021f6d08));
    data_021f6cdc = 6 * data_020ca0ec;
}
