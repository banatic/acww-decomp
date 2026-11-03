/* villager_talk_part_8: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02027cc8 @ 0x02027cc8, 0x70 bytes, Thumb
 * func_02027c64 @ 0x02027c64, 0x64 bytes, Thumb
 * func_02027c58 @ 0x02027c58, 0xc bytes, Thumb
 */

#define Predicate_02027d38 ((int (*)(unsigned short *, int)) func_02027d38)

struct DWord {
    unsigned int low;
    unsigned int high;
};

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

extern int func_0202d9c4(void *p);
extern int func_0209bc40(int v);
extern unsigned short func_02027d38(unsigned short *, int);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(void *p, int val);
extern void func_020157c8(void *p, int a, int b);
extern void func_0202dbf0(void *p, struct DWord data);
extern const struct DWord data_020d8dc8;
extern const struct DWord data_020d8e08;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern GlobalData data_020c8980;

void func_02027cc8(void *arg)
{
    int id = func_0209bc40(func_0202d9c4(arg));
    switch (id) {
        case 0x0a:
            func_020157d4(arg, Predicate_02027d38, 13, 0);
            func_02015828(arg, 0);
            func_0202dbf0(arg, data_020d8dc8);
            break;
        case 0x13:
            func_020157c8(arg, 0x28, 1);
            func_02015828(arg, 2);
            func_0202dbf0(arg, data_020d8e08);
            break;
        default:
            func_02015828(arg, 7);
            break;
    }
}

void func_02027c64(OuterStruct *p1, char *p2)
{
    int temp = func_020036e8(func_0208150c(p1->inner->value));
    func_0202da38(p1, (char *) p1 + 0x104, (char *) p1 + 0x122, 0x1e, temp, data_020c8980.word, data_020c8980.byte, 0, 0);
    *(char **) p2 = (char *) p1 + 0x104;
    *(p2 + 4) = *((unsigned char *) p1 + 0x122);
}

// placeholder, not used
void func_02027c58(void *r0)
{
    unsigned int *r1;
    r1 = *(unsigned int **) ((char *) r0 + 0x40);
    if (r1 != 0) {
        *((unsigned int *) r1 + 2) = 1;
    }
}
