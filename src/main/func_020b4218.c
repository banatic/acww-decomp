/* func_020b4218 @ 0x020b4218, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    signed char data;
};

struct UnkStruct_020b4218 {
    char pad_00[0x0afc];
    struct Node start_node;
    char pad_AFD[0x0df7];
    char sub[1];
    char pad_18F5[0x33];
    unsigned char flag;
    char pad_1929[0x2f];
    struct Node *current;
};

extern void func_020b4c0c(char *p);
extern int func_020b419c(struct UnkStruct_020b4218 *self);
extern struct Node *func_020a7bf4(struct Node *n, int a);
extern void func_020b4bf0(char *p, int n);
extern void func_020b4bd4(char *p);

int func_020b4218(struct UnkStruct_020b4218 *self)
{
    int ret;
    struct Node *start;

    ret = 0;
    func_020b4c0c(self->sub);
    start = &self->start_node;

    while (self->flag == 0) {
        struct Node *n = start;
        int val = 0;

        while (n != 0 && n->data != 10) {
            self->current = n;
            val = func_020b419c(self);
            if (val > 0) {
                break;
            }
            n = func_020a7bf4(n, 1);
        }

        func_020b4c0c(self->sub);
        if (val > 0) {
            func_020b4bf0(self->sub, val);
            ret = 1;
        } else {
            func_020b4bd4(self->sub);
        }
    }

    return ret;
}
