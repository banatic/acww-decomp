/* func_0205e0f0 @ 0x0205e0f0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c5bc(int);
extern void func_0205dfa8(void *ptr);
extern int func_020e9abc(void *);

extern unsigned char data_021c9adc[];
extern unsigned char data_021c9e68[];

void func_0205e0f0(unsigned int val)
{
    unsigned int *ptr;

    func_0205c5bc(val);
    func_0205dfa8((void *) data_021c9e68);
    ptr = (unsigned int *) data_021c9adc;
    val = *ptr;
    if (val != 0) {
        func_020e9abc((void *) val);
    }
}
