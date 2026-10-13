/* func_02074904 @ 0x02074904, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Object;
struct Object {
    char pad_00[0x64];
    int unk_64;
};
extern struct Object *data_020ccf94;
extern int func_02073dd4(struct Object *p, int field);
extern int func_02073d70(struct Object *p);
extern void func_020734d0(struct Object *p);
extern void func_0207342c(struct Object *p);
extern void func_020739d0(struct Object *p);

void func_02074904(int flag)
{
    struct Object *p;
    if (flag != 0) {
        return;
    }
    p = data_020ccf94;
    if (func_02073dd4(p, p->unk_64) == 0) {
        return;
    }
    if (func_02073d70(p) == 0) {
        return;
    }
    p = data_020ccf94;
    func_020734d0(p);
    func_0207342c(p);
    func_020739d0(p);
}
