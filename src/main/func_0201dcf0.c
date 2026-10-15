/* func_0201dcf0 @ 0x0201dcf0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201dcf0 {
    char pad_00[0x830];
    int value;
} UnkStruct_0201dcf0;

typedef struct UnkStruct_0201dcf0_2 {
    char pad_00[0x100];
    UnkStruct_0201dcf0 *ptr;
    char buf[30];
    unsigned char flag;
} UnkStruct_0201dcf0_2;

typedef struct Global {
    int word;
    unsigned char byte;
} Global;

typedef struct UnkStruct_0201dcf0_3 {
    char *ptr;
    unsigned char byte;
} UnkStruct_0201dcf0_3;

extern Global data_020c8d18;

extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0202da38(UnkStruct_0201dcf0_2 *a, void *p1, void *p2, int n, int arg5, int arg6, int arg7, int arg8, int arg9);

void func_0201dcf0(UnkStruct_0201dcf0_2 *a, UnkStruct_0201dcf0_3 *out)
{
    func_0202da38(a, a->buf, &a->flag, 30, func_020036e8(func_0208150c(a->ptr->value)), data_020c8d18.word, 1, 7,
                  data_020c8d18.byte);
    out->ptr = a->buf;
    out->byte = a->flag;
}
