/* func_0205e878 @ 0x0205e878, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(void *a, void *b, unsigned int c, unsigned int d);
extern char data_021c9f48[];
extern char data_020dd738[];

void *func_0205e878(unsigned int a)
{
    func_02064328(data_021c9f48, data_020dd738, a >> 5, a);
    return data_021c9f48;
}
