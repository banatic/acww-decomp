/* func_0201107c @ 0x0201107c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_0201107c;
extern void func_02003260(UnkStruct_0201107c *p);
void func_0201107c(UnkStruct_0201107c *p, int *q)
{
    p->unk_98 = *q;
    func_02003260(p);
}
