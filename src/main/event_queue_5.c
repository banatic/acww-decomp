/* event_queue_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203e5f4 @ 0x0203e5f4, 0x48 bytes, Thumb
 * func_0203e5c0 @ 0x0203e5c0, 0x34 bytes, Thumb
 */

struct Node {
    void *unk_00;
    struct Node *next;
    unsigned char pad_08[12];
    unsigned char unk_14;
    unsigned char unk_15;
};

struct UnkStruct_0203e5c0 {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
};

extern struct Node *data_021c72c4;            // 0x021c72c4
extern struct Node *data_021c72b8;            // 0x021c72b8
extern int (*data_020daa28[])(struct Node *); // 0x020daa28
extern int func_020e8ce0(struct Node **list_head, struct Node *node);
extern int (*data_020daa64[])(struct UnkStruct_0203e5c0 *);

void func_0203e5f4(int receiver)
{
    struct Node *node = data_021c72c4;

    while (node) {
        if (data_020daa28[node->unk_15](node)) {
            func_020e8ce0(&data_021c72c4, node);
            data_021c72b8 = node;
            node->unk_14 = 2;
            break;
        }
        node = node->next;
    }
}

void func_0203e5c0(int receiver)
{
    if ((*(struct UnkStruct_0203e5c0 * *) &data_021c72b8)->unk_14 == 2) {
        if (data_020daa64[(*(struct UnkStruct_0203e5c0 * *) &data_021c72b8)->unk_15]((*(struct UnkStruct_0203e5c0 * *) &data_021c72b8)) != 0) {
            (*(struct UnkStruct_0203e5c0 * *) &data_021c72b8)->unk_14 = 3;
        }
    }
}
