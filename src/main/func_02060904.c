/* func_02060904 @ 0x02060904, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328(void *a, void *b, void *c);
extern char data_021cad1c;
extern char data_020dd814;

void *func_02060904(void *arg)
{
    func_02064328(&data_021cad1c, &data_020dd814, arg);
    return &data_021cad1c;
}
