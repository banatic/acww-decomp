/* func_02077050 @ 0x02077050, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *src, void *dst, int size);
extern void func_02052ac8(int a, void *b);

void func_02077050(int param1, int param2, int param3, unsigned int player)
{
    char buffer[4];
    func_020736bc(data_020ccf94, buffer, 4);
    func_02052ac8(param3, buffer);
}
