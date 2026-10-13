/* func_020374d0 @ 0x020374d0, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    short unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
} UnkStruct_020374d0;

extern void func_020374ac(UnkStruct_020374d0 *p, int x, short y, int z);

UnkStruct_020374d0 *func_020374d0(UnkStruct_020374d0 *p, int x, short y, int z, int w, unsigned char c)
{
    func_020374ac(p, x, y, z);
    p->unk_00 = x;
    p->unk_04 = y;
    p->unk_0C = z;
    p->unk_08 = w;
    p->unk_10 = c;
    return p;
}
