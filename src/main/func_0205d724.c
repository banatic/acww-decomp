/* func_0205d724 @ 0x0205d724, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c7b4(int);
extern void func_0205d5f0(void *);
extern int func_020e9abc(void *);

extern unsigned char data_021c9af4[];
extern unsigned char data_021c9d1c[];

void func_0205d724(int argument0)
{
    void *condition_value0;
    unsigned int *ptr;

    func_0205c7b4((int) argument0);
    func_0205d5f0((void *) data_021c9d1c);
    ptr = (unsigned int *) data_021c9af4;
    if ((condition_value0 = (void *) (*ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}
