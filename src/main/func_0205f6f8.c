/* func_0205f6f8 @ 0x0205f6f8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c560(int);
extern void func_0205f434(int *);
extern unsigned int func_0205c440(int);
extern void func_0205f3b4(int *);
extern int func_020e9abc(void *);
extern int data_021ca16c;
extern int data_021c9ad8;
extern int data_021c9acc;

void func_0205f6f8(int arg)
{
    void *condition_value0;
    void *condition_value1;
    func_0205c560(arg);
    func_0205f434(&data_021ca16c);
    if ((condition_value0 = (void *) (data_021c9ad8))) {
        func_020e9abc(condition_value0);
    }
    func_0205c440(arg);
    func_0205f3b4(&data_021ca16c);
    if ((condition_value1 = (void *) (data_021c9acc))) {
        func_020e9abc(condition_value1);
    }
}
