/* func_0202ab30 @ 0x0202ab30, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int arg);
extern int func_020036e8(int arg);
extern void func_0200368c(char *buf, int len, int value, int extra);
extern int data_020c8b20;

typedef struct UnkStructT {
    char pad_00[0x830];
    int value;
} UnkStructT;

typedef struct UnkStructS {
    char pad_00[0x100];
    UnkStructT *t_ptr;
    char data[30];
    unsigned char unk_122;
} UnkStructS;

typedef struct UnkStruct_0202ab30 {
    char *ptr;
    unsigned char byte;
} UnkStruct_0202ab30;

void func_0202ab30(UnkStructS *s, UnkStruct_0202ab30 *out)
{
    int v;

    v = func_020036e8(func_0208150c(s->t_ptr->value));
    func_0200368c(s->data, 30, data_020c8b20, v);
    s->unk_122 = 2;
    out->ptr = s->data;
    out->byte = s->unk_122;
}
