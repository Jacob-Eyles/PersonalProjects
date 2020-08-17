%This function will create an image that has the 'action' removed by
%applying a median filter to a set of source images. Each new pixel in the
%image is the median red green and blue values from the corrsponding pixels
%of the oriainal images. The input is a 1 by n cell array (where n denotes
%the number of source images) and the output is the action removed image as
%a 3D array.
% Author: Jacob Eyles

function [actionRemoved] = RemoveAction(picarray)

%Taking the size and length of each image 3D array within the picarray
%cell array.
[row,col,~] = size(picarray{1});
Length = length(picarray);

%Pre-allocating 4 dimensional matrices for Red,blue and green arrays. These
%4d arrays will be filled with all the r,g,b values of all the values from
%each of the 3d arrays in the 'picarray' cell array.
Red=zeros(row,col,3,Length);
Blue=Red;
Green=Red;
array = Red;

for i=1:Length
    
    
    %Each layer of the 4d array will be values of corresponding 3d array
    %in the'picarray'. Within each 4d layer will be the three layers for
    %the r,g,b values of that particular image (within the 'picarray').
% %     Red(:,:,1,i) = picarray{i}(:,:,1);
% %     Green(:,:,2,i) = picarray{i}(:,:,2);
% %     Blue(:,:,3,i) = picarray{i}(:,:,3);
array(:,:,:,i) = picarray{i}(:,:,:);


end

%The median of all of the first red layer across every image (every 4d
%layer) is placed in the medianRed array. The same is produced for the
%green and blue values.
% medianRed= median(Red(:,:,1,:),4);
% medianGreen= median(Green(:,:,2,:),4);
% medianBlue= median(Blue(:,:,3,:),4);

medianarray = median(array(:,:,:,:),4);

%The actionRemoved array is pre-allocated to have the original dimensions
%of the images in 'picarray'.
actionRemoved = zeros(row,col,3);
actionRemoved(:,:,:) = medianarray;
%The median red,green and blue arrays are placed in the 3d array layers
%1,2,3 respectively of the actionRemoved array.
% actionRemoved(:,:,1) = medianRed;
% actionRemoved(:,:,2) = medianGreen;
% actionRemoved(:,:,3) = medianBlue;

%The actionRemoved values are converted into uint8 values. Providing the
%required output.
actionRemoved = uint8(actionRemoved);

end
