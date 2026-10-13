/* func_ov128_0229bd68 @ 0x0229bd68, 0x6c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x110];
    char unk_110;
    char pad_111[0x2d6c - 0x111];
    unsigned char unk_2D6C;
} Obj_t;

extern int func_ov128_0229bd38(Obj_t *obj);
extern int func_ov128_0229bd08(Obj_t *obj);
extern int func_ov128_0229b7ec(Obj_t *obj, int a);
extern void func_ov128_0229bc30(Obj_t *obj);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);

void func_ov128_0229bd68(Obj_t *obj)
{
    int a = func_ov128_0229bd38(obj);
    int b = func_ov128_0229bd08(obj);
    func_ov002_0220a0b4(&obj->unk_110, a, b);
    if (func_ov128_0229b7ec(obj, 2)) {
        func_ov002_0220a374(&obj->unk_110, 1);
    } else {
        if (obj->unk_2D6C == 3) {
            func_ov002_0220a374(&obj->unk_110, 0xD);
        } else {
            func_ov002_0220a374(&obj->unk_110, 1);
        }
    }
    func_ov128_0229bc30(obj);
}
