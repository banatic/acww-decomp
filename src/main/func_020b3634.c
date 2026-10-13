/* func_020b3634 @ 0x020b3634, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a50(unsigned int, const unsigned char *);
extern unsigned char data_020e5108[];

void func_020b3634(char *out, unsigned int in)
{
    *out = func_02057a50(in, data_020e5108);
}
