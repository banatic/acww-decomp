/* func_ov105_0229cc5c @ 0x0229cc5c, 0x4c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229cd30(void *p);
extern void func_ov105_0229c734(void *p);
extern void func_ov105_0229c6a0(void *p);
extern void func_ov105_0229c698(void *p);
extern void func_ov105_0229db14(void *p);

typedef struct {
    char pad_00[0x2be];
    unsigned char unk_2BE;
} UnkStruct_ov105_0229cc5c;

void func_ov105_0229cc5c(UnkStruct_ov105_0229cc5c *p)
{
    switch (p->unk_2BE) {
        case 0:
            func_ov105_0229cd30(p);
            break;
        case 1:
            func_ov105_0229c734(p);
            break;
        case 2:
            func_ov105_0229c6a0(p);
            break;
        case 3:
            func_ov105_0229c698(p);
            break;
        case 4:
        default:
            func_ov105_0229db14(p);
            break;
    }
}
