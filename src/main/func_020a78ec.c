/* func_020a78ec @ 0x020a78ec, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a78ec {
    char pad_00;
    unsigned char byte;
};

extern void func_02077a54(struct UnkStruct_020a78ec *p, int b, unsigned char flags);

void func_020a78ec(struct UnkStruct_020a78ec *p, int a, int b, int c, unsigned char d, int e)
{
    unsigned char flags = 0;
    if (c) {
        flags |= 1;
    }
    if (d) {
        flags |= 2;
    }
    func_02077a54(p, b, flags);
    p->byte = e;
    p->byte |= (a << 6) & 0xC0;
}
