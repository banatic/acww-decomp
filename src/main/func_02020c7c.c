/* func_02020c7c @ 0x02020c7c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x100];
    void *unk_100;
    char data[0x1e];
    unsigned char unk_122;
} UnkStruct_02020c7c;

typedef struct {
    unsigned char pad_00[0x830];
    int unk_830;
} SecondStruct;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02020c7c_2;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02020c7c_3;

extern UnkStruct_02020c7c_2 data_020c8a88;
extern int func_0208150c(int arg);
extern int func_020036e8(int arg);
extern void func_0202da38(void *p1, void *p2, void *p3, int d, int e, int f, int g, int h, int i);

void func_02020c7c(UnkStruct_02020c7c *p1, UnkStruct_02020c7c_3 *out)
{
    int local0;
    int local1;
    int local2;

    local0 = func_020036e8(func_0208150c(((SecondStruct *) p1->unk_100)->unk_830));
    local1 = data_020c8a88.unk_00;
    local2 = data_020c8a88.unk_04;

    func_0202da38(p1, p1->data, &p1->unk_122, 30, local0, local1, local2, 1, 0);

    out->ptr = p1->data;
    out->byte = p1->unk_122;
}
