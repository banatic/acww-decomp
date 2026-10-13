/* func_0209bc88 @ 0x0209bc88, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bc94(unsigned char byte);

struct Struct0209bc88 {
    unsigned char data[0xa];
    unsigned char byte;
};

void func_0209bc88(struct Struct0209bc88 *self)
{
    func_0209bc94(self->byte);
}
