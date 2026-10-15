/* func_ov068_02269944 @ 0x02269944, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_0203e020(void *ptr);
extern void func_ov068_0226cce4(void *a, int n);

struct UnkStruct_02269944 {
    char pad_00[0x1c];
    unsigned char byte;
};

struct UnkStruct_02269944_2 {
    char pad_00[0x618];
    char data;
};

void func_ov068_02269944(struct UnkStruct_02269944 *a, struct UnkStruct_02269944_2 *b)
{
    if (func_02014868(&b->data) != 0) {
        return;
    }
    func_0203e020(b);
    func_ov068_0226cce4(a, 0);
    a->byte = 1;
}
