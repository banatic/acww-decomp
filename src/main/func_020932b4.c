/* func_020932b4 @ 0x020932b4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x34];
    int mode;
    char tail[0xc];
} UnkStruct_020932b4;

extern int func_02034270(UnkStruct_020932b4 *obj, int a, int b, int c);
extern void func_0203423c(UnkStruct_020932b4 *obj);
extern int func_020b6598(void);
extern int func_02094cf8(int a0, int a1, int a2, int a3, int a4, int a5);

int func_020932b4(int p0, int p1, int p2, int p3, int p4, int p5)
{
    UnkStruct_020932b4 obj;
    int mode;
    int result;

    func_02034270(&obj, p1, 0, 0);
    mode = obj.mode;
    result = -1;
    if (mode == 0x13 || (func_020b6598() && mode == 3)) {
        result = p4;
    }
    if (result != -1) {
        result = func_02094cf8(p4, p0, p1, p2, p3, p5);
        func_0203423c(&obj);
        return result;
    } else {
        func_0203423c(&obj);
        return 3;
    }
}
