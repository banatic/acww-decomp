/* func_020770e0 @ 0x020770e0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int, char *, int);
extern void func_0203f4ec(char *, int);

void func_020770e0(int length, int sequence, unsigned char category, unsigned int player)
{
    char buf[8];
    func_020736bc(data_020ccf94, buf, length);
    func_0203f4ec(buf, player);
}
