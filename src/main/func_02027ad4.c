/* func_02027ad4 @ 0x02027ad4, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202d9c4(void);
extern int func_0209bc40(void);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);

typedef struct {
    int value;
    unsigned char byte;
} GlobalData;

extern GlobalData data_020c8e48;
extern GlobalData data_020c8e40;

typedef struct {
    char *buffer;
    unsigned char flag;
} UnkStruct_02027ad4;

void func_02027ad4(char *self, UnkStruct_02027ad4 *out)
{
    GlobalData *r4 = 0;
    int x;
    int a, v, b;

    func_0202d9c4();
    x = func_0209bc40();

    switch (x) {
        case 0xa:
            r4 = &data_020c8e48;
            break;
        case 0x13:
            r4 = &data_020c8e40;
            break;
        default:
            break;
    }

    if (r4 != 0) {
        a = func_020036e8(func_0208150c(*(int *) (*(char **) (self + 0x100) + 0x830)));
        v = r4->value;
        b = r4->byte;
        func_0202da38(self, self + 0x104, self + 0x122, 30, a, v, b, 0, 0);
    }

    out->buffer = self + 0x104;
    out->flag = *(unsigned char *) (self + 0x122);
}
