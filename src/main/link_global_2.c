/* link_global_2: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7450 @ 0x020a7450, 0x4 bytes, Thumb
 * func_020a744c @ 0x020a744c, 0x4 bytes, Thumb
 * func_020a7448 @ 0x020a7448, 0x2 bytes, Thumb
 * func_020a7408 @ 0x020a7408, 0x40 bytes, Thumb
 * func_020a7394 @ 0x020a7394, 0x74 bytes, Thumb
 * func_020a7380 @ 0x020a7380, 0x14 bytes, Thumb
 * func_020a7360 @ 0x020a7360, 0x20 bytes, Thumb
 * func_020a7330 @ 0x020a7330, 0x30 bytes, Thumb
 * func_020a7300 @ 0x020a7300, 0x30 bytes, Thumb
 * func_020a72d0 @ 0x020a72d0, 0x30 bytes, Thumb
 * func_020a7278 @ 0x020a7278, 0x58 bytes, Thumb
 * func_020a7258 @ 0x020a7258, 0x20 bytes, Thumb
 * func_020a71ec @ 0x020a71ec, 0x6c bytes, Thumb
 * func_020a70ec @ 0x020a70ec, 0x100 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y;
} Pair;

typedef struct {
    int unk_00;
} Entry;

typedef struct {
    char data[8];
} Entry_020a7360;

struct triple {
    unsigned char a, b, c;
};

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020a7278;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
} TableEntry;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} Struct020ccf94;

typedef struct {
    u8 a, b, c;
} UnkStruct_020a70ec;

struct GB {
    u8 pad_00[0x64];
    int lim;
};

extern void func_020a7704(int *p, int *a, int *b);
extern void func_020a7710(int *p, int a, int b);
extern Pair data_021f432c[];
extern char data_021f4320[];
extern int data_020ccf94;
extern void func_020a774c(char *base, unsigned char v0, unsigned char v1, unsigned char v2);
extern void func_02073598(int value);
extern Entry data_021f434c[];
extern void func_020a76e0(Entry *entry, int arg);
extern Entry_020a7360 data_021f435c[];
extern void func_020a7794(void *ptr, int a, int b, int c, int d);
extern void func_020a7738(const unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d);
extern int func_020a6684(TableEntry *data_021f4320);
extern int func_020a668c(TableEntry *data_021f4320);
extern int func_02073dd4(int a, int b);
extern int func_020a627c(UnkStruct_020a70ec *);

int func_020a7450(void)
{
    return 0;
}

int func_020a744c(void)
{
    return 0;
}

void func_020a7448(void) {}

void func_020a7408(int p0, int p1)
{
    Pair *base = data_021f432c;
    int i;
    for (i = 3; i >= 0; i--) {
        int b, a;
        func_020a7704((int *) base, &a, &b);
        if (a >= 4) {
            func_020a7710((int *) base, p0, p1);
            break;
        }
        base++;
    }
}

void func_020a7394(int a, int b, int c, int d, int mask)
{
    unsigned char local[3];
    char *base;

    base = data_021f4320 + 3 * a;
    func_020a7738((const unsigned char *) base, &local[0], &local[1], &local[2]);
    if ((mask & 1) != 0) {
        local[0] = (unsigned char) b;
    }
    if ((mask & 2) != 0) {
        local[1] = (unsigned char) c;
    }
    if ((mask & 4) != 0) {
        local[2] = (unsigned char) d;
    }
    func_020a774c(base, local[0], local[1], local[2]);
    func_02073598(data_020ccf94);
}

void func_020a7380(int index, int arg)
{
    func_020a76e0(&data_021f434c[index], arg);
}

void func_020a7360(int index, int a, int b, int c, int d)
{
    func_020a7794(&data_021f435c[index], a, b, c, d);
}

int func_020a7330(int arg0)
{
    unsigned char buffer[3];
    if (arg0 < 4) {
        func_020a7738(((unsigned char *) data_021f4320) + 3 * arg0, &buffer[0], &buffer[1], &buffer[2]);
        return buffer[0];
    }
    return 0x3f;
}

unsigned char func_020a7300(int n)
{
    if (n < 4) {
        unsigned char local[3];
        func_020a7738((const unsigned char *) (&((struct triple *) data_021f4320)[n]), &local[0], &local[1], &local[2]);
        return local[1];
    }
    return 1;
}

int func_020a72d0(int param)
{
    unsigned char tmp[3];
    int result;
    if (param < 4) {
        func_020a7738(&((unsigned char *) data_021f4320)[param * 3], tmp, tmp + 1, tmp + 2);
        result = tmp[2];
    } else {
        result = 0;
    }
    return result;
}

int func_020a7278(void)
{
    int idx;
    unsigned char local[3];

    idx = (*(UnkStruct_020a7278 * *) &data_020ccf94)->unk_64;
    if (idx >= 4) {
        return 1;
    }

    func_020a7738((const unsigned char *) (&((TableEntry *) data_021f4320)[idx]), &local[0], &local[1], &local[2]);

    if (local[2] == 0) {
        return local[1];
    }

    if (func_020a6684(((TableEntry *) data_021f4320)) < 7) {
        return local[1];
    }

    return func_020a668c(((TableEntry *) data_021f4320));
}

int func_020a7258(void)
{
    if ((*(Struct020ccf94 * *) &data_020ccf94)->unk_64 < 4) {
        return func_020a72d0((*(Struct020ccf94 * *) &data_020ccf94)->unk_64);
    } else {
        return 1;
    }
}

int func_020a71ec(int param)
{
    int n = 3;
    int i;
    int result = 4;
    int x;
    unsigned char arr[3];
    i = n;
    x = data_020ccf94;
    while (i >= 0) {
        if (func_02073dd4(x, i) != 0) {
            func_020a7738(&((unsigned char *) data_021f4320)[n * i], &arr[0], &arr[1], &arr[2]);
            if (arr[0] == param && arr[1] != 0 && arr[2] == 0) {
                result = i;
                break;
            }
        }
        i--;
    }
    return result;
}

int func_020a70ec(int a, int b, int c, u8 *d)
{
    int lim;
    u8 v0, v1, v2, v3, v4, v5;
    int t;

    lim = (*(struct GB * *) &data_020ccf94)->lim;
    *d = 0;
    if (b == 0) {
        if (a == 0) {
            return a;
        }
    } else if (b == 0) {
        if (a == 0) {
            return a;
        }
    } else if (b == 1) {
        if (a == 1) {
            return a;
        }
    } else if (b == 2) {
        if (a == 2) {
            return a;
        }
    } else if (b == 3) {
        if (a == 3) {
            return a;
        }
    } else if (b == 4) {
        if (a != lim) {
            return a;
        }
    } else if (b == 5) {
        if (a != 0) {
            return a;
        }
    } else if (b == 6) {
        t = func_020a71ec(c);
        if (t < 4) {
            if (t == a) {
                return a;
            }
        } else {
            func_020a7738((const unsigned char *) (&((UnkStruct_020a70ec *) data_021f4320)[a]), (unsigned char *) (&v0), (unsigned char *) (&v1), (unsigned char *) (&v2));
            if (v0 == c && v1 != 0 && v2 != 0) {
                *d = 1;
            }
        }
    } else if (b == 7) {
        func_020a7738((const unsigned char *) (&((UnkStruct_020a70ec *) data_021f4320)[a]), (unsigned char *) (&v3), (unsigned char *) (&v4), (unsigned char *) (&v5));
        if (v3 == c) {
            if (v4 == 0 && v5 == 0 && a != lim) {
                return a;
            }
        } else {
            t = func_020a627c(((UnkStruct_020a70ec *) data_021f4320));
            if (t < 4 && t == a && a != lim) {
                return a;
            }
        }
    }
    return 4;
}
