/* func_020253bc @ 0x020253bc, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020253bc {
    unsigned char pad_00[0x830];
    int unk_830;
} UnkStruct_020253bc;

typedef struct UnkStruct_020253bc_2 {
    unsigned char pad_00[0x100];
    UnkStruct_020253bc *ptr;
    unsigned char arr[0x1e];
    unsigned char byte;
} UnkStruct_020253bc_2;

typedef struct UnkStruct_020253bc_3 {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_020253bc_3;

typedef struct UnkStruct_020253bc_4 {
    unsigned char *unk_00;
    unsigned char unk_04;
} UnkStruct_020253bc_4;

extern UnkStruct_020253bc_3 data_020c8ad0;
extern UnkStruct_020253bc_3 data_020c8ac0;

extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(UnkStruct_020253bc_2 *, unsigned char *, unsigned char *, int, int, int, int, int, int);

void func_020253bc(UnkStruct_020253bc_2 *r5, UnkStruct_020253bc_4 *r6)
{
    UnkStruct_020253bc_3 *r4 = &data_020c8ad0;

    if (func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) r5)) == 1) {
        r4 = &data_020c8ac0;
    }

    func_0202da38(r5, r5->arr, &r5->byte, 0x1e, func_020036e8((unsigned char *) func_0208150c(r5->ptr->unk_830)), r4->unk_00,
                  r4->unk_04, 0, 0);

    r6->unk_00 = r5->arr;
    r6->unk_04 = r5->byte;
}
