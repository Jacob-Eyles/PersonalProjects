%This function will create a list of frames which are to be extracted from
%a movie file. 
%The inputs will be the starting frame number(start), the step size(step) 
%and the number of frames which are required(n).
%The single output will be a 1D array of frame numbers in increasing
%magnitude (framelist).

% Author: Jacob Eyles

function [framelist]= GenerateFrameList(start,step,num)

%defining a finish value for the set. 
finish = (num-1)*step+start;
%The frame list can be created using linspace. The inputs are: start,
%finish and number of frames to create a 1D array of the frame list as
%required.
framelist = linspace(start,finish,num);

end

