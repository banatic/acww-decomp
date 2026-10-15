/* func_020326c4 @ 0x020326c4, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int a, int b);
extern void func_02031e28(int *arr, int val);
extern void func_02031e08(int *arr, int val);
extern int func_0202fc5c(void *out, int *src, int a, int b);
extern int func_0202fc18(void *out, int *src, int a, int b, void *param);

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
} UnkStruct_020326c4;

typedef struct {
    int a, b, c, d;
} UnkStruct_020326c4_2;

void func_020326c4(UnkStruct_020326c4 *out, int *src, int a, int b, int c)
{
    int local1[3];
    int local2[3];
    UnkStruct_020326c4_2 local3;
    int avg0, avg1, avg2;

    out->unk_48 = FX_MulFunc(c, c);

    local1[0] = src[0];
    local1[1] = src[1];
    local1[2] = src[2];
    local2[0] = src[0];
    local2[1] = src[1];
    local2[2] = src[2];

    func_02031e28(local1, a);
    func_02031e08(local2, a);
    func_02031e28(local1, b);
    func_02031e08(local2, b);

    avg2 = (local2[2] + local1[2]) >> 1;
    avg1 = (local2[1] + local1[1]) >> 1;
    avg0 = (local2[0] + local1[0]) >> 1;
    out->unk_3C = avg0;
    out->unk_40 = avg1;
    out->unk_44 = avg2;

    func_0202fc5c(&local3, src, a, b);
    func_0202fc18(out, src, a, b, &local3);
}
