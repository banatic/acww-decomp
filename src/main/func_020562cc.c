/* func_020562cc @ 0x020562cc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8ca8;
struct entry {
    int value;
    int key;
};
extern struct entry data_021c8e8c[];

int func_020562cc(int key)
{
    int i;
    if (key == 0x4e554c4c) {
        return 0;
    }
    for (i = 0; i < data_021c8ca8; i++) {
        if (key == data_021c8e8c[i].key) {
            return data_021c8e8c[i].value;
        }
    }
    return 0;
}
