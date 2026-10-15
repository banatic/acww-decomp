/* func_020276dc @ 0x020276dc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, char *, unsigned char *, int, int, int offset, int, int, int);

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_020276dc;

typedef struct {
    void *ptr;
    unsigned char c;
} UnkStruct_020276dc_2;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} GlobalData;

extern GlobalData data_020c8e20;

void func_020276dc(UnkStruct_020276dc *p1, UnkStruct_020276dc_2 *p2)
{
    func_0202da38(p1, p1->unk_104, &p1->unk_122, 30, func_020036e8(func_0208150c(*(int *) ((char *) p1->unk_100 + 0x830))),
                  data_020c8e20.unk_00, data_020c8e20.unk_04, 0, 0);
    p2->ptr = p1->unk_104;
    p2->c = p1->unk_122;
}
