/* func_02076a78 @ 0x02076a78, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(void *src, void *dst, int size);
extern void func_0209d484(void *src, int param);
extern void *data_020ccf94;

void func_02076a78(int length, int sequence, unsigned char category, unsigned int player)
{
    char buf[8];
    func_020736bc(data_020ccf94, buf, 1);
    func_0209d484(buf, player);
}
