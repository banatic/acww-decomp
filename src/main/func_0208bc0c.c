/* func_0208bc0c @ 0x0208bc0c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC];
    int sub;
} UnkStruct_0208bc0c;

extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern void func_0208be3c(void *);

void func_0208bc0c(UnkStruct_0208bc0c *obj)
{
    func_0208a0c8(&obj->sub);
    if (func_0208a160(&obj->sub)) {
        func_0208be3c(obj);
    }
}
