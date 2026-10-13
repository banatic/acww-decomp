/* func_02044e28 @ 0x02044e28, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} GObj_02044e28;

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x24 - 0xc];
} TableElem_02044e28;

typedef struct {
    unsigned char b0_bit0 : 1;
    unsigned char kind : 2;
    unsigned char b0_pad : 5;
    unsigned char sub : 2;
    unsigned char flag : 1;
    unsigned char b1_pad : 5;
} A_02044e28;

extern GObj_02044e28 *data_020ccf94;
extern TableElem_02044e28 data_021c7c48[4];
extern void *data_021c7880;
extern void *func_020b65c4(void);
extern int DWC_Alloc(int a, int b);
extern void func_02042a9c(A_02044e28 *a);
extern void func_02044fe8(A_02044e28 *a);
extern void func_02044f3c(A_02044e28 *a);
extern void func_02044ec4(A_02044e28 *a, void *b);

void func_02044e28(A_02044e28 *a, void *b)
{
    if (data_020ccf94->unk_64 == a->kind) {
        int idx = a->sub;
        TableElem_02044e28 *e = &data_021c7c48[idx];
        if (!a->flag) {
            e->unk_08 = 3;
        } else {
            e->unk_08 = 2;
            func_02044fe8(a);
        }
    } else if (a->flag) {
        if (b == func_020b65c4() && data_021c7880 != 0) {
            if (DWC_Alloc(10, 4)) {
                func_02042a9c(a);
                func_02044fe8(a);
            } else {
                func_02044fe8(a);
                func_02044f3c(a);
            }
        } else {
            func_02044ec4(a, b);
        }
    }
}
