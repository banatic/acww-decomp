/* func_02091744 @ 0x02091744, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_020914dc(void *entry);

struct Node {
    struct Node *next;
    char pad[0x1c];
    unsigned short unk_20;
};

struct UnkStruct_02091744 {
    char pad[8];
    struct Node *head;
};

struct UnkStruct_02091744_2 {
    char pad[0xc];
    struct UnkStruct_02091744 *sub;
};

struct Entry {
    char pad[0xc];
    short unk_0C;
    short unk_0E;
    char pad_10[4];
    int unk_14;
    char pad_18[4];
};

extern struct Entry data_021d52d8[];

int func_02091744(struct UnkStruct_02091744_2 *self)
{
    unsigned char buf[4];
    unsigned char *src;
    unsigned char *dst;
    int i;
    int result;
    struct Entry *entry;

    src = (unsigned char *) self + 4;
    dst = buf;
    i = 4;
    do {
        *dst++ = *src++;
    } while (--i != 0);

    entry = &data_021d52d8[buf[0]];
    result = 0;
    if (entry->unk_14 != -1 && entry->unk_0E != 0) {
        struct Node *node = self->sub->head;
        int val = 0x30d4;
        if (entry->unk_0C < 0) {
            val = -12500;
        }
        {
            unsigned short v = (unsigned short) val;
            while (node != 0) {
                node->unk_20 = v;
                node = node->next;
            }
        }
        if (entry->unk_0E > 0) {
            entry->unk_0E--;
        }
        result = 1;
    }
    if (result == 0) {
        func_020914dc(entry);
    }
    return result;
}
