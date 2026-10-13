/* func_02084d5c @ 0x02084d5c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[2];
    unsigned short id;
    unsigned char pad_04[16];
} UnkStruct_02084d5c;

UnkStruct_02084d5c *func_02084d5c(unsigned short *value, UnkStruct_02084d5c *array, int count)
{
    int i;
    UnkStruct_02084d5c *p;

    p = array;
    for (i = 0; i < count; i++) {
        if (p->id == *value) {
            return p;
        }
        p++;
    }
    return 0;
}
