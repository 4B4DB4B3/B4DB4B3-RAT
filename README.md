# -= B4DB4B3-RAT =-
 Program for remote computer management using Telegram on C++ - by B4DB4B3
### [Interface]  
 ![UI](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/NEWUI.png)   
 ![EXAMPLE](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/EXAMPLE.png)   
### [Weight of stub and builder]  
 #### P.S: Around 400-300 KB :)
 ![WEIGHT](https://github.com/4B4DB4B3/B4DB4B3-RAT/blob/main/WEIGHT.png)   
   
# [Commands (Will be added)]   
### Process manager:      
 Command name         | Parameters                             | Description
 -------------------- | -------------------------------------- | -----------
 /user[ID] processes  |                                        | get process list    
 /user[ID] closeproc  | [processname.exe]                      | close process    
 /user[ID] inject_dll | [processname.exe] [C:\Path\To\File.dll]| Inject dll into process
 
### Auxiliary: 
 Command name         | Parameters                                              | Description
 -------------------- | ------------------------------------------------------- | -----------
 /user[ID] loader     | [https://google.com/file.exe] [C:\ProgramData\file.exe] | upload file from [LINK] to [PATH]    
 /user[ID] run        | [C:\ProgramData\file.exe] [Args to run file | Or empty] | run file from [PATH] with arguments [ARGS]   
   
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
 /user[ID] dir del_file    | [C:\Path\To\File.exe]                                   | delete file into directory    

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
- [ ] Add more information about PC 
- [ ] Add Service manager (for deleting, showing and adding your system drivers)
 
# [Instruction to use]
## English
1. Download the release of the program (or compile it yourself), and then run Builder.exe (Important: Stub.exe must be located next to Builder.exe)
2. Create your bot and get its API from t.me/BotFather
3. Insert the your BOT API in the "Enter the BOT API:"
4. Get the CHAT ID from t.me/chatid_echo_bot
5. Insert your CHAT ID in the "Enter your CHAT ID"
6. Enter any file name in the "Enter output file name"
7. In the "Enter the drop path", enter the path where the program should be copied after launch
8. In "Client delay", enter the delay of accessing the Telegram API in m\s (recommended: 2000)
9. In "Enter the name in autorun:" enter how the program will be signed in autorun
10. In "Enter the name in taskschd:" enter how the program will be signed in the task scheduler
#### Checkboxes
1. "Auto delete yourself before run" - used together with "Drop and run yourself from [DROP PATH]" - after starting, the program is copied to the path "Enter the drop path:" and starts, and the original program is deleted.
2. "Write yourself in autorun" - sign up for autorun after startup
3. "Drop and run yourself from [DROP PATH]" - copy to the specified path in "Enter the drop path:" and after launching from there
4. "Protect from debuggers (By processes)" - create a thread that will search for debugger and sniffer processes
5. "Write yourself in task scheduler" - sign up for the task scheduler after launch
## Russian
1. Загрузите релиз программы (или скомпилируйте его самостоятельно), а затем запустите Builder.exe (важно: Stub.exe должен быть расположен рядом с Builder.exe)
2. Создайте своего бота и получите его BOT API у t.me/BotFather
3. Вставьте API вашего бота в поле "Enter the BOT API:"
4. Получите CHAT ID у t.me/chatid_echo_bot
5. Вставьте ваш CHAT ID в "Enter the CHAT ID:"
6. Введите любое имя файла в "Enter output file name:"
7. В "Enter the drop path:" введите путь, куда программа должна будет скопирована после запуска
8. В "Client delay", введите задержку обращения к Telegram API в м\с (рекомендуется: 2000)
9. В "Enter the name in autorun:" введите, как программа будет называться в автозагрузке
10. В "Enter the name in taskschd:" введите, как программа будет называться в планировщике задач
#### Галочки
1. "Auto delete yourself before run" - используется вместе с "Drop and run yourself from [DROP PATH]" - после запуска программа копируется в путь   "Enter the drop path:" и запускается, а исходная программа удаляется.
3. "Write yourself in autorun" - если стоит галочка - программа после запуска запишется в автозагрузку
4. "Drop and run yourself from [DROP PATH]" - скопироваться в указанный путь в "Enter the drop path:" и запуститься оттуда
5. "Protect from debuggers (By processes)" - создание потока, который будет искать процессы отладчиков и снифферов
6. "Write yourself in taskschd" - если стоит галочка - программа после запуска запишет себя в планировщик заданий

# [CHANGELOG]
> 17.10.2020 16:30 - Code is optimized, added commands   
> 18.10.2020 18:40 - Code is refactored and optimized, fixed bugs (command inject dll didn't work), added new function in builder (write in scheduler task), updated GUI, added re-launch protection, added commands  
 
# [LICENSE]
 ![B4DB4B3-RAT](https://github.com/4B4DB4B3/B4DB4B3-RAT) is licensed under MIT License - https://mit-license.org/
