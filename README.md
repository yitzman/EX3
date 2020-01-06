# EX3

Flight Gear Simulator - Milestone 1

#### Contributors
Yitzi Jacobs 333991271, Avi Fraind 311519441 
#### Objective
    Connect to the FlightGear Simulator application via server. Send and receive data to and from FlightGear by reading the fly.txt file then interpreting and executing given commands. 
   ## Work Flow
         i) Split fly.txt file int strings using the Lexer class. Each string contains either a command or data required to execute a given command.
         ii) Parse through strings and execute the commands. connect to server etc.. 
         iii) close the client socket and free all dynamically allocated memory.
### Program's Capabilities
   First, we connect to a server in order to have dialogue with the flight simulator. We then save certain variable names in a map data structure linking them to strings representing commands that FlightGear Understands. The program is then capable of referring to those variables and getting or changing any data linked to them. Simple tasks such as Print ,which can print a variable's value, and Sleep, which pauses certain threads, are supported by the program. We can then also read mimicked "while", "if" and function scopes and seamlessly perform the appropriate tasks written in the text file. The program is also capable of interpreting arithmetic expressions using Dijkstra’s Shunting Yard Algorithm.

### GitHub Project Link
        https://github.com/yitzman/EX3
