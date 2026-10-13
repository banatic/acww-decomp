/* func_020ad1f4 @ 0x020ad1f4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_01ffd070(void *buffer, int param, void *s);
extern void func_020aced0(const char *src, char *dest);
extern const char data_021f48d0[];

void func_020ad1f4(int param)
{
    int s[3];
    char buffer[16];
    s[0] = 0x166;
    s[1] = 0;
    s[2] = 0xc80;
    func_01ffd070(buffer, param, s);
    func_020aced0(data_021f48d0, buffer);
}
