/* func_ov003_0221be7c @ 0x0221be7c, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b248c(int value);

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
    char pad_138[0xFE];
    unsigned char unk_236;
} UnkStruct_0221be7c;

int func_ov003_0221be7c(UnkStruct_0221be7c *s)
{
    func_020b248c(s->unk_136);
    s->unk_236 &= ~2;
    return 1;
}
