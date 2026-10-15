/* func_020a43a0 @ 0x020a43a0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a43a0 {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_020a43a0 *func_020682e0(int);
extern void func_02068320(struct UnkStruct_020a43a0 *);
extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void func_020a4e94(int, int);

void func_020a43a0(int arg0)
{
    struct UnkStruct_020a43a0 *p = func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    if ((((int) (func_02068320(p), p)), func_020b65c4()) == 6) {
        func_020b6098(func_020b5e10(), 2);
    } else {
        func_020b6098(func_020b5e10(), 0);
    }
    func_020a4e94(arg0, 0);
}
