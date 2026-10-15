/* func_020b1b68 @ 0x020b1b68, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;

extern void OS_Terminate(void);
extern unsigned char data_021f4b10;

void func_020b1b68(void *argument, WVRResult result)
{
    if (result != WVR_RESULT_SUCCESS) {
        OS_Terminate();
    }
    data_021f4b10 = 1;
}
