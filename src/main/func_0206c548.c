/* func_0206c548 @ 0x0206c548, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct St {
    char pad_00[0x2c];
    unsigned int unk_2C;
};

extern void func_0206d420(struct St *p, unsigned int a, unsigned int b);

void func_0206c548(struct St *p)
{
    unsigned int y = p->unk_2C + 0x14b8;
    func_0206d420(p, y + 0x228, y);
}
