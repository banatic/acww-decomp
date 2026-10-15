/* func_02076168 @ 0x02076168, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736ec(int value, unsigned long);
extern int data_020ccf94;
extern void (*data_020cd0dc[])(int, int, unsigned char, unsigned int);

void func_02076168(int index, int unused, int a, int b, unsigned char c, unsigned int d)
{
    func_020736ec(data_020ccf94, unused);
    data_020cd0dc[index](a, b, c, d);
}
