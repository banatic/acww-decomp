/* func_0201ea44 @ 0x0201ea44, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201ea44;
extern void func_0202da38(struct UnkStruct_0201ea44 *a, unsigned char *b, unsigned char *c, int d, int e, unsigned int f,
                          int g, int h, int i);
extern int func_0208150c(int);
extern int func_020036e8(int);

struct UnkStruct_0201ea44_2 {
    unsigned char pad_00[0x830];
    unsigned int val;
};
struct UnkStruct_0201ea44 {
    unsigned char pad_00[0x100];
    struct UnkStruct_0201ea44_2 *ptr;
    unsigned char arr[30];
    unsigned char byte;
};
struct UnkStruct_0201ea44_4 {
    unsigned char *ptr;
    unsigned char byte;
};
struct UnkStruct_0201ea44_3 {
    unsigned int word;
    unsigned char byte;
};
extern struct UnkStruct_0201ea44_3 data_020c8d60;

void func_0201ea44(struct UnkStruct_0201ea44 *a, struct UnkStruct_0201ea44_4 *b)
{
    unsigned int v;
    int x;
    v = a->ptr->val;
    x = func_020036e8(func_0208150c(v));
    func_0202da38(a, a->arr, &a->byte, 30, x, data_020c8d60.word, 1, 0, data_020c8d60.byte);
    b->ptr = a->arr;
    b->byte = a->byte;
}
