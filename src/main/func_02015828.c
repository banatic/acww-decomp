/* func_02015828 @ 0x02015828, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02015828 {
    char pad_00[0x68];
    int unk_68;
} UnkStruct_02015828;

int func_0201596c(UnkStruct_02015828 *p, int arg);

int func_02015828(UnkStruct_02015828 *p, int x)
{
    int result = 0;
    if (func_0201596c(p, result)) {
        p->unk_68 = x;
        result = 1;
    }
    return result;
}
