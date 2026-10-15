/* func_0205d234 @ 0x0205d234, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c6b0(int);
extern void func_0205d12c(void *);
extern int func_020e9abc(void *);

extern int data_021c9ae8;
extern unsigned char data_021c9c2c[];

void func_0205d234(int argument0)
{
    void *condition_value0;
    func_0205c6b0((int) argument0);
    func_0205d12c((void *) data_021c9c2c);
    if ((condition_value0 = (void *) (data_021c9ae8))) {
        func_020e9abc(condition_value0);
    }
}
