/* func_02076d40 @ 0x02076d40, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *ptr, void *buf, int a, int d);
extern void func_02050884(void *buf, int d);

void func_02076d40(int a, int b, int c, int d)
{
    char buffer[8];
    func_020736bc(data_020ccf94, buffer, a, d);
    func_02050884(buffer, d);
}
