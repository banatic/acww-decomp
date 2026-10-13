/* func_020fa204 @ 0x020fa204, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct Node {
    struct Node *next;
    unsigned char pad_04[0x18];
    unsigned int pad_bits : 3;
    unsigned int flag : 1;
} Node;

typedef struct {
    unsigned int pad_00;
    Node *head;
    unsigned char pad_08[0x2c];
    Node *cur;
    unsigned int saved;
} UnkStruct_020fa204;

extern void func_020fabe8(UnkStruct_020fa204 *self, unsigned int arg);

void func_020fa204(UnkStruct_020fa204 *self, unsigned int arg1, unsigned int arg2)
{
    Node *p;

    *(volatile unsigned short *) 0x04000060 = (unsigned short) ((*(volatile unsigned short *) 0x04000060 & ~0x3000) | 8);
    self->saved = arg1;
    p = self->head;

    while (p != 0) {
        self->cur = p;
        if (!p->flag) {
            func_020fabe8(self, arg2);
        }
        p = p->next;
    }
}
