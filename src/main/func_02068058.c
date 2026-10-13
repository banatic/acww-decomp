/* func_02068058 @ 0x02068058, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02068058 {
    char pad_00[0x1a69];
    unsigned char byte;
    char pad_1A6A[0x4e];
    void *unk_1AB8;
};

extern void func_020b44bc(void **, unsigned char);

void *func_02068058(struct UnkStruct_02068058 *p)
{
    func_020b44bc(&p->unk_1AB8, p->byte);
    return (void *) &p->unk_1AB8;
}
