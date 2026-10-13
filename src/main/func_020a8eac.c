/* func_020a8eac @ 0x020a8eac, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a8eac {
    char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020a8eac;

extern void func_020511f8(UnkStruct_020a8eac *);
extern void func_02051568(UnkStruct_020a8eac *);

void func_020a8eac(UnkStruct_020a8eac *arg0)
{
    if (arg0->unk_7C == 1) {
        func_020511f8(arg0);
    } else if (arg0->unk_7C == 2) {
        func_02051568(arg0);
    }
}
