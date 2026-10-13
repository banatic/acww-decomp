/* func_02022d84 @ 0x02022d84, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(int);
extern int func_020036e8(void);
extern void func_0202da38(void *, char *, char *, int, int, int, int, int, int);

typedef struct {
    char pad_00[0x100];
    void *ptr;
    char arr1[0x1e];
    char arr2;
} UnkStruct_02022d84;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02022d84_2;
extern UnkStruct_02022d84_2 data_020c8a08;

int func_02022d84(UnkStruct_02022d84 *a)
{
    func_0208150c(*(int *) ((char *) a->ptr + 0x830));
    func_0202da38(a, a->arr1, &a->arr2, 0x1e, func_020036e8(), data_020c8a08.unk_00, data_020c8a08.unk_04, 0, 0);
    return 1;
}
