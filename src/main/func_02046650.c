/* func_02046650 @ 0x02046650, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern void func_02042c40(void *receiver);
extern void func_020481a0(int);
extern int data_020ccf94;

extern unsigned char data_021c779c[];
extern unsigned char data_021c7c48[];

void func_02046650(void)
{
    int result;

    result = func_02073d90(data_020ccf94);
    if (result) {
        return;
    }
    func_02042c40(data_021c7c48);
    func_020481a0((unsigned int) data_021c779c);
}
