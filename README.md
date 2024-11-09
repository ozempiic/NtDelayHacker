
# NtDelayExecution Manipulator

This project uses `NtDelayExecution` function to create a custom sleep mechanism, along with manipulating breakpoints and handling exceptions.

![exec](https://cdn.discordapp.com/attachments/1253196583403786302/1304731873074745346/image.png?ex=673075bf&is=672f243f&hm=d8a499b0897166971759128edb209cbdcb313611439690fdc5eda3b97ec03fe2&)



# Installation 

### Step 1: Download and Extract w64devkit

- Download w64devkit v2.0.0 from the [w64devkit Github](https://github.com/skeeto/w64devkit/releases/tag/v2.0.0).
- Extract the downloaded files to a directory.

### Step 2: Download NASM

- Go to the [NASM website](https://nasm.us/) and download the appropriate installer for your system.
-  Install NASM and make sure it is added to your system's `PATH` so it can be called from the command line.

### Step 3: Clone Repository

Clone the repository to your local machine:

```bash
git clone https://github.com/ozempiic/NtDelayHacker.git
```

### Step 4: Compiling & Running

```bash
run w64devkit console & cd into NtDelayHacker/src
nasm -f win64 syscall.asm -o syscall.obj
g++ -m64 main.cpp syscall.obj -o main
./main
```
## Authors

- [@KillBot](https://www.github.com/coplite) - made most of it
- [@Avale](https://www.github.com/ozempiic) - gave idea + fixed his sleep function

