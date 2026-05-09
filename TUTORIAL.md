# Mac PrintSploit Tutorial
--------------------------

## Introduction
This tutorial will walk you through the process of making a simple MacOS printsploit using native Mac libraries for injection (dyld) and calling the Roblox print offset externally

## Prerequisites

(Tools: XCode Command Line Tools, VSCode or any IDE with terminal)

## Tutorial

First Section:
### Install Roblox
```bash
curl -s "https://raw.githubusercontent.com/norbyv1/MacPrintSploitTutorial/refs/heads/main/intelinstaller.sh" | bash
```

### Getting print offset
```bash
otool -tV /Applications/Roblox.app/Contents/MacOS/RobloxPlayer | grep -A 5 "Current identity is %d" | grep 'callq' | head -n 1 | awk '{print $3}'
```
Save the outputted offset (0x100******) in clipboard or anywhere that is easily retrievable

Next Section:
### Adding code
Make a folder named `printsploit`\
Copy and paste code -> (find code here: `https://github.com/norbyv1/MacPrintSploitTutorial/blob/main/tutorial.cpp`)\
Change the offset variable in main.cpp to the one you found:
 - Example: `uintptr_t offset = 0x1010adc10;` should be replaced with `uintptr_t offset = thesavedoffsetyouhad;`.
Save the file & name the file as main.cpp\
Open a new VSCode terminal:
 - Go to the Mac top bar (when VSCode is **focused**), press **Terminal**, and click **New Terminal**.
Compile `main.cpp` using `clang++`
   - Enter this command in the VSCode terminal:
   ```bash
     clang++ -arch x86_64 -std=c++17 -dynamiclib main.cpp -o printsploit.dylib -lpthread
   ```
Wait for it to compile. 
Afterwards, you should see a printsploit.dylib file in the folder\
Run this command in the same VSCode terminal:
```bash
DYLD_INSERT_LIBRARIES="./printsploit.dylib" /Applications/Roblox.app/Contents/MacOS/RobloxPlayer
```
Roblox should launch; join a game and open console\
It should display the 4 console outputs (print, info, warn, error), and if it doesn't, increase the sleep time by ~5 seconds.

-------------------------------------------------------------------------------------------------------------------------------------------\
Any improvements or suggestions, make a pull request.
