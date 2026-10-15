/* func_0205dc58 @ 0x0205dc58, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c4fc(int);
extern void func_0205dbb8(void *ptr);
extern int func_020e9abc(void *);

extern unsigned char data_021c9ad4[];
extern unsigned char data_021c9df4[];

void func_0205dc58(int argument0)
{
    void *condition_value0;
    void *ptr;
    int *global_ptr;

    func_0205c4fc((int) argument0);
    func_0205dbb8((void *) data_021c9df4);
    global_ptr = (int *) data_021c9ad4;
    if ((condition_value0 = (void *) (*global_ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}
