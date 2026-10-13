/* func_0205510c @ 0x0205510c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0205510c {
    unsigned char pad_00[8];
    unsigned int flags;
    unsigned char pad_0C[0x30];
    unsigned int cond;
} UnkStruct_0205510c;

extern void func_02055e7c(UnkStruct_0205510c *s, int param2);

void func_0205510c(UnkStruct_0205510c *s, int param2)
{
    if (s->cond) {
        s->flags |= 1;
    }
    func_02055e7c(s, param2);
}
