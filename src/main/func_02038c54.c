/* func_02038c54 @ 0x02038c54, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *, void *);
extern int data_020da548;

typedef struct {
    void *unk_00;
} UnkStruct02038c54;

void *func_02038c54(void *self)
{
    UnkStruct02038c54 *obj = self;

    obj->unk_00 = &data_020da548;
    func_020a8c38(self, &data_020da548);
    return self;
}
