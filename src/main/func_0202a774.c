/* func_0202a774 @ 0x0202a774, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200368c(void *a, int b, int c, int d);
extern int func_020036e8(int);
extern int func_0208150c(int);
extern int data_020c8b20;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104;
    char pad_105[0x122 - 0x104 - 1];
    unsigned char unk_122;
} UnkStruct_0202a774;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0202a774_2;

void func_0202a774(UnkStruct_0202a774 *p0, UnkStruct_0202a774_2 *p1)
{
    unsigned char *p = &p0->unk_122;
    int result = func_020036e8(func_0208150c(*((int *) ((char *) p0->unk_100 + 0x830))));

    func_0200368c(&p0->unk_104, 30, data_020c8b20, result);

    *p = 4;
    p1->ptr = &p0->unk_104;
    p1->byte = *p;
}
