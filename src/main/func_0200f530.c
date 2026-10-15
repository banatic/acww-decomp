/* func_0200f530 @ 0x0200f530, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(void *dst, unsigned int a, unsigned int b);
extern int func_0200f434(void *arg1, void *arg2);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Pair;

int func_0200f530(void *arg1, Pair *arg2)
{
    unsigned int buffer[4];
    func_0204f794(buffer, arg2->unk_00, arg2->unk_04);
    return func_0200f434(arg1, buffer);
}
