/* func_02050be0 @ 0x02050be0, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short key;
    unsigned short value;
} Entry;

unsigned short func_02050be0(unsigned short key, unsigned short cur_key, Entry *e)
{
    while (1) {
        if (key == cur_key) {
            return e->value;
        }
        e++;
        cur_key = e->key;
        if (cur_key == 0) {
            break;
        }
    }
    return key;
}
