/* func_02012bcc @ 0x02012bcc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x88];
    int unk_88;
    int unk_8C;
} UnkStruct_02012bcc;
extern void *data_021c80bc;
extern int func_02013518(UnkStruct_02012bcc *, void *);
extern void func_02013440(UnkStruct_02012bcc *);
extern void func_02012e58(UnkStruct_02012bcc *, void *);

extern void func_02012c20(UnkStruct_02012bcc *, void *);
int func_02012bcc(UnkStruct_02012bcc *a, void *b)
{
    if (data_021c80bc == 0) {
        goto zero;
    }
    func_02012c20(a, b);
    if (func_02013518(a, b) != 0) {
        goto one;
    }
    func_02013440(a);
    a->unk_88 = 0;
    a->unk_8C = 2;
    func_02012e58(a, b);
    goto zero;
one:
    return 1;
zero:
    return 0;
}
