/* func_02028838 @ 0x02028838, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x830];
    unsigned int unk_830;
} UnkStruct_02028838;

typedef struct {
    char pad_00[0x100];
    UnkStruct_02028838 *sub;
    char pad_104[0x1E];
    unsigned char unk_122;
} UnkStruct_02028838_2;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} UnkStruct_02028838_3;

typedef struct {
    void *ptr;
    unsigned char byte;
} OutputStruct;

extern UnkStruct_02028838_3 data_020c8c30;
extern UnkStruct_02028838_3 data_020c8c10;
extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern unsigned int func_0208150c(unsigned int);
extern unsigned int func_020036e8(unsigned char *);
extern int func_0202da38(void *a, void *b, void *c, int d, int base, int offset, int scale, int h, int i);

void func_02028838(UnkStruct_02028838_2 *p1, OutputStruct *p2)
{
    UnkStruct_02028838_3 *dp = 0;
    int x;
    unsigned int v;

    x = func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) p1));
    switch (x) {
        case 10:
            dp = &data_020c8c30;
            break;
        case 19:
            dp = &data_020c8c10;
            break;
    }
    if (dp) {
        v = func_020036e8((unsigned char *) func_0208150c(p1->sub->unk_830));
        func_0202da38(p1, (char *) p1 + 0x104, (char *) p1 + 0x122, 30, v, dp->unk_00, dp->unk_04, 0, 0);
    }
    p2->ptr = (char *) p1 + 0x104;
    p2->byte = p1->unk_122;
}
