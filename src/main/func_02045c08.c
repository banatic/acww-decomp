/* func_02045c08 @ 0x02045c08, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a : 3;
    unsigned char : 5;
    unsigned char b : 7;
    unsigned char c : 1;
    unsigned char pad_02[14];
} UnkStruct_02045c08;
extern UnkStruct_02045c08 data_021c7884[0x14];
int func_02045c08(int key)
{
    UnkStruct_02045c08 *e;
    int i;
    int r;
    i = 0;
    r = -1;
    key = (unsigned char) (key & 3);
    e = data_021c7884;
    for (; i < 0x14; i++) {
        if (key == e->a && e->c != 0) {
            r = i;
            break;
        }
        e++;
    }
    return r;
}
