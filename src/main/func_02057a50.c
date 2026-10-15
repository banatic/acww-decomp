/* func_02057a50 @ 0x02057a50, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02057a50;

extern int func_02057a98(void *, const char *name);

int func_02057a50(UnkStruct_02057a50 *p, const char *name)
{
    return func_02057a98((char *) p + p->unk_08 + 4, name);
}
