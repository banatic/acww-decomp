/* func_02023c44 @ 0x02023c44, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02023c44_3 UnkStruct_02023c44_3;
typedef struct UnkStruct_02023c44 UnkStruct_02023c44;
typedef struct UnkStruct_02023c44_2 UnkStruct_02023c44_2;
typedef struct UnkStruct_02023c44_4 UnkStruct_02023c44_4;

struct UnkStruct_02023c44_3 {
    unsigned char pad_00[0x830];
    void *data;
};

struct UnkStruct_02023c44 {
    unsigned char pad_00[0x100];
    UnkStruct_02023c44_3 *sub;
    char buf[0x1e];
    unsigned char flag;
};

struct UnkStruct_02023c44_2 {
    int word;
    unsigned char byte;
};

struct UnkStruct_02023c44_4 {
    char *text;
    unsigned char flag;
};

extern void func_0208150c(void *p);
extern int func_020036e8(void);
extern void func_0202da38(UnkStruct_02023c44 *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern UnkStruct_02023c44_2 data_020c8c18;

void func_02023c44(UnkStruct_02023c44 *a, UnkStruct_02023c44_4 *out)
{
    int x;
    int p6;
    int p7;

    func_0208150c(a->sub->data);
    x = func_020036e8();
    p6 = data_020c8c18.word;
    p7 = data_020c8c18.byte;

    func_0202da38(a, a->buf, &a->flag, 0x1e, x, p6, p7, 0, 0);

    out->text = a->buf;
    out->flag = a->flag;
}
