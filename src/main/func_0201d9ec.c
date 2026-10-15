/* func_0201d9ec @ 0x0201d9ec, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *a, char *b, void *c, int d, int e, int f, int g, int h, int i);

typedef struct {
    int low;
    int high;
} Pair;

typedef struct UnkStruct_0201d9ec_2 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0201d9ec_2;

typedef struct UnkStruct_0201d9ec {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x30];
    UnkStruct_0201d9ec_2 *ptr;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0201d9ec;

typedef struct {
    char *unk_00;
    unsigned char unk_04;
} UnkStruct_0201d9ec_3;

typedef struct {
    int first;
    unsigned char second;
} UnkStruct_0201d9ec_4;

extern UnkStruct_0201d9ec_4 data_020c8d68;
extern Pair data_020d9110;

void func_0201d9ec(UnkStruct_0201d9ec *a, UnkStruct_0201d9ec_3 *out)
{
    func_0202da38(a, a->unk_104, &a->unk_122, 0x1e, func_020036e8(func_0208150c(a->ptr->unk_830)), data_020c8d68.first,
                  data_020c8d68.second, 0, 0);

    out->unk_00 = a->unk_104;
    out->unk_04 = a->unk_122;

    a->unk_C8 = data_020d9110;
}
