/* func_02028550 @ 0x02028550, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int scale, int, int);
extern int data_020c8ab8;

typedef struct {
    char pad_00[0x100];
    void *unk_100;
} UnkStruct_02028550;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_02028550_2;

void func_02028550(UnkStruct_02028550 *a, UnkStruct_02028550_2 *b)
{
    int r = func_020036e8(func_0208150c(*(int *) ((char *) a->unk_100 + 0x830)));
    func_0202da38(a, (char *) a + 0x104, (char *) a + 0x122, 30, r, data_020c8ab8, ((unsigned char *) &data_020c8ab8)[4], 0,
                  0);
    b->unk_00 = (char *) a + 0x104;
    b->unk_04 = *(unsigned char *) ((char *) a + 0x122);
}
