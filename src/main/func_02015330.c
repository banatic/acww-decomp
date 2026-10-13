/* func_02015330 @ 0x02015330, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(void *a, int b);

typedef struct {
    char pad_00[0x7e];
    unsigned short unk_7E;
    unsigned int unk_80;
    char pad_84[0x10];
    unsigned char unk_94;
    char pad_95[3];
    unsigned int unk_98;
} UnkStruct_02015330;

int func_02015330(UnkStruct_02015330 *p, unsigned short *src, unsigned int val3, unsigned char val4, unsigned int val5)
{
    int result = 0;
    if (func_0201596c(p, 4) != 0) {
        p->unk_7E = *src;
        p->unk_80 = val3;
        p->unk_94 = val4;
        p->unk_98 = val5;
        result = 1;
    }
    return result;
}
