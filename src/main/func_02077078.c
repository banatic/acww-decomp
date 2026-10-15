/* func_02077078 @ 0x02077078, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *src, void *dest, int size);
extern void func_02052a3c(int a, void *b);

void func_02077078(int a1, int a2, int a3, unsigned int player)
{
    int buf;
    func_020736bc(data_020ccf94, &buf, 4);
    func_02052a3c(a3, &buf);
}
