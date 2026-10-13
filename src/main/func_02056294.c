/* func_02056294 @ 0x02056294, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned int value;
    unsigned int key;
};
extern struct Entry data_021c8cac[];

unsigned int func_02056294(unsigned int param)
{
    int i;
    if (param == 0x4e554c4c) {
        return 0;
    }
    for (i = 0; i < 60; i++) {
        if (param == data_021c8cac[i].key) {
            return data_021c8cac[i].value;
        }
    }
    return 0;
}
