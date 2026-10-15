/* func_0205f820 @ 0x0205f820, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c4a4(int);
extern void func_0205f7bc(int);
extern int func_020e9abc(void *);

extern unsigned char data_021c9ad0[];

extern unsigned char data_021cacd0[];

void func_0205f820(int argument0)
{
    void *condition_value0;
    int *ptr;

    func_0205c4a4((int) argument0);
    func_0205f7bc((unsigned int) data_021cacd0);
    ptr = (int *) data_021c9ad0;
    if ((condition_value0 = (void *) (*ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}
