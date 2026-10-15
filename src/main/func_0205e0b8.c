/* func_0205e0b8 @ 0x0205e0b8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(void *, void *, unsigned int, unsigned int);
extern char data_021c9e54[];
extern char data_020dd718[];

void *func_0205e0b8(unsigned int param)
{
    func_02064328(data_021c9e54, data_020dd718, param >> 5, param);
    return data_021c9e54;
}
