/* func_020935fc @ 0x020935fc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094bcc(void *arg, int a, int b);

typedef struct Node Node;
struct Node {
    Node *next;               // 0x00
    unsigned char pad0[0x20]; // 0x04 - 0x23
    unsigned short unk_24;    // 0x24
    unsigned short unk_26;    // 0x26
};

typedef struct UnkStruct_020935fc {
    unsigned char pad0[0x8]; // 0x00 - 0x07
    Node *head;              // 0x08
} UnkStruct_020935fc;

typedef struct UnkStruct_020935fc_2 {
    unsigned char pad0[0xC];   // 0x00 - 0x0B
    UnkStruct_020935fc *inner; // 0x0C
} UnkStruct_020935fc_2;

int func_020935fc(UnkStruct_020935fc_2 *arg)
{
    Node *node;
    if (func_02094bcc(arg, 0, 0) == 0) {
        node = arg->inner->head;
        while (node) {
            node->unk_26 = node->unk_24;
            node = node->next;
        }
        return 0;
    }
    return 1;
}
