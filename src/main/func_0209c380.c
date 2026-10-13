/* func_0209c380 @ 0x0209c380, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209c38c(unsigned char);

typedef struct {
    char pad_00[0x10];
    unsigned char unk_10;
} Func0209c380;

void func_0209c380(Func0209c380 *self)
{
    func_0209c38c(self->unk_10);
}
