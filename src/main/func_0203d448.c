/* func_0203d448 @ 0x0203d448, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203d300(void *ptr);
extern void func_0203d2f4(void *ptr);
extern void func_0203d238(void *ptr);
extern char data_021c6998[];

void func_0203d448(int param)
{
    if (param == 1) {
        func_0203d300(data_021c6998);
    } else {
        func_0203d2f4(data_021c6998);
    }

    func_0203d238(data_021c6998);
}
