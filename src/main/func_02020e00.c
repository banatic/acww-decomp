/* func_02020e00 @ 0x02020e00, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02020e00 {
    unsigned char pad_00[0x830];
    int val;
} UnkStruct_02020e00;

typedef struct UnkStruct_02020e00_2 {
    unsigned char pad_00[0x100];
    UnkStruct_02020e00 *p;
    unsigned char data[0x1e];
    unsigned char b;
} UnkStruct_02020e00_2;

typedef struct UnkStruct_02020e00_3 {
    void *ptr;
    unsigned char b;
} UnkStruct_02020e00_3;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

typedef struct {
    int a;
    unsigned char b;
} UnkStruct_02020e00_4;

extern UnkStruct_02020e00_4 data_020c8a88;

void func_02020e00(UnkStruct_02020e00_2 *r5, UnkStruct_02020e00_3 *r4)
{
    int a, b, c, d, e;
    a = func_020036e8(func_0208150c(r5->p->val));
    b = data_020c8a88.a;
    c = data_020c8a88.b;
    d = 0;
    e = 0;
    func_0202da38(r5, r5->data, &r5->b, 0x1e, a, b, c, d, e);
    r4->ptr = r5->data;
    r4->b = r5->b;
}
