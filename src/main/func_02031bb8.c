/* func_02031bb8 @ 0x02031bb8, 0x5a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02031bb8 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02031bb8;

extern int func_02034270(int obj, void *p, int value0, int value1);
extern int func_020341c8(void *obj, int flag);
extern void func_0203423c(void *obj);
extern int func_02031078(int x, int y, int *out1, int *out2, int *out3);

int func_02031bb8(UnkStruct_02031bb8 *p)
{
    int v1, v2, v3;
    unsigned char obj[0x40];

    func_02034270((int) obj, p, 0, 0);

    if (func_020341c8(obj, 0) != 0) {
        func_0203423c(obj);
        return 1;
    }

    if (func_02031078(p->unk_00 >> 13, p->unk_08 >> 13, &v1, &v2, &v3) != 0) {
        func_0203423c(obj);
        return 1;
    } else {
        func_0203423c(obj);
        return 0;
    }
}
