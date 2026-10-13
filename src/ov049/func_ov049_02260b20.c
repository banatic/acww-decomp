/* func_ov049_02260b20 @ 0x02260b20, 0x7c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206837c(int);
extern void func_020ab670(int, int, int);
extern void func_020ab628(int, int, char *, int, char *, unsigned int, int);
extern void func_020ab5f8(int);
extern void func_02068388(int, int);
extern unsigned int data_ov049_02263298;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260b20;

typedef struct {
    const unsigned char *data;
    unsigned char count;
} List;

void func_ov049_02260b20(UnkStruct_02260b20 *obj, List *list, int c)
{
    int v = obj->unk_40;
    int handle;
    int zero = 0;
    const unsigned char *data;
    unsigned char count;
    int i;
    char buf[2];

    handle = func_0206837c(v);
    data = list->data;
    count = list->count;
    if (c != -1) {
        func_020ab670(handle, count, c);
    } else {
        func_020ab670(handle, count, -1);
    }
    for (i = 0; i < count; i++) {
        buf[0] = data[i];
        buf[1] = 6;
        func_020ab628(handle, i, buf, zero, &buf[1], data_ov049_02263298, zero);
    }
    func_020ab5f8(handle);
    func_02068388(v, 1);
}
