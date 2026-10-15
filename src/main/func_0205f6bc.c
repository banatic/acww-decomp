/* func_0205f6bc @ 0x0205f6bc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021ca120;
extern char data_020dd798;
extern int func_02064328(void *a, void *b, unsigned int c, unsigned int d);

void *func_0205f6bc(unsigned int p)
{
    func_02064328(&data_021ca120, &data_020dd798, p >> 5, p);
    return &data_021ca120;
}
