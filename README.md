# -= B4DB4B3-RAT =-
 Program for remote computer management using Telegram on C++ - by B4DB4B3   
 P.S: I didn't do animations on buttons. I can do it in the future, If you like the project
### [Interface]  
 ![UI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWUI.png)   
 ![EXAMPLE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/COMMANDLIST.png)   
### [Weight of stub and builder]  
 #### P.S: Around 400-300 KB :)
 ![WEIGHT](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/WEIGHT.png)   
   
# [Commands (Will be added)]   
### Process manager:      
 Command name         | Parameters                             | Description
 -------------------- | -------------------------------------- | -----------
 /user[ID] processes  |                                        | get process list    
 /user[ID] closeproc  | [processname.exe]                      | close process    
 /user[ID] inject_dll | [processname.exe] [C:\Path\To\File.dll]| inject dll in process
 
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

### Service manager:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] service show    |                                                         | show all drivers in system    
 /user[ID] service add     | [Name] [DisplayName] [C:\ProgramData\yourdriver.sys] [Type-Driver] [Start-Type] | add your driver in system, Check Type-Driver and Start-Type values in "Service manager parse table"    
 /user[ID] service delete  | [NameService]                                           | delete driver from system


### Screen manager:
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /user[ID] screenshot      |                                                         | take screenshot, upload her on prnt.sc and send you 


### RAT:   
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /online                   |                                                         | show online users   
	
# [Coming soon]
- [x] Add file manager
- [x] Add function to get screenshot
   - [ ] Add function to record desktop
   - [ ] Add function to record microphone
- [x] Add more jokes (open url, block url, close process and etc.)
- [x] Add process control (inject dll, shellcode and etc.)
- [x] Add more information about PC 
- [x] Add Service manager (for deleting, showing and adding your system drivers)   

# [CHANGELOG]
Date       | Time  | Description
---------- | ----- | -----------
17.10.2020 | 16:30 | Code is optimized, added commands   
18.10.2020 | 18:40 | Code is refactored and optimized, fixed bugs (command inject dll didn't work), added new function in builder (write in scheduler task), updated GUI, added re-launch protection, added commands ![NEWUI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWUI.png)
19.10.2020 | 01:30 | Deleted traces of debugging (sorry for this), added more information about PC ![NEWINFO](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWINFO.png)
19.10.2020 | 17:20 | Clear warnings, added Service manager ![SERVICE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/SERVICE.png)   
20.10.2020 | 11:19 | Code review, bug fix, added new function (screen manager) (wrote yourself api on wininet for work with prnt.sc api) ![SCREEN](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/SCREENTOOL.png)  
20.10.2020 | 18:49 | Update GUI (change location objects)

## Service manager parse table:
### [service add] params [Type] driver
String param             | Value
------------------------ | --------------------------
win32-service            | SERVICE_WIN32
adapter-service          | SERVICE_ADAPTER
kernel-driver            | SERVICE_DRIVER
interactive-process      | SERVICE_INTERACTIVE_PROCESS
user-serice              | SERVICE_USER_SERVICE
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
