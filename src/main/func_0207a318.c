/* func_0207a318 @ 0x0207a318, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_0207a318;

extern void func_0207a308(UnkStruct_0207a318 *p1, UnkStruct_0207a318 *p2);
extern void func_0207a254(UnkStruct_0207a318 *p);

void func_0207a318(UnkStruct_0207a318 *p)
{
    func_0207a308(p, p);
    func_0207a254(p);
    p->unk_0C = 0;
    p->unk_10 = 0;
}
