/* func_02055b50 @ 0x02055b50, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dTexGetRequiredSize(void *);
extern int NNS_G3dTex4x4GetRequiredSize(void *);
extern int NNS_G3dPlttGetRequiredSize(void *);
extern int func_02055c74(void *, int);
extern int func_02055c68(void *, int);
extern int func_02055c40(void *, int);
extern void NNS_G3dTexSetTexKey(void *, int, int);
extern void func_02105178(void *, int);

void func_02055b50(void *arg0, void *arg1)
{
    int v1, v2, v3, v4, v5, v6;
    v1 = NNS_G3dTexGetRequiredSize(arg1);
    v2 = NNS_G3dTex4x4GetRequiredSize(arg1);
    v3 = NNS_G3dPlttGetRequiredSize(arg1);
    v4 = func_02055c74(arg0, v1);
    v5 = func_02055c68(arg0, v2);
    v6 = func_02055c40(arg0, v3);
    NNS_G3dTexSetTexKey(arg1, v4, v5);
    func_02105178(arg1, v6);
    ((char *) arg0)[0x10] = 1;
}
