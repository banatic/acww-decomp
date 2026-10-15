/* func_0209f668 @ 0x0209f668, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0209f668;

extern UnkStruct_0209f668 *func_020682e0(int);
extern void func_02068320(UnkStruct_0209f668 *);
extern int func_020b5e10(void);
extern int func_020b6434(int, int, int, int);
extern int func_02073d90(int);
extern int func_020b5ee4(int, int);
extern void func_020a18ac(void);
extern void func_020a1948(void);
extern int data_020ccf94;

void func_0209f668(void)
{
    UnkStruct_0209f668 *s = func_020682e0(0);
    if (s->unk_04 != 0) {
        return;
    }

    func_02068320(s);
    func_020b6434(func_020b5e10(), 46, 2, 3);

    if (func_02073d90(data_020ccf94) != 0) {
        func_020b5ee4(func_020b5e10(), 0);
        func_020a18ac();
    } else {
        func_020a1948();
    }
}
