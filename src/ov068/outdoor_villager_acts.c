/* outdoor_villager_acts: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022674b0 @ 0x022674b0, 0xa8 bytes, Thumb
 * func_ov068_02267468 @ 0x02267468, 0x48 bytes, Thumb
 * func_ov068_02267400 @ 0x02267400, 0x68 bytes, Thumb
 */

typedef struct {
    int a;
} UnkStruct_02267468;

typedef struct {
    char pad_00[0x564];
    UnkStruct_02267468 sub;
} Src;

typedef struct {
    char pad_00[0x1c];
    unsigned char flag;
    char pad_1D[3];
    int value;
} UnkStruct_02267468_2;

extern void func_ov068_0226cfd4(void *);
extern void func_0201651c(void *, int);
extern void func_ov068_02266c34(void *, void *, int, int, int, void *, int, int, int);
extern void func_0202e188(void *);
extern void func_02013c0c(void *);
extern int func_0201c2c8(void *, int);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_0201cbbc(void *);
extern unsigned char data_021fbee8[];
extern unsigned int data_020c814c;
extern unsigned short data_020c80f8;
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c90(void *, int, int, unsigned short);
extern int func_02019df8(char *);
extern int func_ov068_0226c0a4(void *);
extern int func_02019c6c(char *, int, unsigned short);
extern void func_ov068_0226cce8(void *, void *, int);

void func_ov068_022674b0(char *p1, char *p2)
{
    int res;

    func_ov068_0226cfd4(p2);
    func_0201651c((char *) p2 + 0x334, 0);
    func_ov068_02266c34((char *) p2 + 0x898, p2, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_0202e188(p2);
    func_02013c0c((char *) p2 + 0x558);
    res = func_0201c2c8(p2, 4);
    func_02019d0c((char *) p2 + 0x564, 3, 1, 0, 0, 0, res, 0, 0, data_020c80f8, 0);
    func_0201cbbc((char *) p2 + 0x83c);
    p1[0x1c] = 0;
    p1[0xe0] = 1;
}

void func_ov068_02267468(UnkStruct_02267468_2 *out, Src *src)
{
    if (func_02019e00(&src->sub) != 3) {
        return;
    }
    if (func_02019de8(&src->sub) == 0) {
        return;
    }
    func_02019c90(&src->sub, 1, 0x1a, data_020c80f8);
    out->value = 0x14;
    out->flag = 1;
}

void func_ov068_02267400(void *param0, void *param1)
{
    if (func_02019e00((void *) (((char *) param1) + 0x564)) != 8) {
        return;
    }
    if (func_02019df8(((char *) param1) + 0x564) != 0x1a) {
        return;
    }
    if (*(unsigned int *) (((char *) param0) + 0x20) != 0) {
        return;
    }
    if (func_ov068_0226c0a4(param0) != 0) {
        return;
    }
    if (((*(unsigned int *) (((char *) param1) + 0x190) << 4) >> 16) != 0) {
        return;
    }
    func_02019c6c(((char *) param1) + 0x564, 1, data_020c80f8);
    func_ov068_0226cce8(param0, param1, 0);
}
