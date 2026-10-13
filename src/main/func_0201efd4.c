/* func_0201efd4 @ 0x0201efd4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern int data_020c8ba0;

struct UnkStruct_0201efd4 {
    unsigned char pad_00[0x100];
    void *ptr;
    unsigned char data[0x1e];
    unsigned char ch;
};

struct UnkStruct_0201efd4_2 {
    void *ptr;
    unsigned char byte;
};

void func_0201efd4(struct UnkStruct_0201efd4 *p, struct UnkStruct_0201efd4_2 *out)
{
    func_0202da38(p, p->data, &p->ch, 30, func_020036e8(func_0208150c(*(int *) ((char *) p->ptr + 0x830))), data_020c8ba0, 1,
                  0x11, 2);
    out->ptr = p->data;
    out->byte = p->ch;
}
