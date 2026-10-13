/* func_0201b188 @ 0x0201b188, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0200322c(unsigned short *x, unsigned short *y);

typedef struct {
    char pad_00[0x34];
    unsigned short unk_34;
    char pad_36[0x0E];
    unsigned short unk_44;
} UnkStruct_0201b188;

typedef struct {
    char pad_00[0x5c];
    unsigned short unk_5C;
} UnkStruct_0201b188_2;

void func_0201b188(UnkStruct_0201b188 *a, UnkStruct_0201b188_2 *b)
{
    a->unk_34 = func_0200322c(&b->unk_5C, &a->unk_44);
}
