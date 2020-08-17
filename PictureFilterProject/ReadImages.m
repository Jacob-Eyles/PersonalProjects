%This function will read a list of images and create a 1D cell array, with
%each element containing an RGB image. The RGB image for each specified
%image will contain a 3D array of 'uint8' values ranging from 0 to 255.

%The inputs of this function are a string containing the images file 
%directory and a 1xn 1D cell array containing the filenames of the images
%to be read (where n is the number of files).

%The output of the function is a a cell array as specified above with each
%cell entry containing a 3D RGB array of values.

% Author: Jacob Eyles

function [picarray] = ReadImages(dirname,namelist)

Length=length(namelist);
%A new empty cell array is created with dimensions of 1xn, where n is the
%length of the cell array containing the file names, (number of files).
picarray= cell(1,Length);

for i=1:Length
    %The loop cycles through each filename in the original cell array and
    %creates a new string value each loop. The string value will be entered
    %into the 'imread' function. The string contains the directory, the
    %'\'symbol (which is required with a directory) and the filename.
    string = sprintf('%s%c%s',dirname,92,namelist{i});
    
    %For each new string value, it is entered into the 'imread' function
    %and creates a new 3D array to be stored in the empty 'picarray' cell
    %array. The final cell array is the required output.
    picarray{1,i}= imread(string);
    
end
    

 