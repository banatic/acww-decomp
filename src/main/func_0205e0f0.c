/* func_0205e0f0 @ 0x0205e0f0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c5bc(void);
extern void func_0205dfa8(void *ptr);
extern void func_020e9abc(void);

extern unsigned char data_021c9adc[];
extern unsigned char data_021c9e68[];

void func_0205e0f0(void)
{
    unsigned int *ptr;
    unsigned int val;

    func_0205c5bc();
    func_0205dfa8((void *) data_021c9e68);
    ptr = (unsigned int *) data_021c9adc;
    val = *ptr;
    if (val != 0) {
        func_020e9abc();
    }
}
