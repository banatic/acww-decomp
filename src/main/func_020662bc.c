/* func_020662bc @ 0x020662bc, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[32];
} UnkStruct_020662bc;

extern void func_02094fd4(UnkStruct_020662bc *);
extern void func_02003618(int, UnkStruct_020662bc *);
extern void func_0203d7c4(int, UnkStruct_020662bc *);
extern void func_02094fbc(UnkStruct_020662bc *);
extern void func_02095074(int, UnkStruct_020662bc *);
extern void func_0203d73c(UnkStruct_020662bc *);
extern void func_0203d930(void *, void *, void *, int *, int, int);
extern void func_02066344(int, void *, void *, void *, int, int, int, int);

extern char data_021cd8c4;
extern char data_021cd9b0;
extern char data_021cd8ec;

void func_020662bc(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    int local3;
    UnkStruct_020662bc local1;
    UnkStruct_020662bc local2;

    if (p7 != 11) {
        func_02094fd4(&local1);
        func_02003618(p5, &local1);
        func_0203d7c4(p7, &local1);
        func_02094fbc(&local1);
    }

    func_02094fd4(&local2);
    func_02095074(p6, &local2);
    func_0203d73c(&local2);
    func_02094fbc(&local2);

    func_0203d930(&data_021cd8c4, &data_021cd9b0, &data_021cd8ec, &local3, p2, p3);
    func_02066344(p1, &data_021cd8c4, &data_021cd9b0, &data_021cd8ec, local3, p4, p5, p6);
}
