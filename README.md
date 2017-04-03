# CfgAdmin
CfgAdmin is a simple library writed in C++ to administrate your configuration files.

Uploaded a new version with some fixes for CodeBlock. 

#List of objetives - Library behavior:

--Load a configuration - OK.

--Get different values - OK (String, Float, Integer values just put the parameter).

--Validate in case of non-existent parameter - In progress.

--Validate in case of invalidad value in parameter - In progress.

--Inteligent library that evaluates the current operating system - In progress (Principally to choose some configurations).

--validateIsInteger() - In progress. (Check if all of the parameter characters are numer).

--validateIsFloat() - In progress. (Check if all of the parameter characters are number or floating point).

--validateParameter() - In progress. (Check if the parameter follows the standard).

--createEmptyFile() - This method will create a new .cfg file.

Misc behavior and library settings.

--Edit the source to fix the type of the variables passed for the parameter of the parse methods. - OK

--Commit the source code. - OK

// bool getValue(string value, out type salida); // Sobrecargar con todos los tipos de datos primitivos.


