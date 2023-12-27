### Switch RE

This repo contains my RE of various Switch sysmodules. Very much WIP and not complete.

### Structs

The structs folder contains all the structs I've created in a few big C headers. It's intended that you import `<sysmodule>.h` into IDA, e.g `audio.h` for audio. The normal way I use these is to edit whichever struct, and then use ctrl+f9 in IDA to load it. All the structs will be updated and stuff, then just hit f5 to re-decompile whichever function you're looking at and the changes will apply.
You can use these structs alone without needing the IDA DBs, although when first importing there may be some errors with missing symbols etc because of the order everything is laid out in the header. Try using ctrl+f9 a couple times in a row, if the number of errors don't go down, then check the output, you'll probably just need to throw the `struct` keyword on some struct members which use structs that are defined below them. Everything is there though.
My DBs do contain some outdated structs since I changed struct names and stuff while working on the RE, e.g `nn::audio::dsp::ReverbCommand` vs `nn::audio::ReverbCommand` where the second one is the current and most updated one, as it's currently named in audio.h. Be careful of that kind of thing.

The structs are updated to firmware 15 currently, so using them directly on firmware 13 for example will be wrong and give you some wrong struct sizes. Unfortunately I didn't keep older firmware versions as separate headers as I should have, but those versions are still available via the DBs so you can dump them from there.

The nn structs were taken from https://github.com/misson20000/nn-types and modified a little bit.

If you have any questions or stuff doesn't work then you can message me on Discord, Maide on Yuzu's server.
