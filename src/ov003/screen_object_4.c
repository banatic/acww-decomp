/* screen_object_4: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221b9c0 @ 0x0221b9c0, 0x10 bytes, Thumb
 * func_ov003_0221b9bc @ 0x0221b9bc, 0x4 bytes, Thumb
 * func_ov003_0221b9b8 @ 0x0221b9b8, 0x4 bytes, Thumb
 * func_ov003_0221b96c @ 0x0221b96c, 0x4c bytes, Thumb
 */

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x1a5];
    unsigned char flag;
} UnkStruct_0221b96c;

extern void func_ov003_0221b83c(void *argument0);
extern int func_020e8b4c(int a, int b);
extern void func_0203edd0(void *p);

int func_ov003_0221b9c0(void *argument0)
{
    func_ov003_0221b83c(argument0);
    return 1;
}

int func_ov003_0221b9bc(void)
{
    return 1;
}

int func_ov003_0221b9b8(void)
{
    return 1;
}

int func_ov003_0221b96c(UnkStruct_0221b96c *p0, UnkStruct_0221b96c *p1)
{
    if ((p0->flag & 8) != 0 && p1 != 0 && func_020e8b4c((short) (p0->unk_8E + 0x8000), (short) p1->unk_8E) < 0x1300) {
        func_0203edd0(p0);
        return 1;
    }
    return 0;
}
