/* func_0205db10 @ 0x0205db10, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c704(int);
extern void func_0205d9ec(void *param);
extern int func_020e9abc(void *);
// placeholder, not used

extern unsigned char data_021c9aec[];
extern unsigned char data_021c9d7c[];

void func_0205db10(int argument0)
{
    void *condition_value0;
    int *ptr;
    func_0205c704((int) argument0);
    func_0205d9ec((void *) data_021c9d7c);
    ptr = (int *) data_021c9aec;
    if ((condition_value0 = (void *) (*ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}
