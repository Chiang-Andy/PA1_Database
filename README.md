# CS-457 Project Assignment 1:Metadata Management
# Build Environment
Visual Studio Code

Apple clang 12.0.5
# Executable & Compiling
To compile files: Type g++ -std=c++11 main.cpp -o main into the terminal

To execute files: After compiling, an executable "main" should appear. Type './main to launch executable.

# Running The Program
After launching the executable, you should now be able to copy and paste each line from the sql file. Each expected output has been reach from my testing.

# Documentation/Notes
The system design is simple with a main.cpp database file and a table.
My program has a simple way of organizing multiple databases by creating directories for them.
And multiple tables are handled by pushing them into a vector of table classes. 
My program works by using a auto command control is used by looking for specific text case.
Directories is created and saved by storing the name of the database. Name of any database created is saved in the program and can be accessed for future uses.
After such, using a name directory, table is created by finding the name of the data and creating the table under the database filename. Data is parsed to pass in for use. And removing a table is done by using a simple remove function.
Table values are saved within index and place in a vector. 
Select allows you to find the table index if it exists by looking through the vector.
Altering table is done similarily to select as it grabs the values in the table index, but differs by changing the values within the table index.
