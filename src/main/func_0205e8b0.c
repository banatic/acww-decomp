/* func_0205e8b0 @ 0x0205e8b0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c65c(int);
extern void func_0205e5ec(void *arg);
extern int data_021c9f5c;
extern int data_021c9ae4;
extern int func_020e9abc(void *);

void func_0205e8b0(int argument0)
{
    void *condition_value0;
    func_0205c65c((int) argument0);
    func_0205e5ec(&data_021c9f5c);
    if ((condition_value0 = (void *) (data_021c9ae4)) != 0) {
        func_020e9abc(condition_value0);
    }
}
