/* func_0202a8e8 @ 0x0202a8e8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void *p);
extern void func_0200368c(void *ptr, int a, int b, int c);
extern int func_020036e8(void);
extern int data_020c8b20;

struct UnkStruct_0202a8e8 {
    char pad_00[0x830];
    void *unk_830;
};

struct UnkStruct_0202a8e8_2 {
    char pad_00[0x100];
    struct UnkStruct_0202a8e8 *inner;
};

struct Result {
    void *ptr;
    char byte;
};

void func_0202a8e8(struct UnkStruct_0202a8e8_2 *a, struct Result *b)
{
    int tmp;
    unsigned char *p;

    func_0208150c(a->inner->unk_830);
    tmp = func_020036e8();
    func_0200368c((char *) a + 0x104, 0x1e, data_020c8b20, tmp);
    p = (unsigned char *) a + 0x122;
    *p = 3;
    b->ptr = (void *) ((char *) a + 0x104);
    b->byte = *p;
}
