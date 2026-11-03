/* held_item_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205eb8c @ 0x0205eb8c, 0x28 bytes, Thumb
 * func_0205eae0 @ 0x0205eae0, 0xac bytes, Thumb
 * func_0205eac4 @ 0x0205eac4, 0x1c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x10];
    int unk_10;
} Entry;

typedef struct {
    char pad_00[0x9c];
    Entry entry;
} Record;

extern void func_0205ebb4(void *);
extern void func_0205ec50(void *a, int b, int c, void *d, int e, int f);
extern u8 data_021ca16c[];
extern void func_0205f1bc(u8 *, int, int, int, int);
extern void func_0205f15c(u8 *, int, int, int);
extern void func_0206026c(u8 *, int);
extern Record *func_0205f130(Record *base, unsigned char index);

void func_0205eb8c(void *a, void *b, int c)
{
    unsigned char d;
    void *e;
    int f;

    d = *(unsigned char *) a;
    func_0205ebb4(a);
    f = c;
    e = b;
    func_0205ec50(a, d, 0, e, f, 0);
}

void func_0205eae0(u8 *a, int b, int c, int d)
{
    func_0205f1bc(data_021ca16c, a[0], b, c, d);
    switch (b) {
        case 0x13:
            func_0206026c(a + 0x28, 1);
            break;
        case 0x15:
            func_0206026c(a + 0x28, 3);
            break;
        case 0x16:
            func_0206026c(a + 0x28, 2);
            break;
        case 0x18:
            func_0206026c(a + 0x28, 6);
            break;
        case 0x19:
        case 0x1b:
            func_0206026c(a + 0x28, 7);
            break;
        case 0x1a:
            func_0206026c(a + 0x28, 8);
            break;
        case 0x28:
            func_0205f15c(data_021ca16c, a[0], 1, d);
            break;
    }
}

void func_0205eac4(unsigned char *key, int value)
{
    Entry *e;

    e = &func_0205f130(((Record *) data_021ca16c), *key)->entry;
    e->unk_10 = value;
}
