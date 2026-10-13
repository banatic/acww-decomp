/* func_020a4370 @ 0x020a4370, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    int unk_04;
} UnkStruct_020a4370;

extern UnkStruct_020a4370 *func_020682e0(int);
extern int func_02068320(UnkStruct_020a4370 *);
extern int func_020b5e10(int);
extern int func_020b6098(int, int);
extern void func_020a4e94(int, int);

void func_020a4370(int arg)
{
    UnkStruct_020a4370 *p = func_020682e0(0);
    if (p->unk_04 == 0) {
        func_020b6098(func_020b5e10(func_02068320(p)), 2);
        func_020a4e94(arg, 0);
    }
}
