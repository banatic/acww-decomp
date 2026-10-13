/* func_ov078_02279460 @ 0x02279460, 0x3a bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(void *, void *, int, int);
extern int func_0201ae8c(void *);

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_02279460;
typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_02279460_2;

int func_ov078_02279460(void *p, UnkStruct_02279460_2 *out, int arg2)
{
    int result = 0;
    UnkStruct_02279460 local;

    func_0201af58(&local, (char *) p + 0x5c, arg2, *(short *) ((char *) p + 0x94));
    if (func_0201ae8c(&local) != 1) {
        out->x = local.x;
        out->y = local.y;
        out->z = local.z;
        result = 1;
    }
    return result;
}
