/* func_02035198 @ 0x02035198, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[28];
} UnkStruct_02035198;

extern int func_02034f78(UnkStruct_02035198 *, int);
extern void func_02034e78(UnkStruct_02035198 *, int);
extern void func_02037470(UnkStruct_02035198 *, int);

void func_02035198(UnkStruct_02035198 *p, int arg1)
{
    int idx = func_02034f78(p, arg1);
    if (idx < 0) {
        return;
    }
    func_02034e78(p, idx);
    func_02037470(p + idx, arg1);
}
