/* func_02084d8c @ 0x02084d8c, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02084d8c {
    char pad_00[0x70];
    unsigned char flag;
    unsigned int data;
};

void func_02084d8c(struct UnkStruct_02084d8c *obj, unsigned int *src)
{
    unsigned char *p = (unsigned char *) obj;
    p += 0x70;
    *p = 1;
    obj->data = *src;
}
