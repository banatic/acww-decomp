/* func_ov071_02279694 @ 0x02279694, 0x3a bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(void *buffer, const void *src, int c, int val);
extern int func_0201ae8c(const void *buffer);

typedef struct {
    char pad_00[0x5c];
    char sub;
    char pad_5D[0x37];
    short unk_94;
} UnkStruct_02279694;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_02279694_2;

int func_ov071_02279694(UnkStruct_02279694 *a, UnkStruct_02279694_2 *b, int c)
{
    int ret = 0;
    int local[4];

    func_0201af58(local, &a->sub, c, a->unk_94);
    if (func_0201ae8c(local) != 1) {
        b->x = local[0];
        b->y = local[1];
        b->z = local[2];
        ret = 1;
    }
    return ret;
}
