/* __sinit_020c4204 @ 0x020c4204, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003dac(void *);
extern void __register_global_object(void *, void *, void *);
extern void *func_02003b78(void *);
extern unsigned char data_0213ff98;
extern void func_02003da8(void *);
extern unsigned char data_0213ff8c;
extern unsigned char data_0213ffb0;
extern void *func_02003b50(void *);
extern unsigned char data_0213ff80;

void __sinit_020c4204(void)
{
    func_02003dac((void *) &data_0213ff98);
    __register_global_object((void *) ((void *) &data_0213ff98), (((void *) func_02003da8)),
                             (void *) ((void *) &data_0213ff8c));
    func_02003b78((void *) &data_0213ffb0);
    __register_global_object((void *) ((void *) &data_0213ffb0), (((void *) func_02003b50)),
                             (void *) ((void *) &data_0213ff80));
}
