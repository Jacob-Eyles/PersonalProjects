%This helper function calculates the square of the distance between two 
%points in 3D colour space. The inputs are two arrays which contain 
%elements which represent values in 3D colour space (red, green and blue 
%values). Each value for squared distance is placed in an array containing 
%all the squared distance values concerning the two input arrays.

% Author: Jacob Eyles

function [squaredDistance] = PixelDistance2(a,b)
%The case where the input arrays contain 'uint8' values, we need to convert
%them to 'double' values to produce the desired squaredDistance. If they
%are already 'double' values, then no change occurs.
a=double(a);
b=double(b);

%The squaredDistance formula takes the difference between the all the
%red,green and blue values of the two input arrays and squares it. Each
%value is added together to created a total 'squaredDistance' value. This 
%will work with any array configuration.

[row,col,~] = size(a);

%Pre-allocating the squaredDistance array.
squaredDistance = zeros(row,col);

%all the differences across the red, green, and blue values in the two 
%arrays are squared and summed. The output is the required squaredDistance
%array.
squaredDistance(:,:) = (a(:,:,1)-b(:,:,1)).^2 + (a(:,:,2)-b(:,:,2)).^2 ... 
    +(a(:,:,3)-b(:,:,3)).^2;

end
