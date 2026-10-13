/* func_02037210 @ 0x02037210, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c9f28[];
void func_020356c4(int, int, int, int);

typedef struct {
    char pad_00[8];
    int index;
    unsigned short unk_0C;
} UnkStruct_02037210;

void func_02037210(UnkStruct_02037210 *s)
{
    unsigned short val = data_020c9f28[s->index];
    func_020356c4(0x24, val, 0x7f, 0);
    s->unk_0C = val;
}
