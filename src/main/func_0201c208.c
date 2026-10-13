/* func_0201c208 @ 0x0201c208, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(void *dest, void *src, int param, int size);
extern int func_0201ae8c(void *data);

typedef struct {
    char pad_00[0x94];
    signed short unk_94;
} UnkStruct_0201c208;

int func_0201c208(UnkStruct_0201c208 *in, int *out, int arg2)
{
    int local[3];
    int ret = 0;
    char *p;

    p = (char *) in;
    p += 0x5c;
    func_0201af58(local, p, arg2, in->unk_94);
    if (func_0201ae8c(local) != 1) {
        out[0] = local[0];
        out[1] = local[1];
        out[2] = local[2];
        ret = 1;
    }
    return ret;
}
