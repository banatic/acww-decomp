/* func_02027c64 @ 0x02027c64, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct InnerStruct {
    unsigned char pad_00[0x830];
    int value;
} InnerStruct;

typedef struct OuterStruct {
    unsigned char pad_00[0x100];
    InnerStruct *inner;
} OuterStruct;

typedef struct GlobalData {
    unsigned int word;
    unsigned char byte;
} GlobalData;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern GlobalData data_020c8980;

void func_02027c64(OuterStruct *p1, char *p2)
{
    int temp = func_020036e8(func_0208150c(p1->inner->value));
    func_0202da38(p1, (char *) p1 + 0x104, (char *) p1 + 0x122, 0x1e, temp, data_020c8980.word, data_020c8980.byte, 0, 0);
    *(char **) p2 = (char *) p1 + 0x104;
    *(p2 + 4) = *((unsigned char *) p1 + 0x122);
}
