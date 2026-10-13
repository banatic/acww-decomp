/* func_02078748 @ 0x02078748, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02078748 {
    int x;
    int y;
} UnkStruct_02078748;
extern int *data_020ccf94;
extern int func_02073d90(int *);
extern void func_020787b4(UnkStruct_02078748 *, int, int, int);
extern void func_02073820(int *);
extern void func_020737f0(int *, UnkStruct_02078748 *, int);
extern void func_02073770(int *, int, int);

void func_02078748(int a, int b, int c)
{
    UnkStruct_02078748 local;
    int *p;
    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }
    func_020787b4(&local, a, b, c);
    p = data_020ccf94;
    func_02073820(p);
    func_020737f0(p, &local, 3);
    func_02073770(p, 0x3e, 4);
}
