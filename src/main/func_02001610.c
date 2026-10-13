/* func_02001610 @ 0x02001610, 0x23c bytes, Thumb, module main
 * mwccarm 1.2/base -O2,s
 */

#include "types.h"

struct Node {
    char pad_00[0x68];
    struct Node *unk_68;
    int unk_6C;
    char pad_70[0x90 - 0x70];
    int unk_90;
    int unk_94;
    int unk_98;
};
struct Root {
    char pad_00[4];
    struct Node *unk_04;
    struct Node *unk_08;
};
struct UnkStruct_02001610 {
    char pad_00[8];
    struct UnkStruct_02001610_2 *unk_08;
};
struct UnkStruct_02001610_2 {
    char pad_00[0xc];
    u16 unk_0C;
};

extern void func_020b97b4();
extern void func_020b97d4(u16 *buf, void *dst, void *v);
extern int func_020eea3c(int a);
extern int OS_GetProcMode(void);
extern void *OS_GetIrqStackStatus(void);
extern int OS_GetStackStatus(struct Node *n);

extern char *data_0213fdd0;
extern int data_0213fdd4;
extern char data_021c5914[];
extern int data_0213e7fc;
extern struct UnkStruct_02001610 *data_021fcff4;
extern u16 data_021fcfdc;
extern u8 data_021fcfd4;
extern int *data_0213fde0;
extern int data_0213fdd8;
extern int data_0213fdcc;
extern int data_0213fdec;
extern int data_0213fde8;
extern void *data_0213fde4;
extern struct Root OSi_ThreadInfo;

extern char data_020d3420[];
extern char data_020d3428[];
extern char data_020d3438[];
extern char data_020d3450[];
extern char data_020c7538[];
extern char data_020d345c[];
extern char data_020d3468[];
extern char data_020d3474[];
extern char data_020d3480[];
extern char data_020d348c[];
extern char data_020d3494[];
extern char data_020d34a4[];
extern char data_020d34b0[];
extern char data_020d34bc[];

void func_02001610(void)
{
    u16 buf[2];
    char *base;
    int n;
    int *tbl;
    unsigned int i;
    u16 id;
    struct UnkStruct_02001610 *e;
    struct UnkStruct_02001610_2 *e2;
    char *q;
    struct Node *node;
    int res;

    base = data_0213fdd0;
    buf[0] = 0xd000;
    buf[1] = 0xd000;
    func_020b97b4(buf, base + 0x40, data_020d3420, data_0213fdd4);
    func_020b97d4(buf, base, data_021c5914);

    n = data_0213e7fc;
    if (n != 0 && n < 6) {
        func_020b97b4(buf, base + 0x180, data_020d3428, n, func_020eea3c(n));
    }

    id = 0xffff;
    e = data_021fcff4;
    if (e != 0) {
        e2 = e->unk_08;
        if (e2 != 0) {
            id = e2->unk_0C;
        }
    } else {
        id = data_021fcfdc;
    }
    if (id != 0xffff) {
        func_020b97b4(buf, base + 0x1c0, data_020d3438, id, data_021fcfd4);
    }

    tbl = data_0213fde0;
    if (tbl != 0) {
        for (i = 0; i < 0x12; i++) {
            func_020b97b4(buf, base + ((i + 2) << 6) + 0x28, data_020d3450, &data_020c7538[i * 3], tbl[i]);
        }
        q = (char *) data_0213fde0 + 0x64;
        func_020b97b4(buf, base + 0x528, data_020d345c, *(int *) q);
        func_020b97b4(buf, base + 0x568, data_020d3468, *(int *) (q + 4));
    } else {
        func_020b97b4(buf, base + 0x428, data_020d3474, data_0213fdd8);
        func_020b97b4(buf, base + 0x4a8, data_020d3480, data_0213fdcc);
    }

    if (data_0213fdec != 0) {
        func_020b97b4(buf, base + 0x480, data_020d348c, data_0213fdec, data_0213fde8);
        func_020b97d4(buf, base + 0x4c0, data_0213fde4);
    }

    res = OS_GetProcMode();
    node = OSi_ThreadInfo.unk_04;
    func_020b97b4(buf, base + 0x80, data_020d3494, node->unk_6C, res);
    func_020b97b4(buf, base + 0xc0, data_020d34a4, node->unk_90, node->unk_94);

    q = (char *) OS_GetIrqStackStatus();
    if (q != 0) {
        func_020b97b4(buf, base + 0x100, data_020d34b0, q);
    } else {
        node = OSi_ThreadInfo.unk_08;
        res = 0;
        while (node != 0) {
            res = OS_GetStackStatus(node);
            if (res != 0) {
                break;
            }
            node = node->unk_68;
        }
        if (node != 0) {
            func_020b97b4(buf, base + 0x100, data_020d34bc, res, node->unk_6C, node->unk_98);
        }
    }
}
