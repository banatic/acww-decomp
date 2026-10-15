/* func_0204d5f8 @ 0x0204d5f8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *);
extern char data_020da13c;
extern char data_020db898;

typedef struct {
    volatile void *unk_00;
} UnkStruct_0204d5f8;

void *func_0204d5f8(void)
{
    UnkStruct_0204d5f8 *obj;
    obj = (UnkStruct_0204d5f8 *) func_020edf70(0x5c);
    if (obj) {
        func_020ee660(obj);
        obj->unk_00 = (void *) &data_020da13c;
        obj->unk_00 = (void *) &data_020db898;
    }
    return (void *) obj;
}
