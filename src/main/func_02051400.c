/* func_02051400 @ 0x02051400, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *NNS_FndGetNextListObject(void *a, void *b);
extern void func_02050f0c(void *p);
extern void func_02051368(void *p);
extern int data_021c81bc[];

typedef struct {
    char pad_00[0x54];
    unsigned char flag;
    char pad_55[3];
    int key;
    int state;
} MNode;

void func_02051400(int param)
{
    MNode *node = 0;
    int local = 0;
    int neg_one = -1;
    int zero = 0;

    while (1) {
        node = NNS_FndGetNextListObject(data_021c81bc, node);
        if (node == 0) {
            break;
        }
        if (node->key == param) {
            if (node->state != ~local) {
                func_02050f0c(node);
                node->state = neg_one;
            }
            if (node->flag != 0) {
                func_02051368(node);
                node->flag = zero;
            }
        }
    }
}
