/* func_020321bc @ 0x020321bc, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node;

extern int func_02032444(struct Node *obj, int a2, int a3, int a4, int a5, int a6, int *cfg);

struct Node {
    unsigned char pad_00[0x2c];
    struct Node *next;
};

extern struct Node *data_021c30e4;

int func_020321bc(struct Node *obj, int a2, int a3, int a4, int a5, short a6, int *cfg)
{
    int local[3];
    int result;

    local[0] = 0x1000;
    local[1] = 0x1000;
    local[2] = 0x1000;

    if (cfg != 0) {
        local[0] = cfg[0];
        local[1] = cfg[1];
        local[2] = cfg[2];
    }

    result = func_02032444(obj, a2, a3, a4, a5, (int) a6, local);

    if (result != 0) {
        obj->next = data_021c30e4;
        data_021c30e4 = obj;
        return 1;
    }
    return 0;
}
