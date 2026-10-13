/* func_0200ffec @ 0x0200ffec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0200ffec;
struct UnkStruct_0200ffec_2;

struct UnkStruct_0200ffec {
    char pad_00[0x80c];
    void *elem;
};

struct UnkStruct_0200ffec_2 {
    char pad_00[0xc];
    int value;
};

extern struct UnkStruct_0200ffec_2 *func_02042fc4(void *handle);

int func_0200ffec(struct UnkStruct_0200ffec *ptr)
{
    return func_02042fc4(ptr->elem)->value;
}
