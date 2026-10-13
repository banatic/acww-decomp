/* func_02076a78 @ 0x02076a78, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(void *src, void *dst, int size);
extern int func_0209d484(void *src, int param);
extern void *data_020ccf94;

int func_02076a78(int unused1, int unused2, int unused3, int d)
{
    char buf[8];
    func_020736bc(data_020ccf94, buf, 1);
    return func_0209d484(buf, d);
}
