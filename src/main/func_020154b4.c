/* func_020154b4 @ 0x020154b4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(void *p, int n);

struct UnkStruct_020154b4 {
    char pad_00[0x7E];
    unsigned short unk_7E;
    unsigned int unk_80;
    char pad_84[0x10];
    unsigned char unk_94;
    char pad_95[3];
    unsigned int unk_98;
};

int func_020154b4(struct UnkStruct_020154b4 *s, unsigned short *p, unsigned int v2, unsigned char v3, unsigned int v4)
{
    int result = 0;
    if (func_0201596c(s, 3)) {
        s->unk_7E = *p;
        s->unk_80 = v2;
        s->unk_94 = v3;
        s->unk_98 = v4;
        result = 1;
    }
    return result;
}
