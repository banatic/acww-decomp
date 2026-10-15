/* func_ov009_02264370 @ 0x02264370, 0x18 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02032768(void *);
extern char data_ov009_022658c0[];

typedef struct {
    void *unk_00;
} UnkStruct_02264370;

UnkStruct_02264370 *func_ov009_02264370(UnkStruct_02264370 *obj)
{
    func_02032768(obj);
    obj->unk_00 = data_ov009_022658c0;
    return obj;
}
