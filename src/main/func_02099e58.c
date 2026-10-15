/* func_02099e58 @ 0x02099e58, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642fc(void *object);
extern int func_02003780(void *);

struct UnkStruct_02099e58 {
    char pad_00[30];
    unsigned short unk_1E;
};

struct UnkStruct_02099e58 *func_02099e58(struct UnkStruct_02099e58 *ptr)
{
    func_020642fc(ptr);
    func_02003780((char *) ptr + 14);
    ptr->unk_1E = 0xfff1;
    return ptr;
}
