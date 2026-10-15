/* func_02026bb8 @ 0x02026bb8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct InnerStruct {
    char pad_00[0x830];
    int value;
} InnerStruct;

typedef struct UnkStruct_02026bb8 {
    char pad_00[0x100];
    InnerStruct *inner;
    unsigned char data[0x22];
} UnkStruct_02026bb8;

typedef struct UnkStruct_02026bb8_2 {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_02026bb8_2;

typedef struct DataGlobal {
    int unk_00;
    unsigned char unk_04;
} DataGlobal;

extern DataGlobal data_020c8b68;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(UnkStruct_02026bb8 *, unsigned char *, unsigned char *, int, int, int, int, int, int);

void func_02026bb8(UnkStruct_02026bb8 *a, UnkStruct_02026bb8_2 *b)
{
    int arg5, arg6, arg7, arg8, arg9;

    arg5 = func_020036e8(func_0208150c(a->inner->value));
    arg6 = data_020c8b68.unk_00;
    arg7 = data_020c8b68.unk_04;
    arg8 = 0;
    arg9 = 0;

    func_0202da38(a, a->data, &a->data[0x1e], 0x1e, arg5, arg6, arg7, arg8, arg9);

    b->unk_00 = a->data;
    b->unk_04 = a->data[0x1e];
}
