/* __sinit_020c5b40 @ 0x020c5b40, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206daf8(void *);
extern void __register_global_object(void *, void *, void *);
extern void *func_0206da98(void *);
extern void *func_0206da38(void *);
extern int data_021cd8c4;
extern void *func_0206dae0(void *);
extern int data_021cd8a0;
extern int data_021cd9b0;
extern void *func_0206da80(void *);
extern int data_021cd8b8;
extern int data_021cd8ec;
extern void *func_0206da20(void *);
extern int data_021cd894;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c5b40(void)
{
    func_0206daf8((void *) &data_021cd8c4);
    __register_global_object((void *) ((void *) &data_021cd8c4), (((void *) func_0206dae0)),
                             (void *) ((void *) &data_021cd8a0));
    func_0206da98((void *) &data_021cd9b0);
    __register_global_object((void *) ((void *) &data_021cd9b0), (((void *) func_0206da80)),
                             (void *) ((void *) &data_021cd8b8));
    func_0206da38((void *) &data_021cd8ec);
    __register_global_object((void *) ((void *) &data_021cd8ec), (((void *) func_0206da20)),
                             (void *) ((void *) &data_021cd894));
}

#pragma section INIT end
