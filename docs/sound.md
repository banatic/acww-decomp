# Optional sound output

The playable **Clean** runtime can render the game's music, character speech and effects:

```sh
python tools/play.py --form clean --sound
```

An already built playable program accepts `--sound` too. This enables `RUN_AUDIO=1` and
`RUN_SEQUENCER=1`; the game still runs with its configured Clean policy. Audio does not switch
the game to Reference. With neither sound nor recording requested, the original default
behavior stays disabled. ROMs, sound banks and recordings are not distributed.

Windows playback uses WinMM, loaded after the runtime reserves the DS address ranges. The
device receives 32768 Hz, signed 16-bit stereo PCM in eight reusable 512-frame buffers. Writes
do not block the emulation thread. If no buffer is free, that block is counted as dropped.
An unavailable device is reported without stopping the game. Tab/`--fast` resets and mutes the
device queue; returning to normal speed resumes with current audio. A WAV recording retains
emulated time during fast forward.

For headless checks, including on Linux:

```sh
python tools/run.py 0 2600 --native all --clean all --input runtime/recordings/new-game.txt --audio-wav new-game.wav
```

The playable program also accepts `--audio-wav FILE`, with or without `--sound`. Recording
creates a new file exclusively, refuses to overwrite an existing file, writes little endian
stereo PCM and finalizes the RIFF header on orderly exit. The WAV size limit is reported.
Output contains audio from the user's ROM and should stay private. Runtime reports include
nonzero frames, peak amplitude, device blocks/drops, channel formats and capture sample counts.

## Signal path

`sequencer.c` retains the existing SDK sequence player, instrument selection, note allocation,
envelopes, pitch and modulation. Its hardware writes now optionally feed `ds_audio.c` with
the sample address and bus-cycle timestamp. The mixer decodes signed PCM8/PCM16 and DS IMA
ADPCM, restores ADPCM predictor/index state at loops, and generates the channel-specific
square waves and noise. Timer, volume, divider, pan and master changes take effect after
rendering samples up to that event's clock. Output frames use an integer grid derived from
the DS bus clock, independent of host execution speed.

The ARM9's direct PCM/channel commands are also handled. Crucially, Wild World normally
routes the mixer through capture RAM and playback channels 1/3: rendering only SSEQ notes
leaves those output channels silent. Both capture units now write their PCM buffers at their
shared channel timer rate. The SDK capture commands retain destination, length, format and
loop settings. Its alarms send generation-tagged FIFO notifications so the game's own ARM9
output-effect code processes the buffers. The SDK's surround attenuation and master-pan
override are applied to the channel writes too.

Hardware formats, register fields and timer relationships follow
[GBATEK's DS sound reference](https://mgba-emu.github.io/gbatek/#dssound).
The command packing and alarm payload were checked against the supported Korean ROM's SDK.
No emulator implementation or external audio library is incorporated.

## Validation and limits

`python tools/test_ds_audio.py` compiles and runs the actual mixer and WAV sink using only
synthetic bytes. It checks signed samples, one-shot end/hold, PCM and ADPCM loops, a known
ADPCM vector, saturation, PSG duty/noise, volume/divider/pan, master and output routing,
capture RAM playback, capture one-shot/PCM8, exact frame count, chunk-independent WAV output,
and exclusive creation. These checks run in CI without a ROM.

The standalone contribution is checked on the unmodified Korean version (`adm-kr`), with
no localization options or changes to Clean functions. `tools/setup.py --version adm-kr --quick`
builds the Windows frontend and reproduces the expected 1300-frame title hash with sound off
in the interpreter, Native and Clean: `69297d7d46a0d122090aec6da585046bf2227aaf`.

With `--audio-wav`, Reference and Clean agree on the 1300-frame title recording
(`492ccb294b59c7cc61932737f26f8ab10f624607`) and the 2600-frame new-game recording
(`42f0bfc7def885787a8745769af184f426b8760d`), both at RTC `2005-11-23 12:00:00`.
Their private 32768 Hz stereo WAVs have nonzero samples, peak amplitude 17866 and no
clipped samples. Private ROMs and WAVs are not included.

This is functional output, not a claim of bit-identical analog DS audio. The model does not
reproduce the hardware's FIFO prefetch, every fractional rounding stage or PWM/DAC behavior.
Nearest sample resampling can alias high frequencies. Device latency and underruns depend
on the PC. The ARM7 command model and its existing computed pitch table remain in use.
Real-time device output is Windows only; WAV output is portable. Multi-console audio mixing
is not provided.
