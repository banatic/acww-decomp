/* func_0208d650 @ 0x0208d650, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020d0a64[];
extern void func_02051648(void *);
extern void func_02051694(void *);

typedef struct UnkStruct_0208d650 {
    char pad_00[0x10];
    char *ptr;
} UnkStruct_0208d650;

typedef struct UnkStruct_0208d650_2 {
    char pad_00[0x34];
    UnkStruct_0208d650 *inner;
    char pad_38[0x13];
    unsigned char flag1;
    char pad_4C[0x17];
    unsigned char flag2;
} UnkStruct_0208d650_2;

void func_0208d650(UnkStruct_0208d650_2 *p)
{
    if (p->inner != 0 && p->flag1 != 0) {
        int flag;
        p->flag1 = 0;
        flag = 0;
        if (p->flag2 >= 12) {
            flag = 1;
        }
        p->inner->ptr = data_020d0a64 + 6 * flag;
        func_02051648(p->inner);
        func_02051694(p->inner);
    }
}
