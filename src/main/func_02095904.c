/* func_02095904 @ 0x02095904, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200f290(void *p, int a);
extern int func_0200c3b0(void *p, int a, int b, int c);

struct UnkStruct_02095904 {
    char pad_00[0x7f0];
    int unk_7F0;
};

int func_02095904(void)
{
    void *ptr = (void *) func_02096718(4);
    if (ptr) {
        if (((struct UnkStruct_02095904 *) ptr)->unk_7F0 == 0x28) {
            if (func_0200f290(ptr, 0xb)) {
                return 1;
            }
        }
        return func_0200c3b0(ptr, 3, 5, -1);
    }
    return 0;
}
