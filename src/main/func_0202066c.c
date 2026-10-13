/* func_0202066c @ 0x0202066c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct InnerPtr {
    char pad_00[0x830];
    void *value;
} InnerPtr;

typedef struct UnkStruct_0202066c {
    char pad_00[0x100];
    InnerPtr *ptr;
    char data[0x1E];
    unsigned char byte;
} UnkStruct_0202066c;

typedef struct Output {
    void *ptr;
    unsigned char byte;
} Output;

extern void func_0208150c(void *arg);
extern int func_020036e8(void);
extern int data_020c8ab0;
extern void func_0202da38(UnkStruct_0202066c *a, char *data, unsigned char *byte, int size, int v0, int v1, int v2, int v3,
                          int v4);

void func_0202066c(UnkStruct_0202066c *a, Output *b)
{
    func_0208150c(a->ptr->value);
    func_0202da38(a, a->data, &a->byte, 30, func_020036e8(), data_020c8ab0, 1, 6, 2);
    b->ptr = a->data;
    b->byte = a->byte;
}
