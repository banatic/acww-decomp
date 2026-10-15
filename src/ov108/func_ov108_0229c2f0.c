/* func_ov108_0229c2f0 @ 0x0229c2f0, 0x68 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov108_0229c2bc(void *obj, int x);
extern int func_ov108_0229cd70(void *obj, unsigned char x);
extern void func_ov108_0229c358(void *obj, void *arg, int flag);
extern int func_ov002_022088cc(int a);

typedef struct {
    unsigned char pad_00[0x2b0];
    unsigned char unk_2B0;
} UnkStruct_0229c2f0;

int func_ov108_0229c2f0(UnkStruct_0229c2f0 *obj, int a, int b)
{
    unsigned char init = obj->unk_2B0;
    func_ov108_0229c2bc(obj, 0x30);
    if (a == 0) {
        return 0;
    }
    if (func_ov108_0229cd70(obj, obj->unk_2B0) != 0) {
        func_ov108_0229c358(obj, (void *) a, b);
    } else {
        if (obj->unk_2B0 == 0x15) {
            if (func_ov002_022088cc(a) != 0) {
                obj->unk_2B0 = 0x13;
            }
        }
    }
    if (init != obj->unk_2B0) {
        return 1;
    } else {
        return 0;
    }
}
