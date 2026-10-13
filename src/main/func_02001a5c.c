/* func_02001a5c @ 0x02001a5c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001b6c(int);
extern unsigned char data_0213fe94[];

void func_02001a5c(void)
{
    unsigned char *p;
    unsigned char val;

    func_02001b6c(4);
    p = data_0213fe94;
    val = p[0x12];
    val |= 2;
    p[0x12] = val;
}
