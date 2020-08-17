%This function creates a 1D cell array containing a list of all files of a
%specified filetype, within a specified directory. In this case, the
%function will be primarily used for the names of image files.

%The inputs to the function are a string containing the image file
%directory and a string containing the filetype or file extension
%asscociated with the required image files: eg: 'jpg'.

%The output will be a 1xn cell array containing a list of the specified
%files (n is the number of files).

% Auothor; Jacob Eyles

function [namelist] = GenerateImageList(dirname,filetype)

%As the 'dirname' input is a directory, it needs a '\' at the end.
%to find all the specified files with the dir function, it requires an
%input of '*.(filetype)' after the dirname. sprintf will create the
%required syntax in the form of a string ready to input to 'dir'.
%In this case, the ascii code for '\*.' are used below.
string = sprintf('%s%c%c%c%s',dirname,92,42,46,filetype);

%The dir function creates a structure array containing the information of
%the required files (name,date,etc..).
dirlist = dir(string);

%finding the number of files produced by the dir function (number of rows).
[row,~] = size(dirlist);
%creating an empty cell array of dimensions 1xn (n=number of files).
namelist = cell(1,row);

%The loop cycles through every row(file) in the structure array and takes
%the name of each file by the '.name' command. Each file name is placed in
%order in the cell array. The array (namelist) is the required output.
for i=1:row
    namelist{1,i} = dirlist(i).name;
end
end

