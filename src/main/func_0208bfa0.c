/* func_0208bfa0 @ 0x0208bfa0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208c620(char *);

typedef struct {
    char pad_00[0x20];
    int unk_20;
    char pad_24[0x4];
    char unk_28;
} UnkStruct_0208bfa0;

int func_0208bfa0(UnkStruct_0208bfa0 *p)
{
    if (p->unk_20 != 0) {
        goto L0;
    }
    if (func_0208c620(&p->unk_28) == 0) {
        goto L0;
    }
    return 1;
L0:
    return 0;
}
