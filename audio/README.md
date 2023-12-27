## Audio

Almost all of the work was done on 13.2.1, versins above that were just done via diffing and auto-naming through BinDiff, so some of the function names are definitely wrong, and the newer versions are also not complete.

Unfortunately I updated the structs for version 15 and didn't keep old versions, so *some* structs will now be wrong for versions <15 (mainly the AudioRenderSystem), but 13.2.1 should still be usable. If 15 doesn't have something named, check 13.2.1.

### ADSP

There's a 32-bit binary stored within the audio sysmodule which is launched at startup. This binary is the adsp which comes from nVidia's L4T (Linux4Tegra) packages. It hosts various apps which developers can write for it, and they communicate with the main sysmodule via mailboxes. I've included the base adsp in the adsp folder. \
**It doesn't contain any Nintendo code, it's just the base elf from nVidia**, it includes symbols and structs which can be used as a reference, since the adsp inside the sysmodule is stripped.

The ADSP code is split between regular ARM and THUMB. Most of the DSP code is THUMB, which includes all of Nintendo's app code. I was confused by being unable to decompile most of the ADSP code until Scires pointed this out to me. If a function starts on an odd byte, it's a THUMB function, so 0x80300000 would be normal, 0x80300001 would be a THUMB function. IDA was able to auto analyse almost all of the ADSP once I set a function to THUMB.

Here's a couple ways to get the ADSP in a sysmodule without symbols (In my DBs it's inside the DoFirmwareLoadImpl function):
 - Look at the segments list and it should be the 5th one (after .rodata)
 - Search for 0xC0C99, which is the error thrown when the adsp fails to launch, so just scroll up from that and the function call to launch the ADSP should be right above it. The call takes the start/end pointers of the ADSP code, so you can dump it from there.


 The ADSP itself has a function which sets up and prints the segments (platform_remap_mappings) so you can search for 0x80300000 or search for "text" and you'll find the function even without symbols. So you can then add those segments to the ADSP in IDA if you want.

 The `adsp_static_apps_init` function sets up the registered apps, the linked data contains the app info for each app. There's the app name, an init function, and the main function.
 Nintendo have 3 apps:
  - gmix. This app is what actually deals with audio hardware I think. It recieves samples from the AudioRenderer app and also gets messages from the sysmodule via AudioRenderSession. I haven't done much RE of this app, and I don't understand it very well. Great area for more RE if anyone wants.
  - AudioRenderer. This app interacts with the audren service in the sysmodule. It receives a command list from audren and processes the commands, sending the resulting audio samples through gmix.
  - OpusDecoder. The ADSP contains libopus and deals with Opus audio stuff from the hwopus service. Haven't RE'd this one either.

`<app>_Main` are the entry points for that app, so AudioRender_Main is the place to go to start looking at how the audio renderer works etc. Some of these functions are also included the sdk which is very useful, like CommandListProcessor::Process which is the main audio renderer function which processes the command list, along with all the of individual command functions. I've found it easier to look at the 64-bit SDK side to understand the commands rather than the 32-bit ADSP ones, but it's nice to be able to look at the same functions compiled two different ways to help understand them. For that Command Process function in particular, it's a massive switch of all commands, so you need to re-type commandbuffer to the specific command you're looking at. Variables also overlap with different purposes in each, so you'll probably want to rename variables.
