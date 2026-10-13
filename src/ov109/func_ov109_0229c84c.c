/* func_ov109_0229c84c @ 0x0229c84c, 0x10 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x29d3];
    unsigned char unk_29D3;
} UnkStruct_0229c84c;

extern void func_ov109_0229cb9c(UnkStruct_0229c84c *p, int arg);

void func_ov109_0229c84c(UnkStruct_0229c84c *p)
{
    func_ov109_0229cb9c(p, p->unk_29D3);
}
