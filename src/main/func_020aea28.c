/* func_020aea28 @ 0x020aea28, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020aea28 {
    unsigned char data[0x10];
};

extern void func_020b00c8(void *, const void *, int);

void func_020aea28(struct UnkStruct_020aea28 *p)
{
    func_020b00c8(p, (char *) p + 0x10, 6);
    p->data[0xF] = 1;
}
