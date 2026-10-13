/* func_0203680c @ 0x0203680c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Object {
    unsigned char pad_00[0xF];
    unsigned char flag;
};

extern void func_0203668c(struct Object *obj);
extern void func_02036584(struct Object *obj);

void func_0203680c(struct Object *obj)
{
    if (obj->flag) {
        func_0203668c(obj);
        func_02036584(obj);
    }
}
