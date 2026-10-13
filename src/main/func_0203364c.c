/* func_0203364c @ 0x0203364c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020338f8(void *a, void *b);

typedef struct {
    char pad_00[0x480];
    volatile unsigned int unk_480;
} UnkStruct_0203364c;

int func_0203364c(void *p0, void *buf)
{
    unsigned int c;
    if (((UnkStruct_0203364c *) p0)->unk_480 >= 0x18) {
        goto fail;
    }
    c = ((UnkStruct_0203364c *) p0)->unk_480;
    ((UnkStruct_0203364c *) p0)->unk_480 = c + 1;
    func_020338f8((char *) p0 + c * 0x30, buf);
    return 1;
fail:
    return 0;
}
