/* func_02076bec @ 0x02076bec, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int, void *, int, int);
extern void func_02095558(int, int);

void func_02076bec(int a, int b, int c, int d)
{
    unsigned char buf[8];
    func_020736bc(data_020ccf94, buf, a, d);
    func_02095558(buf[0], d);
}
