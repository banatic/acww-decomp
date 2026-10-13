/* func_02040010 @ 0x02040010, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_02040010;

typedef struct {
    unsigned short h;
    char pad_02[3];
    unsigned char unk_05;
    unsigned char unk_06;
    char pad_07[2];
    unsigned char unk_09;
    unsigned char unk_0A;
} UnkStruct_02040010_2;

void func_02040010(UnkStruct_02040010_2 *p, UnkStruct_02040010 x, ...)
{
    unsigned char c = x.c;
    if (p->h == 0x16) {
        goto L;
    }
    if (p->h == 0x18) {
        goto L;
    }
    if (p->h != 0x19) {
        goto skip;
    }
L:
    p->unk_06 = c;
    p->unk_05 = 6;
    p->unk_0A = c;
    p->unk_09 = 0x18;
skip:;
}
