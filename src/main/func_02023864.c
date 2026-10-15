/* func_02023864 @ 0x02023864, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned int arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *p0, void *p104, void *p122, int n, int x, int offset, int scale, int one, int selected);

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} GlobalType;
extern GlobalType data_020c8aa8;

typedef struct UnkStruct_02023864 {
    char pad_00[0x100];
    void *unk_100;
    char pad_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02023864;

typedef struct OutType {
    void *ptr;
    unsigned char unk_04;
} OutType;

void func_02023864(UnkStruct_02023864 *p0, OutType *out)
{
    unsigned int b = data_020c8aa8.unk_04;
    func_0202da38(p0, (char *) p0 + 0x104, (char *) p0 + 0x122, 0x1e,
                  func_020036e8(func_0208150c(*(unsigned int *) ((char *) p0->unk_100 + 0x830))), data_020c8aa8.unk_00, b, 1,
                  b);
    out->ptr = (char *) p0 + 0x104;
    out->unk_04 = p0->unk_122;
}
