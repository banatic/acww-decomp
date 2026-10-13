/* func_0209737c @ 0x0209737c, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0209737c;

extern int func_02097188(int a, int b, int c, int d);
extern int func_0209de44(int a, int b, int c, int d);

int func_0209737c(UnkStruct_0209737c *p)
{
    if (p->unk_04 == p->unk_08) {
        return func_02097188(2 * p->unk_08 - 2, 2, (unsigned char) p->unk_04, 1);
    }
    if (p->unk_04 == 4 && p->unk_08 == 1) {
        return func_02097188(0x1c, 2, (unsigned char) p->unk_04, 1);
    }
    if (p->unk_04 == 0xc && p->unk_08 == 0x18) {
        return func_02097188(0x1e, 2, (unsigned char) p->unk_04, 1);
    }
    if (p->unk_04 == 6) {
        if (p->unk_08 == func_0209de44((unsigned char) p->unk_00, (unsigned char) p->unk_04, 0, 3)) {
            return func_02097188(0x1a, 2, (unsigned char) p->unk_04, 1);
        }
    }
    if (p->unk_04 == 5) {
        if (p->unk_08 == func_0209de44((unsigned char) p->unk_00, (unsigned char) p->unk_04, 0, 2)) {
            return func_02097188(0x18, 2, (unsigned char) p->unk_04, 1);
        }
    }
    return 0;
}
