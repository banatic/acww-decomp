/* func_02078b84 @ 0x02078b84, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c2a0(int);
extern void func_02078b2c(void *);
extern int func_020e9abc(void *);

extern unsigned char data_021c9abc[];
extern unsigned char data_021d12a4[];

void func_02078b84(int argument0)
{
    void *ptr;
    void *ptr2;

    func_0205c2a0((int) argument0);
    func_02078b2c((void *) data_021d12a4);
    ptr = (void *) data_021c9abc;
    ptr2 = *(void **) ptr;
    if (ptr2 != 0) {
        func_020e9abc(ptr2);
    }
}
