/* __sinit_020c6ca4 @ 0x020c6ca4, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ad1dc(void *);
extern void __register_global_object(void *, void *, void *);
extern int data_021f4904;
extern void func_020ad1d8(void *);
extern int data_021f47f4;
extern int data_021f4938;
extern int data_021f480c;
extern int data_021f496c;
extern int data_021f4830;
extern int data_021f489c;
extern int data_021f483c;
extern int data_021f48d0;
extern int data_021f47dc;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c6ca4(void)
{
    func_020ad1dc((void *) &data_021f4904);
    __register_global_object((void *) ((void *) &data_021f4904), (((void *) func_020ad1d8)),
                             (void *) ((void *) &data_021f47f4));
    func_020ad1dc((void *) &data_021f4938);
    __register_global_object((void *) ((void *) &data_021f4938), (((void *) func_020ad1d8)),
                             (void *) ((void *) &data_021f480c));
    func_020ad1dc((void *) &data_021f496c);
    __register_global_object((void *) ((void *) &data_021f496c), (((void *) func_020ad1d8)),
                             (void *) ((void *) &data_021f4830));
    func_020ad1dc((void *) &data_021f489c);
    __register_global_object((void *) ((void *) &data_021f489c), (((void *) func_020ad1d8)),
                             (void *) ((void *) &data_021f483c));
    func_020ad1dc((void *) &data_021f48d0);
    __register_global_object((void *) ((void *) &data_021f48d0), (((void *) func_020ad1d8)),
                             (void *) ((void *) &data_021f47dc));
}

#pragma section INIT end
