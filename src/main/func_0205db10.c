/* func_0205db10 @ 0x0205db10, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c704(void);
extern void func_0205d9ec(void *param);
extern void func_020e9abc(void);
// placeholder, not used

extern unsigned char data_021c9aec[];
extern unsigned char data_021c9d7c[];

void func_0205db10(void)
{
    int *ptr;
    func_0205c704();
    func_0205d9ec((void *) data_021c9d7c);
    ptr = (int *) data_021c9aec;
    if (*ptr != 0) {
        func_020e9abc();
    }
}
