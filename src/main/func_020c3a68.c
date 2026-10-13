/* func_020c3a68 @ 0x020c3a68, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020c3c64(void *);
extern void func_0202ee5c(void *);
extern char data_020e877c;

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char unk_658[1];
} UnkStruct_020c3a68;

UnkStruct_020c3a68 *func_020c3a68(UnkStruct_020c3a68 *obj)
{
    obj->unk_00 = &data_020e877c;
    func_020c3c64(obj->unk_658);
    func_0202ee5c(obj);
    return obj;
}
