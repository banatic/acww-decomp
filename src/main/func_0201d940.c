/* func_0201d940 @ 0x0201d940, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
typedef struct {
    char pad_00[0xc8];
    int unk_C8;
    int unk_CC;
    char pad_D0[0x30];
    void *ptr;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0201d940;
typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201d940_2;
typedef struct {
    int unk_00;
    unsigned char unk_04;
} Global1;
typedef struct {
    int unk_00;
    int unk_04;
} Global2;
extern Global1 data_020c8be0;
extern Global2 data_020d8e18;
void func_0201d940(UnkStruct_0201d940 *s, UnkStruct_0201d940_2 *out)
{
    int a;
    int b;
    int c;
    int d;
    int e;
    a = func_020036e8(func_0208150c(*((int *) (((char *) s->ptr) + 0x830))));
    b = data_020c8be0.unk_00;
    c = data_020c8be0.unk_04;
    d = 0;
    e = 0;
    func_0202da38(s, s->unk_104, &s->unk_122, 0x1e, a, b, c, d, e);
    out->ptr = s->unk_104;
    out->byte = s->unk_122;
    {
        int tmp0 = data_020d8e18.unk_00;
        int tmp1 = data_020d8e18.unk_04;
        if (data_020c8be0.unk_04) {
            s->unk_C8 = tmp0;
        } else {
            s->unk_C8 = tmp0;
        }
        s->unk_CC = tmp1;
    }
}
