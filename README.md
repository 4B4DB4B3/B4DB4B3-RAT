# -= B4DB4B3-RAT =-
 Program for remote computer management using Telegram on C++ - by B4DB4B3
### [Interface]  
 ![UI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWUI.png)   
 ![EXAMPLE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/EXAMPLE.png)   
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

### RAT:   
 Command name              | Parameters                                              | Description
 ------------------------- | ------------------------------------------------------- | -----------
 /users                    |                                                         | show online users   
	
# [Coming soon]
- [x] Add file manager
- [ ] Add function to get screenshot
   - [ ] Add function to record desktop
   - [ ] Add function to record microphone
- [x] Add more jokes (open url, block url, close process and etc.)
- [x] Add process control (inject dll, shellcode and etc.)
- [x] Add more information about PC 
- [ ] Add Service manager (for deleting, showing and adding your system drivers)   

# [CHANGELOG]
Date       | Time  | Description
---------- | ----- | -----------
17.10.2020 | 16:30 | Code is optimized, added commands   
18.10.2020 | 18:40 | Code is refactored and optimized, fixed bugs (command inject dll didn't work), added new function in builder (write in scheduler task), updated GUI, added re-launch protection, added commands ![NEWUI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/NEWUI.png)
19.10.2020 | 01:30 | Deleted traces of debugging (sorry for this), added more information about PC ![NEWINFO](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/Screenshots/NEWINFO.png)


# [LICENSE]
 ![B4DB4B3-RAT](https://github.com/4B4DB4B3/B4DB4B3-RAT) is licensed under MIT License - https://mit-license.org/
