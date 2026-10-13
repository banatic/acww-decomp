/* func_0202760c @ 0x0202760c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Global1;

typedef struct {
    int unk_00;
    int unk_04;
} Global2;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0202760c;

typedef struct {
    char pad_00[0xc8];
    Global2 unk_C8;
    char pad_D0[0x30];
    void *unk_100;
    char arr_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0202760c_2;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(UnkStruct_0202760c_2 *a, char *p1, unsigned char *p2, int len, int arg5, int arg6, int arg7,
                          int arg8, int arg9);
extern Global1 data_020c8e10;
extern Global2 data_020d94b0;

void func_0202760c(UnkStruct_0202760c_2 *a, UnkStruct_0202760c *out)
{
    int x;
    int g1_word;
    int g1_byte;
    int z1, z2;

    x = func_020036e8(func_0208150c(*(int *) ((char *) a->unk_100 + 0x830)));
    g1_word = data_020c8e10.unk_00;
    g1_byte = data_020c8e10.unk_04;
    z1 = 0;
    z2 = 0;

    func_0202da38(a, a->arr_104, &a->unk_122, 30, x, g1_word, g1_byte, z1, z2);

    out->ptr = a->arr_104;
    out->byte = a->unk_122;
    a->unk_C8 = data_020d94b0;
}
