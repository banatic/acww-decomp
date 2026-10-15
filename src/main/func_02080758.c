/* func_02080758 @ 0x02080758, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d1240;
extern int data_021d12f0;
extern int data_021d125c;
extern void *func_0209529c(int *);
extern void func_02095238(int *);
extern int func_0209526c(void *);
extern __arm void __register_global_object(void *, void *, void *);
extern int func_020807dc(int, int *);

int func_02080758(int arg)
{
    if ((data_021d1240 & 1) == 0) {
        func_0209529c(&data_021d12f0);
        __register_global_object((void *) (&data_021d12f0), (((void *) func_0209526c)), (void *) (&data_021d125c));
        data_021d1240 |= 1;
    }
    func_02095238(&data_021d12f0);
    return func_020807dc(arg, &data_021d12f0);
}
