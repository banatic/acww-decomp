/* func_02037514 @ 0x02037514, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02037514;

void func_02037514(UnkStruct_02037514 *out, const unsigned char *data, int index)
{
    UnkStruct_02037514 tmp;
    unsigned char *p = (unsigned char *) data + 2;
    int off = index * 6;
    tmp.unk_00 = p[off];
    p += off;
    tmp.unk_04 = (*(signed short *) (p + 2)) << 12;
    tmp.unk_08 = (*(signed short *) (p + 4)) << 12;
    *out = tmp;
}
