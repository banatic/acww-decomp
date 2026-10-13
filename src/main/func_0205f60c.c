/* func_0205f60c @ 0x0205f60c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021ca138;
extern int data_020dd780;
extern void func_02064328(void *, void *, unsigned int, unsigned int);

void *func_0205f60c(unsigned int arg)
{
    func_02064328(&data_021ca138, &data_020dd780, arg >> 5, arg);
    return &data_021ca138;
}
