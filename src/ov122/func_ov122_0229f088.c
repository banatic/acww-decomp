/* func_ov122_0229f088 @ 0x0229f088, 0x1e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098ddc(int);
extern void func_02065db8(int, int);

void func_ov122_0229f088(void *obj)
{
    int v;
    v = func_020984e8();
    v = func_02099734(v);
    v = func_02098ddc(v);
    func_02065db8(v, *(int *) ((char *) obj + 0xBC));
}
