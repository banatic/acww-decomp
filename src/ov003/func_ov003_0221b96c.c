/* func_ov003_0221b96c @ 0x0221b96c, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8b4c(int a, int b);
extern void func_0203edd0(void *p);

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x1a5];
    unsigned char flag;
} UnkStruct_0221b96c;

int func_ov003_0221b96c(UnkStruct_0221b96c *p0, UnkStruct_0221b96c *p1)
{
    if ((p0->flag & 8) != 0 && p1 != 0 && func_020e8b4c((short) (p0->unk_8E + 0x8000), (short) p1->unk_8E) < 0x1300) {
        func_0203edd0(p0);
        return 1;
    }
    return 0;
}
