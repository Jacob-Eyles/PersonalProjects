%THis is a helper function which aims to calculate the median of a given
%array faster than the preset function 'median'.
% Author: Jacob Eyles

function [medianround] = FasterMedian(x)

%The length and the rounded half length of the array is produced.
Length=length(x);
r=round(Length/2);

%The array 'x' is sorted in order and the average between the middle two
%points is calculated and rounded (to be consistent with the 'uint8'
%values).
sortedXarray=sort(x);
medianunrounded=(sortedXarray(r)+sortedXarray(Length-r+1))/2;
medianround=round(medianunrounded);

end