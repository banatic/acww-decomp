/* line_handlers: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205c0dc @ 0x0205c0dc, 0x14 bytes, Thumb
 * func_0205c0d4 @ 0x0205c0d4, 0x8 bytes, Thumb
 * func_0205c080 @ 0x0205c080, 0x54 bytes, Thumb
 * func_0205c054 @ 0x0205c054, 0x2c bytes, Thumb
 * func_0205c024 @ 0x0205c024, 0x30 bytes, Thumb
 * func_0205bfdc @ 0x0205bfdc, 0x48 bytes, Thumb
 * func_0205bfd0 @ 0x0205bfd0, 0xc bytes, Thumb
 */

struct Node;

struct Node {
    unsigned char state;
    void (*func4)(void);
    void (*func8)(void);
    unsigned int unk_0C;
    unsigned int unk_10;
    void (*unk_14)(void);
    struct Node *next;
};

typedef struct Node_0205c054 {
    unsigned char type;
    char pad_01[7];
    void (*func)(void);
    char pad_0C[12];
    struct Node_0205c054 *next;
} Node_0205c054;

struct Node_0205c024 {
    char unk_00;
    unsigned char pad_01[3];
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int pad_14;
    struct Node_0205c024 *unk_18;
};

struct Node_0205bfdc {
    char pad_00[0x18];
    struct Node_0205bfdc *next;
};

extern unsigned int data_021c9aa8;
extern unsigned int data_021c9aac;

void func_0205c0dc(void)
{
    unsigned int *p0;
    unsigned int *p1;

    p0 = &data_021c9aa8;
    p1 = &data_021c9aac;
    *p0 = 0;
    *p1 = 0;
}

void func_0205c0d4(void)
{
    func_0205c0dc();
}

void func_0205c080(void)
{
    struct Node *node = (*(struct Node * *) &data_021c9aa8);
    while (node) {
        if (node->state == 0) {
            node->state = 1;
            node->unk_0C = node->unk_10;
            if (node->func8) {
                node->func8();
            }
        }
        if (node->func4) {
            node->func4();
        }
        if (node->state == 2) {
            node->state = 1;
            node->unk_0C = node->unk_10;
            node->func8 = node->unk_14;
            if (node->func8) {
                node->func8();
            }
        }
        node = node->next;
    }
}

void func_0205c054(void)
{
    Node_0205c054 *p;
    p = (*(Node_0205c054 * *) &data_021c9aa8);
    while (p) {
        if ((unsigned char) (p->type + 0xFF) <= 1) {
            if (p->func != 0) {
                p->func();
            }
        }
        p = p->next;
    }
}

int func_0205c024(struct Node_0205c024 *node, int a, int b, int c)
{
    node->unk_10 = a;
    node->unk_0C = 0;
    node->unk_08 = b;
    node->unk_04 = c;
    node->unk_18 = 0;
    node->unk_00 = 0;
    if ((*(struct Node_0205c024 * *) &data_021c9aac)) {
        (*(struct Node_0205c024 * *) &data_021c9aac)->unk_18 = node;
        (*(struct Node_0205c024 * *) &data_021c9aac) = node;
    } else {
        (*(struct Node_0205c024 * *) &data_021c9aac) = node;
        (*(struct Node_0205c024 * *) &data_021c9aa8) = node;
    }
    return 1;
}

int func_0205bfdc(struct Node_0205bfdc *node)
{
    struct Node_0205bfdc *prev;
    if (node == (*(struct Node_0205bfdc * *) &data_021c9aa8)) {
        (*(struct Node_0205bfdc * *) &data_021c9aa8) = node->next;
        if ((*(struct Node_0205bfdc * *) &data_021c9aac) == node) {
            (*(struct Node_0205bfdc * *) &data_021c9aac) = 0;
        }
        return 1;
    }
    prev = (*(struct Node_0205bfdc * *) &data_021c9aa8);
    while (prev) {
        if (prev->next == node) {
            prev->next = prev->next->next;
            if ((*(struct Node_0205bfdc * *) &data_021c9aac) == node) {
                (*(struct Node_0205bfdc * *) &data_021c9aac) = prev;
            }
            return 1;
        }
        prev = prev->next;
    }
    return 0;
}

void *func_0205bfd0(void *r0, int r1, int r2)
{
    *(int *) ((char *) r0 + 0x14) = r2;
    *(int *) ((char *) r0 + 0x10) = r1;
    *(unsigned char *) r0 = 2;
    return (void *) 1;
}
