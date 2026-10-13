/* func_020f5958 @ 0x020f5958, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213f074;

typedef struct {
    int *unk_00;
    char pad_04[0x3a];
    char unk_3E;
} UnkStruct_020f5958;

void func_020f5958(UnkStruct_020f5958 *p)
{
    p->unk_00 = &data_0213f074;
    p->unk_3E = 0;
}
