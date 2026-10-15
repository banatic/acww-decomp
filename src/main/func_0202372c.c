/* func_0202372c @ 0x0202372c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

extern struct {
    int a;
    unsigned char b;
} data_020c89b8;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char pad_104[0x122 - 0x104];
    unsigned char unk_122;
} UnkStruct_0202372c;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0202372c_2;

void func_0202372c(UnkStruct_0202372c *p, UnkStruct_0202372c_2 *out)
{
    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 30,
                  func_020036e8(func_0208150c(*(int *) ((char *) p->unk_100 + 0x830))), data_020c89b8.a, data_020c89b8.b, 0,
                  0);

    out->ptr = (char *) p + 0x104;
    out->byte = p->unk_122;
}
