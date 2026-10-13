/* func_02074d60 @ 0x02074d60, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x6c];
    unsigned char unk_6C;
} UnkStruct_02074d60;

extern UnkStruct_02074d60 *data_020ccf94;

extern int func_02073dd4(UnkStruct_02074d60 *p, int a);
extern void func_020a7394(int a, int b, int c, int d, int e);
extern void func_02073de0(UnkStruct_02074d60 *p, int a, int b);
extern void func_020738f4(UnkStruct_02074d60 *p, unsigned char b);
extern void func_02073cb8(UnkStruct_02074d60 *p, int a);
extern void func_02073c74(UnkStruct_02074d60 *p, int a, int b);
extern void func_020a6c6c(int a);
extern void func_02075104(int a);

void func_02074d60(int param0)
{
    int i;
    UnkStruct_02074d60 *loopPtr;
    UnkStruct_02074d60 *p;

    i = 3;
    loopPtr = data_020ccf94;

    do {
        if (func_02073dd4(loopPtr, i) != 0) {
            if (i == 0) {
                func_020a7394(0, 0x3f, 1, 0, 2);
            } else {
                func_020a7394(i, 0x3f, 0, 0, 2);
            }
        }
        i--;
    } while (i >= 0);

    func_020a7394(param0, 0x3f, 0, 0, 7);

    p = data_020ccf94;
    func_02073de0(p, param0, 0);
    func_020738f4(p, (unsigned char) (p->unk_6C - 1));
    func_02073cb8(p, param0);
    func_02073c74(p, param0, 0);
    func_020a6c6c(param0);
    func_02075104(-param0);
}
