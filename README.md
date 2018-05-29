# ConfigurationParser
A rather simple tool for reading configuration files

I spent some time looking for a C implementation of a tool that could read parameters from an ASCII file, and everything I found was too complicated. ConfigurationParser to the rescue!

Suppose your configuration file looks like this:

```C
# Contents of myConfig.cfg

MySpecialIP = 192.168.0.1
MySpecialPort = 5000
MyNumber = 3.14159 
```

Then reading these using ConfigurationParser is rather straightforward!

```C
char *ip; int port, double myNumber; 

SetConfigurationFile("myConfig.cfg");
ReadString("MySpecialIP", &ip);
ReadInteger("MySpecialPort", &port);
ReadDouble("MyNumber", &myNumber);
```

Comments are indicated using #. ConfigurationParser searches for variable names on the left-hand side of the `=` sign, and then loads the data starting from the first alpha-numeric character to anything to the right of the `=`. It'll tolerate you reading a string as an integer. 

## Todo

Right now, if you have two variable names where one is a subset of the other (e.g. "Oink" and "OinkOink") ConfigurationParser will get confused. 
