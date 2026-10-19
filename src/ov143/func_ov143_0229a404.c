/* func_ov143_0229a404 @ 0x0229a404, 0x34 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA0];
    unsigned char *arr;
    char pad_A4[0x6C];
    char data[1];
} UnkStruct_0229a404;

extern void func_ov143_02299a9c(UnkStruct_0229a404 *);
extern void *func_ov002_0220a720(void *, int);
extern void func_0200467c(int command);

void func_ov143_0229a404(UnkStruct_0229a404 *obj)
{
    int i;

    func_ov143_02299a9c(obj);
    func_ov002_0220a720(obj->data, 3);
    func_0200467c(0x5a);

    for (i = 0; i < 16; i++) {
        obj->arr[i] = 0xf;
    }
}
