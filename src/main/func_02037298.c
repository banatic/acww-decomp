/* func_02037298 @ 0x02037298, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02037298 {
    char unk_00[0x10];
    unsigned char flag;
};

extern void func_020371c8(struct UnkStruct_02037298 *obj);
extern void func_0203710c(struct UnkStruct_02037298 *obj);

void func_02037298(struct UnkStruct_02037298 *obj)
{
    if (obj->flag != 0) {
        func_020371c8(obj);
        func_0203710c(obj);
    }
}
