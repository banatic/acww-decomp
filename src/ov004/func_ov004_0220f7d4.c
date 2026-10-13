/* func_ov004_0220f7d4 @ 0x0220f7d4, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02247634[];
extern int func_ov004_0220ccf8(char *self, int v);
int func_ov004_0220f7d4(char *self)
{
    return func_ov004_0220ccf8(self, data_ov004_02247634[*(int *) (self + 0x76c)]);
}
