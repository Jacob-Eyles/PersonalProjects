%This function will find the pixel, within a list of pixels, which is the
%furthest 'distance' from the median pixel value of the pixel list. The
%distance referred to is the 'square of the distance' between two points in
%3D colour space. This function calls both the 'MedianPixel' and
%'PixelDistance' functions.

%The input is a 3D array containing a single '1 by n by 3' 3D array of 
%pixel(s) containing a 'unit8' value for red, green and blue colours (where
%n is the number of pixels). The ouput is the red, green and blue values of
%the pixel which is the 'most distant' from the median.

% Author: Jacob Eyles

function [R,G,B] = MostDistantPixel(pixels)

%calling the 'MedianPixel' function using a 3D array.
[medianR,medianG,medianB]= MedianPixel(pixels);

%The median values for red, green and blue are assigned to a 'median'
%matrix.
median = [medianR,medianG,medianB];
%The size of the input array 'pixels' is taken. This is a list of 3D pixels
%and so the amount of columns in the array will be the number of 'pixels'
%being analysed.
[~,col,~] = size(pixels);
%creating an empty array for 'squaredDistance' values.
squaredDistance = zeros(1,col);

for i=1:col
    %The 'PixelDistance' function is called and calculates the 'distance'
    %between every pixel and the mean pixel value (as calculated before).
    %These values are placed in the 'squaredDistance' array. The loop
    %counts along the columns of the array and will stop at the final
    %pixel.
    squaredDistance(1,i)= PixelDistance(median,pixels(1,i,:));
    
end

%The 'find' function is used to find the coordinates in the
%'squaredDistance' array of the max distance from the median.
%The coordinates will therefore show which column the 'Most distant pixel'
%is in, and can be used to find the most distant pixel.
[row,col]=find(squaredDistance==max(squaredDistance));

%The coordinates calculated above are put through the original pixel array
%to find the required red, green and blue values. The value is put into an
%array too accomodate for the case where there is more than one maximum.
Rarray=pixels(row,col,1);
Garray=pixels(row,col,2);
Barray=pixels(row,col,3);

%If there was more than one maximum, all values would be the same so taking
%the first value from each red,green and blue would provide the required
%values. If there was only one maximum, the value would remain unchanged.
R=Rarray(1);
G=Garray(1);
B=Barray(1);

end


