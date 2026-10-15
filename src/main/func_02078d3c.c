/* func_02078d3c @ 0x02078d3c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c35c(int);
extern void func_02078cb0(void *ptr);
extern int func_020e9abc(void *);
extern void *data_021c9ac4;
extern char data_021d12dc;

void func_02078d3c(int argument0)
{
    void *condition_value0;
    func_0205c35c((int) argument0);
    func_02078cb0(&data_021d12dc);
    if ((condition_value0 = (void *) (data_021c9ac4))) {
        func_020e9abc(condition_value0);
    }
}
