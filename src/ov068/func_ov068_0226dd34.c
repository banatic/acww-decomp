/* func_ov068_0226dd34 @ 0x0226dd34, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203caa4(void *p, int a, int b);
extern void func_0203c99c(void *p, int a);
extern void func_0203ad58(void);
extern void func_0203ad68(void);
extern void func_0203c40c(void *p, int a);
extern void func_ov068_0226dc64(void *p, int a);

typedef struct {
    char pad_00[0x1fc];
    int unk_1FC;
} UnkStruct_0226dd34;

int func_ov068_0226dd34(UnkStruct_0226dd34 *p)
{
    func_0203caa4(p, 16, 0);
    func_0203c99c(p, 0);
    if (p->unk_1FC == 2) {
        func_0203ad58();
    } else {
        func_0203ad68();
    }
    func_0203c40c(p, 0x1c71);
    func_ov068_0226dc64(p, 0);
    return 1;
}
