/* func_02076f04 @ 0x02076f04, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *obj, int *out, int a);
extern void func_020ad7f4(int *data, int d);

void func_02076f04(int length, int sequence, unsigned char category, unsigned int player)
{
    int buf;
    func_020736bc(data_020ccf94, &buf, length);
    func_020ad7f4(&buf, player);
}
