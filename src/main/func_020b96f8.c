/* func_020b96f8 @ 0x020b96f8, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f6c90;
extern unsigned int data_021f6c80;
extern unsigned int data_021f6c8c;
extern unsigned int data_021f6c7c;
extern unsigned int data_021f6c84;
extern unsigned int data_021f6c74;
extern unsigned int data_021f6c88;
extern unsigned int data_021f6c78;
extern void func_020b9478(void);
extern void OS_Terminate(void);

void func_020b96f8(unsigned int *out1, unsigned int *out2, unsigned int size)
{
    if (data_021f6c90 + size <= data_021f6c80 && data_021f6c8c + (size >> 1) <= data_021f6c7c) {
        *out1 = data_021f6c90;
        *out2 = data_021f6c8c;
        data_021f6c90 += size;
        data_021f6c8c += (size >> 1);
    } else if (data_021f6c84 + size <= data_021f6c74 && data_021f6c84 + size <= 0x60000 &&
               data_021f6c88 + (size >> 1) <= data_021f6c78) {
        *out1 = data_021f6c84;
        *out2 = data_021f6c88;
        data_021f6c84 += size;
        data_021f6c88 += (size >> 1);
    } else {
        func_020b9478();
        OS_Terminate();
        *out1 = 0;
        *out2 = 0x20000;
    }
}
