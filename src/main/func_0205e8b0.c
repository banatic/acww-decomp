/* func_0205e8b0 @ 0x0205e8b0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c65c(void);
extern void func_0205e5ec(void *arg);
extern int data_021c9f5c;
extern int data_021c9ae4;
extern void func_020e9abc(void);

void func_0205e8b0(void)
{
    func_0205c65c();
    func_0205e5ec(&data_021c9f5c);
    if (data_021c9ae4 != 0) {
        func_020e9abc();
    }
}
