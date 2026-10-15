/* func_020ba0a8 @ 0x020ba0a8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002b40(int, unsigned char, int, int);

struct UnkStruct_020ba0a8 {
    int a;
    unsigned char b;
    int c;
    int d;
};

void func_020ba0a8(struct UnkStruct_020ba0a8 *s)
{
    func_02002b40(s->a, s->b, s->c, s->d);
}
