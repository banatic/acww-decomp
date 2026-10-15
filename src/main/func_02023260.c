/* func_02023260 @ 0x02023260, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void *func_02099640(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern void func_0209af04(void *);

typedef struct {
    char pad_00[0x100];
    void *ptr;
    char arr[0x1E];
    unsigned char byte;
} UnkStruct_02023260;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02023260_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02023260_3;

extern UnkStruct_02023260_3 data_020c8e08;

void func_02023260(UnkStruct_02023260 *self, UnkStruct_02023260_2 *out)
{
    int a, b, c, d, e, x;
    void *p;

    p = func_02099640((int) func_020984e8());
    x = *(int *) ((char *) self->ptr + 0x830);
    a = func_020036e8(func_0208150c(x));
    b = data_020c8e08.unk_00;
    c = data_020c8e08.unk_04;
    d = 0;
    e = 0;
    func_0202da38(self, self->arr, &self->byte, 30, a, b, c, d, e);
    out->ptr = self->arr;
    out->byte = self->byte;
    func_0209af04((char *) p + 0xa4);
}
