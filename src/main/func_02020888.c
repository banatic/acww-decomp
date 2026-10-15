/* func_02020888 @ 0x02020888, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02020888 {
    unsigned char pad_00[0x830];
    int unk_830;
} UnkStruct_02020888;

typedef struct UnkStruct_02020888_2 {
    unsigned char pad_00[0x100];
    UnkStruct_02020888 *sub;
    char buffer[0x1E];
    unsigned char byte;
} UnkStruct_02020888_2;

typedef struct UnkStruct_02020888_3 {
    char *ptr;
    unsigned char byte;
} UnkStruct_02020888_3;

typedef struct {
    int a;
    unsigned char b;
} GlobalData;

extern GlobalData data_020c8ab0;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(UnkStruct_02020888_2 *, char *, unsigned char *, int, int, int, int, int, int selected);

void func_02020888(UnkStruct_02020888_2 *obj, UnkStruct_02020888_3 *out)
{
    int val = func_020036e8(func_0208150c(obj->sub->unk_830));
    func_0202da38(obj, obj->buffer, &obj->byte, 30, val, data_020c8ab0.a, 1, 3, data_020c8ab0.b);
    out->ptr = obj->buffer;
    out->byte = obj->byte;
}
