# B4DB4B3-RAT
 Program for remote computer management using Telegram on C++ - by B4DB4B3
### Interface  
 ![UI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/UI.png)   
 ![EXAMPLE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/EXAMPLE.png)   
### Weight of stub and builder  
 #### P.S: Around 400-300 KB :)
 ![WEIGHT](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/WEIGHT.png)   
   
# Commands (Will be added)   
```
 Process manager:      
 /user[ID] processes - get process list    
 /user[ID] closeproc [processname.exe] - close process    
 /user[ID] inject_dll [processname.exe] [C:\Path\To\File.dll] - Inject dll into process    
   
 Auxiliary:   
 /user[ID] loader [LINK] [PATH] - upload file from [LINK] to [PATH]    
 /user[ID] run [PATH] [ARGS] - run file from [PATH] with arguments [ARGS]   
   
 Jokes:   
 /user[ID] disable pc - disable computer of user    
 /user[ID] close - close rat    
 /user[ID] disable display - disable display user    
   
 File manager:   
 /user[ID] dir [C:\Folder] - show files and folders in directory    
 /user[ID] dir del_file C:\Path\To\File.exe - delete file into directory    

 RAT:   
 /users - show online users   
```
	
# Coming soon
- [x] Add file manager
- [ ] Add function to get screenshot
   - [ ] Add function to record desktop
   - [ ] Add function to record microphone
- [x] Add more jokes (open url, block url, close process and etc.)
- [ ] Add process control (inject dll, shellcode and etc.)
- [ ] Add more information about PC 
 
# Changelog
> 17.10.2020 16:30 - Code is optimized, added commands
 
# License
 ![B4DB4B3-RAT](https://github.com/4B4DB4B3/B4DB4B3-RAT) is licensed under MIT License - https://mit-license.org/
