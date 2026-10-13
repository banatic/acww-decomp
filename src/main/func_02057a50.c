/* func_02057a50 @ 0x02057a50, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02057a50;

extern void func_02057a98(void *, int);

void func_02057a50(UnkStruct_02057a50 *p, int arg)
{
    func_02057a98((char *) p + p->unk_08 + 4, arg);
}
