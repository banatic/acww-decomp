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

extern void func_020374ac(UnkStruct_020374d0 *p);

UnkStruct_020374d0 *func_020374d0(UnkStruct_020374d0 *p, int x, int y, int z, int w, int c)
{
    func_020374ac(p);
    p->unk_00 = x;
    p->unk_04 = y;
    p->unk_0C = z;
    p->unk_08 = w;
    p->unk_10 = *(unsigned char *) &c;
    return p;
}
