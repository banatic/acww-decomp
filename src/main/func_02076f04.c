/* func_02076f04 @ 0x02076f04, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_020736bc(void *obj, int *out, int a, int d);
extern int func_020ad7f4(int *data, int d);

int func_02076f04(int a, int b, int c, int d)
{
    int buf;
    func_020736bc(data_020ccf94, &buf, a, d);
    return func_020ad7f4(&buf, d);
}
