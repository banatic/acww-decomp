/* func_020b95f4 @ 0x020b95f4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f6c70;
extern unsigned int data_021f6c94;
extern void OS_Terminate(void);

unsigned int func_020b95f4(unsigned int size)
{
    unsigned int old = data_021f6c70;
    unsigned int aligned = (size + 0xF) & 0xFFF0;
    unsigned int new = old + aligned;

    data_021f6c70 = new;
    if (new >= data_021f6c94) {
        data_021f6c70 = old;
        OS_Terminate();
        return 0;
    } else {
        return old;
    }
}
