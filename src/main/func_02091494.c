/* func_02091494 @ 0x02091494, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020914dc(void *);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    short unk_0C;
    short unk_0E;
    short unk_10;
    int unk_14;
    short unk_18;
} UnkStruct_02091494;

void func_02091494(UnkStruct_02091494 *out, int a, short b, int *src, short *p1, short *p2, short c)
{
    func_020914dc(out);
    out->unk_14 = a;
    out->unk_18 = b;
    out->unk_00 = src[0];
    out->unk_04 = src[1];
    out->unk_08 = src[2];
    if (p1) {
        out->unk_0C = *p1;
    }
    if (p2) {
        out->unk_10 = *p2;
    }
    out->unk_0E = c;
}
