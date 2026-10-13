/* func_0203af08 @ 0x0203af08, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1ca];
    unsigned char unk_1CA;
    char pad_1CB[1];
    int unk_1CC[3];
    int unk_1D8[3];
} UnkStruct_0203af08;
extern UnkStruct_0203af08 *data_021c67a4;
extern int *func_02095794(int a);
extern int func_0203affc(int *a, int *b, int *c, int *out, int *extra);
extern int func_0203b144(void);
extern void func_0203c0ac(UnkStruct_0203af08 *p, int mode);

void func_0203af08(int *a, int *b)
{
    int r;

    r = func_0203affc(func_02095794(4), a, b, 0, 0);
    if (r >= 0xb000) {
        func_0203b144();
    } else {
        int *d;
        data_021c67a4->unk_1CA = 1;
        d = data_021c67a4->unk_1CC;
        d[0] = a[0];
        d[1] = a[1];
        d[2] = a[2];
        d = data_021c67a4->unk_1D8;
        d[0] = b[0];
        d[1] = b[1];
        d[2] = b[2];
        func_0203c0ac(data_021c67a4, 2);
    }
}
