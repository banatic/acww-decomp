/* func_02076fe0 @ 0x02076fe0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int, void *, int);
extern void func_020528fc(void *, int);

void func_02076fe0(int a1, int a2, int a3, int a4)
{
    char buf[8];
    func_020736bc(data_020ccf94, buf, 3);
    func_020528fc(buf, a4);
}
