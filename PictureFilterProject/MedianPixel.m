%This function calculates the median value for each colour value for a set
%(3D array)of pixels. The input is a single '1 by n by 3' 3D array of 
%pixel(s) containing a 'uint8' value for red, green and blue colours (where
%n is the number of pixels). The ouput is a single (rounded) median value
%for each of the red,green and blue values across the given pixels in the
%original array.
% Author: Jacob Eyles

function [R,G,B] = MedianPixel(pixels)

%A sub-1D-array is created for each of the red,green and blue values in 
%'pixels'. The 'median' function is used on this 1D array which is then
%rounded to the nearest integer. The outputs are the required median 'uint8'
%values for red, green, and blue (R,G,B).

R = round(median(pixels(:,:,1)));
G = round(median(pixels(:,:,2)));
B = round(median(pixels(:,:,3)));

end