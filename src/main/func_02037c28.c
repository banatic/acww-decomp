/* func_02037c28 @ 0x02037c28, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(int arg);
extern int data_021c590c;

int func_02037c28(void)
{
    func_020e9898(data_021c590c);
    data_021c590c = 0;
    return 1;
}
