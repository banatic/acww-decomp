/* func_02077078 @ 0x02077078, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_020736bc(void *src, void *dest, int size);
extern int func_02052a3c(int a, void *b);

int func_02077078(int a1, int a2, int a3)
{
    int buf;
    func_020736bc(data_020ccf94, &buf, 4);
    return func_02052a3c(a3, &buf);
}
