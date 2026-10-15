/* func_0202445c @ 0x0202445c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int lo;
    unsigned int hi;
} DblWord;

extern DblWord data_020d91a8;
extern int func_020154b4(void *a, void *b, int c, int d, int e);
extern void func_0202dbf0(void *a, DblWord val);

void func_0202445c(void *obj)
{
    func_020154b4(obj, (char *) obj + 0x19c, 0, 5, 0);
    func_0202dbf0(obj, data_020d91a8);
}
