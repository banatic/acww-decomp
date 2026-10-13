/* func_0208a978 @ 0x0208a978, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a510(void *);
extern void func_0208a664(void *);
extern void func_0208a944(void *);

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char unk_54;
} UnkStruct_0208a978;

void func_0208a978(UnkStruct_0208a978 *p)
{
    if (p->unk_54) {
        p->unk_54 = 0;
        func_0208a510(p);
        func_0208a664(p);
        func_0208a944(p);
    }
}
