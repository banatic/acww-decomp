/* func_02076ae8 @ 0x02076ae8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *src, char *dst, int len);
extern void func_02044e28(char *src, int param);

void func_02076ae8(int a, int b, int c, unsigned int player)
{
    char buffer[16];
    func_020736bc(data_020ccf94, buffer, 14);
    func_02044e28(buffer, c);
}
