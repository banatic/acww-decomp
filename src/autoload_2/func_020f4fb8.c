/* func_020f4fb8 @ 0x020f4fb8, 0x84 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    void *hptr;
} GObj;

extern GObj data_021fd1f8;
extern int func_020f5e50(void *, int);
extern int func_020f5e24(int);
extern int func_020f5c64(void *, int);
extern void NNS_SndPlayerSetVolume(void *param1, int param2);
extern void func_0210b634(void *a, unsigned short b, void *c);
extern unsigned short data_0213e858;

void func_020f4fb8(int unused, void *p)
{
    int vol;
    GObj *g;
    unsigned int ok;
    int pan;
    g = &data_021fd1f8;
    ok = (g->hptr != 0);
    if (ok == 0) {
        return;
    }
    vol = func_020f5e24(func_020f5e50(p, 0));
    pan = func_020f5c64(p, 0);
    if (vol < 0x28) {
        vol = 0x28;
    }
    NNS_SndPlayerSetVolume(g, vol);
    func_0210b634(g, data_0213e858, (void *) pan);
}
