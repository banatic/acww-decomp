/* func_02016764 @ 0x02016764, 0x120 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xec];
    unsigned char unk_EC[0x2a0 - 0xec];
    unsigned char unk_2A0[0x2ac - 0x2a0];
    unsigned char unk_2AC[0x418 - 0x2ac];
    unsigned char unk_418[4];
} UnkStruct_02016764;

extern int func_020168ac(void *a0, int a2, void *p);
extern int func_0201b380(void *p);
extern int func_02016884(void *a0, int x, void *p);
extern void *func_020168e4(void *a0, int v, int idx);
extern void func_020542c0(void *p, void *item, int a3, int a5, int a6, int mode, int z);
extern void func_020161e4(void *a0, UnkStruct_02016764 *obj);
extern int func_020164a0(void *a0, int z);
extern int func_0201a7b4(void *p);
extern void func_0201a090(void *p, int a, int b, int c);
extern void func_020547b0(void *p, void *item, int a3, int a5, int a6, int mode, int z1, int z2);
extern void func_02054240(void *p, void *item, int a3, int a5, int a6, int mode, int z1, int z2);

void func_02016764(void *a0, UnkStruct_02016764 *obj, int a2, int a3, int a5, int a6, unsigned short a7, int a8)
{
    int mode;
    int x;
    void *item;
    int t4;
    int t3;

    if (a7 == 0) {
        switch (a5) {
            case 2:
            case 3:
                mode = 0xffff;
                goto have_mode;
            default:
                break;
        }
    }
    mode = a7;
have_mode:
    if (a8 < 0 || a8 >= 3) {
        return;
    }
    switch (a8) {
        case 0:
            x = func_020168ac(a0, a2, obj->unk_2A0);
            if (x != func_0201b380(obj->unk_2A0) || func_02016884(a0, x, obj->unk_2A0) == 0) {
                item = func_020168e4(a0, x, a8);
                if (item != 0) {
                    func_020542c0(obj->unk_EC, item, a3, a5, a6, mode, 0);
                }
            }
            func_020161e4(a0, obj);
            t4 = func_020164a0(a0, 0);
            t3 = func_0201a7b4(obj->unk_418);
            func_0201a090(obj->unk_2AC, t4, a5, t3);
            break;
        case 1:
            item = func_020168e4(a0, a2, a8);
            if (item != 0) {
                func_020547b0(obj->unk_EC, item, a3, a5, a6, mode, 0, 0);
            }
            break;
        case 2:
            item = func_020168e4(a0, a2, a8);
            if (item != 0) {
                func_02054240(obj->unk_EC, item, a3, a5, a6, mode, 0, 0);
            }
            break;
    }
}
