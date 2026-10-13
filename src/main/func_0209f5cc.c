/* func_0209f5cc @ 0x0209f5cc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207417c(int);

typedef struct {
    unsigned char pad_00[0xA0];
    unsigned short unk_A0;
} UnkStruct_0209f5cc;

void func_0209f5cc(UnkStruct_0209f5cc *s)
{
    s->unk_A0 = 0xC8;
    func_0207417c(3);
}
