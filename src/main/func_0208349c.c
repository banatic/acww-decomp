/* func_0208349c @ 0x0208349c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    char pad_04[4];
    char unk_08;
} UnkStruct_0208349c;

extern char data_020e1a90[];
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_02083514(void);
extern void func_02083c78(UnkStruct_0208349c *);

UnkStruct_0208349c *func_0208349c(UnkStruct_0208349c *obj)
{
    obj->unk_00 = data_020e1a90;
    func_02138c48(&obj->unk_08, 5, 2, func_02083514);
    func_02083c78(obj);
    return obj;
}
