/* func_02020588 @ 0x02020588, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern unsigned int data_020c8ab0;
extern unsigned int data_020d91f8[2];

typedef struct UnkStruct_02020588_2 {
    unsigned char pad_00[0x830];
    unsigned int unk_830;
} UnkStruct_02020588_2;

typedef struct TwoWords {
    unsigned int a;
    unsigned int b;
} TwoWords;

struct UnkStruct_02020588 {
    unsigned char pad_00[0xc8];
    TwoWords unk_C8;
    unsigned char pad_D0[0x30];
    UnkStruct_02020588_2 *unk_100;
    unsigned char unk_104[30];
    unsigned char unk_122;
};

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02020588_3;

void func_02020588(struct UnkStruct_02020588 *s, UnkStruct_02020588_3 *out)
{
    int local0;
    unsigned int local1;

    local0 = func_020036e8(func_0208150c(s->unk_100->unk_830));
    local1 = data_020c8ab0;
    func_0202da38(s, &s->unk_104, &s->unk_122, 30, local0, local1, 1, 8, 2);

    out->ptr = &s->unk_104;
    out->byte = s->unk_122;

    *(TwoWords *) ((char *) s + 0xc8) = *(TwoWords *) data_020d91f8;
}
