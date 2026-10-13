/* func_ov129_0229d500 @ 0x0229d500, 0x54 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207eb4(void *a, int b, int c);
extern void func_ov002_0220a63c(void *a, int b);
extern int func_ov129_0229b7ec(void *a, int b);
extern void func_ov002_0220a9e4(void *a, int b);
extern void func_ov129_0229b7cc(void *a, int b);
extern void func_ov002_02208090(void *a, int b);

struct obj_struct {
    char pad_00[0x1d4];
    int unk_1D4;
};

void func_ov129_0229d500(struct obj_struct *obj)
{
    func_ov002_02207eb4(obj, 0, 0);
    func_ov002_0220a63c(&obj->unk_1D4, 6);
    if (func_ov129_0229b7ec(obj, 4)) {
        func_ov002_0220a9e4(&obj->unk_1D4, 0x87);
    } else {
        func_ov002_0220a9e4(&obj->unk_1D4, 0x22);
    }
    func_ov129_0229b7cc(obj, 1);
    func_ov002_02208090(obj, 7);
}
