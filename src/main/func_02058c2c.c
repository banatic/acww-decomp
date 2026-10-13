/* func_02058c2c @ 0x02058c2c, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xD6];
    unsigned short unk_D6;
} UnkStruct_02058c2c;

extern void func_02059674(UnkStruct_02058c2c *p, int a);

void func_02058c2c(UnkStruct_02058c2c *p)
{
    if ((int) p->unk_D6 < 10) {
        p->unk_D6++;
        if ((int) p->unk_D6 >= 10) {
            func_02059674(p, 0);
        }
    }
}
