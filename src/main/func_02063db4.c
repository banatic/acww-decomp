/* func_02063db4 @ 0x02063db4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern void func_02063ce0(int, unsigned char, unsigned char, unsigned char);

void func_02063db4(int arg)
{
    union {
        unsigned int words[2];
        unsigned char bytes[8];
    } u;
    u.words[0] = 0;
    u.words[1] = 0;
    func_0209e474(&u);
    func_02063ce0(arg, u.bytes[5], u.bytes[4], u.bytes[3]);
}
