/* fox_4: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221bec4 @ 0x0221bec4, 0x4 bytes, Thumb
 * func_ov003_0221bea4 @ 0x0221bea4, 0x20 bytes, Thumb
 * func_ov003_0221be7c @ 0x0221be7c, 0x28 bytes, Thumb
 */

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
    char pad_138[0xFE];
    unsigned char unk_236;
} UnkStruct_0221be7c;

extern int func_0203e0a8(void *p, int n);
extern void func_020b248c(int value);

int func_ov003_0221bec4(void *object)
{
    return 1;
}

void func_ov003_0221bea4(void *p)
{
    unsigned int flags = ((unsigned char *) p)[0x235] & 4;
    if (flags != 0) {
        func_0203e0a8(p, 0);
    }
}

int func_ov003_0221be7c(UnkStruct_0221be7c *s)
{
    func_020b248c(s->unk_136);
    s->unk_236 &= ~2;
    return 1;
}
