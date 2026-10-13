/* func_0205f5ec @ 0x0205f5ec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021ca150;
extern int data_020dd768;
extern void func_02064328(void *, void *, unsigned int, unsigned int);

void *func_0205f5ec(unsigned int arg)
{
    func_02064328(&data_021ca150, &data_020dd768, arg >> 5, arg);
    return &data_021ca150;
}
