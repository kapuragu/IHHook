# IHHook
Version r24 - 2026-08-06 (see github for full changes)
Added SnakeBite builds for Ultimate ASI Loader and plugin folder versions.
Compatibility with tpp-mod.
Simplified and futureproofed version check. Added [exe name]_version_info.txt to the check.
Cleaned up my (rlc) additions.
Renamed internal functions to match real names.

Version r23 - 2026-08-04
version_info.txt version bump
JP 15.4 Walker Gear address fix by suke0930

Version r22 - 2026-06-14
Fixed D-Walker hook addresses that made the game crash for some users on the English version.

Version r21 - 2026-06-10
1.0.15.4 game version addresses by Yazed0071.

Version r20 - 2026-05-20
Added some but not all manual function patterns
Fixed GUI style editor save crash

Version r19 - 2026-04-29
Forked by caplag, contributions by ZIP and Half Way Lambda.
Player appearance override for Snake/Normal fixed (very sloppy, but works)
Added a few of unknown321's block loading trace functions
Side ops in custom locations can now be entered from the side ops list (markers still don't work properly)
Logging fixes

For MGSV version 1.15 (in title screen), 1.0.15.4 in exe  
For Infinite Heaven r265 

Previously bundled with Infinite Heaven, IHHook has been split into a seperate install and nexus page to isolate feedback and issues.

IHHook source: https://github.com/kapuragu/IHHook
IHHook mod: https://www.nexusmods.com/metalgearsolidvtpp/mods/1226
Infinite Heaven mod: https://www.nexusmods.com/metalgearsolidvtpp/mods/45

## Description 
A proxy dll (of dinput8.dll) that loads with MGSV to provide extended features for modding.


## Dependencies
### Runtime
Microsoft Visual C++ Redistributable for Visual Studio, x64  
https://aka.ms/vs/17/release/VC_redist.x64.exe 

### Development
MSVS v141 - VS 2017 C++ x64/x86 build tools (v14.16)  
Windows 10 SDK (10.0.17763.0)  
(Install via Visual Studio Installer > Individual Components)  

## IHHook features
See this youtube playlist for features that are visually demonstratable  
https://www.youtube.com/playlist?list=PLSKlVTXYh6F9XCIpHUGTSkd9gDzoU6N1s

dear-IMGUI based menu for Infinite Heaven.  
[youtube]ERL7okZVcW4[/youtube]  
https://youtu.be/ERL7okZVcW4

Lua C API support (mostly complete)  
Allows extending the MGSVs embedded lua via C.  
Does not have dynamic library support as mgsv lua is statically compiled, and running the mgsv lua state through a seperate distro of lua isn't desirable since the mgsv lua core is modified from default.  
However it is possible to compile lua C modules into IHHook.  


Logging via spdlog.  
Infinite Heaven uses this for better performance (mostly used for debugging)  
Has it's own seperate log for debug/info output.  


Named Pipe server: Starts up a threaded Named Pipe server with two pipes mgsv_in, mgsv_out.  
Currently used by Infinite Heaven to improve performance when using IHExt and should open further posibilities I was reluctant to persue due to old text file based IH>IHExt communication.  


CityHash logging (currently has to be compiled in with a #define) using emooses cityhash logging (though using spdlog for better performance) that IHHook was initially built off.  


RawInput keyboard processing and blocking (proof of concept)  

## Further info
See IHHHook.h for some comments about the project.

## Thanks
zip for making me smooth out the release process, sorry about taking so long.
sai for mentioning what he had done with ghidra which helped me get past a few hurdles to start finding MGSVs lua functions.  
emoose for CityHook which provided a base to start IHHook from.
Half Way Lambda for imgui contributions in r18
Yazed0071 for the addresses in 1.0.15.4