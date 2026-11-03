/* nook_clerk_3: 9 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02263e74 @ 0x02263e74, 0x4 bytes, Thumb
 * func_ov050_02263e1c @ 0x02263e1c, 0x58 bytes, Thumb
 * func_ov050_02263df8 @ 0x02263df8, 0x24 bytes, Thumb
 * func_ov050_02263dbc @ 0x02263dbc, 0x3c bytes, Thumb
 * func_ov050_02263d7c @ 0x02263d7c, 0x40 bytes, Thumb
 * func_ov050_02263d44 @ 0x02263d44, 0x38 bytes, Thumb
 * func_ov050_02263d40 @ 0x02263d40, 0x4 bytes, Thumb
 * func_ov050_02263d3c @ 0x02263d3c, 0x4 bytes, Thumb
 * func_ov050_02263cfc @ 0x02263cfc, 0x40 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} Data_020ccf94;

struct UnkStruct_02263dbc {
    char pad_00[0x8e];
    short unk_8E;
};

extern int func_0201c0e0(void *);
extern int func_0201c040(void *, int *, int *);
extern int func_020a7278(void);
extern void func_0201c054(void *, int, int, int);
extern void func_ov050_02264834(void *, int);
extern Data_020ccf94 *data_020ccf94;
extern int func_02019c6c(int a, int b, int c);
extern int func_0201c2c8(void *, int);
extern int func_020e8b4c(int, int);
extern short data_020c80f0;
extern int func_ov050_02260718(void *);
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern unsigned short data_020c80f8;
extern int func_02019e00(void *);
extern int func_02019de8(void *);

int func_ov050_02263e74(void)
{
    return 1;
}

int func_ov050_02263e1c(void *p)
{
    int a, b;
    if (func_0201c0e0(p) && (a = 4, b = 4, func_0201c040(p, &a, &b)) && a == 4 && func_020a7278()) {
        func_0201c054(p, 1, data_020ccf94->unk_64, 4);
        func_ov050_02264834(p, 13);
    }
    return 1;
}

int func_ov050_02263df8(int a)
{
    func_02019c6c(a + 0x564, 1, *(unsigned short *) ((char *) a + 0x730));
    return 1;
}

int func_ov050_02263dbc(struct UnkStruct_02263dbc *p)
{
    int a, b;
    a = func_0201c2c8(p, 4);
    b = func_020e8b4c(p->unk_8E, a);
    if (b >= data_020c80f0) {
        func_ov050_02264834(p, 0xe);
    } else {
        func_ov050_02260718(p);
    }
    return 1;
}

int func_ov050_02263d7c(int arg0)
{
    int ret = func_0201c2c8((void *) arg0, 4);
    func_02019d0c(arg0 + 0x564, 3, 1, 0, 0, 0, ret, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov050_02263d44(void *param)
{
    if (func_02019e00((char *) param + 0x564) == 3) {
        if (func_02019de8((char *) param + 0x564) != 0) {
            func_ov050_02264834(param, 0xd);
        } else {
            func_ov050_02260718(param);
        }
    }
    return 1;
}

int func_ov050_02263d40(void)
{
    return 1;
}

int func_ov050_02263d3c(void)
{
    return 1;
}

int func_ov050_02263cfc(void *p)
{
    *(unsigned char *) ((char *) p + 0x73d) = 0x32;
    func_02019d0c((int) ((char *) p + 0x564), 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
