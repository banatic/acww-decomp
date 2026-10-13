/* func_0208c804 @ 0x0208c804, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e2250;
extern void func_0208c668(void *);
extern void func_0208af00(void *);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_0208a1f4(void);

typedef struct {
    void *unk_00;
    unsigned char pad_04[8];
    unsigned char unk_0C;
} UnkStruct_0208c804;

void *func_0208c804(void *arg)
{
    UnkStruct_0208c804 *obj = (UnkStruct_0208c804 *) arg;

    obj->unk_00 = &data_020e2250;
    func_0208c668(obj);
    func_02138c48(&obj->unk_0C, 9, 20, func_0208a1f4);
    func_0208af00(obj);
    return obj;
}
