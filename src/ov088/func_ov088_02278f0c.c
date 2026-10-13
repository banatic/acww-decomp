/* func_ov088_02278f0c @ 0x02278f0c, 0xe bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb0];
    unsigned int unk_B0;
    unsigned char unk_B4;
} UnkStruct_02278f0c;

void func_ov088_02278f0c(UnkStruct_02278f0c *p, unsigned int v)
{
    unsigned int *pw;
    unsigned char *pb;

    pw = &p->unk_B0;
    *pw = v;
    pb = &p->unk_B4;
    *pb = 0;
}
