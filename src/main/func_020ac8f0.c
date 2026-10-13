/* func_020ac8f0 @ 0x020ac8f0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FS_OpenFile(const void *, const void *);
extern void *func_020e98d4(int);
extern int FS_ReadFile(const void *, void *, int);
extern int FS_CloseFile(const void *);
extern int data_020e40c4;

typedef struct {
    int unk_00;
    void *unk_04;
} UnkStruct_020ac8f0;

int func_020ac8f0(UnkStruct_020ac8f0 *out, const void *param1)
{
    int a;
    int b;
    int c;

    a = FS_OpenFile(param1, &data_020e40c4);
    out->unk_04 = func_020e98d4(0x800);

    if (out->unk_04 != 0) {
        b = FS_ReadFile(param1, out->unk_04, 0x800) != -1;
    } else {
        b = 0;
    }

    c = FS_CloseFile(param1);

    return (a && b && c && out->unk_04 != 0) ? 1 : 0;
}
