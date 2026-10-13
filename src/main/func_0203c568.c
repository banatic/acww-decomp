/* func_0203c568 @ 0x0203c568, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0203c568 {
    char pad_00[0x9c];
    short unk_9C;
    char pad_9E[0xaa];
    short unk_148;
} UnkStruct_0203c568;

short func_0203c568(UnkStruct_0203c568 *p)
{
    return (short) (p->unk_148 + p->unk_9C);
}
