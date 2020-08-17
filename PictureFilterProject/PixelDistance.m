%This function calculates the square of the distance between two points in
%3D colour space. The inputs are two arrays which contain three elements
%which represent values in 3D colour space (red, green and blue values). The
%output is a single value for squaredDistance.
% Author: Jacob Eyles

function [squaredDistance] = PixelDistance(a,b)
%In the case where the input array contains 'uint8' values, we need to convert
%them to 'double' values to produce the desired squaredDistance. If they
%are already 'double' values, then no change occurs.
a=double(a);
b=double(b);

%The squaredDistance formula takes the difference between the 1st,2nd and
%third values of the two input arrays and squares it. Each value is added
%together to created a total 'squaredDistance' value. This will work with
%any array configuration.
squaredDistance = (a(1)-b(1))^2 + (a(2)-b(2))^2 + (a(3)-b(3))^2;

end

