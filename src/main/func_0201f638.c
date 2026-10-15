/* func_0201f638 @ 0x0201f638, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *ptr);
extern int func_020036e8(int val);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern int data_020c8bd8;

struct UnkStruct_0201f638 {
    char pad_00[0x100];
    void *unk_100;
    char buffer[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_0201f638_2 {
    void *ptr;
    unsigned char byte;
};

void func_0201f638(struct UnkStruct_0201f638 *p1, struct UnkStruct_0201f638_2 *p2)
{
    void *ptr = *((void **) ((char *) p1->unk_100 + 0x830));
    int result = func_020036e8(func_0208150c(ptr));
    func_0202da38(p1, p1->buffer, &p1->unk_122, 0x1e, result, *(int *) &data_020c8bd8, 1, 13,
                  ((unsigned char *) &data_020c8bd8)[4]);
    p2->ptr = p1->buffer;
    p2->byte = p1->unk_122;
}
